// stl2obj converts an STL CAD file to OBJ format.

// Copyright (c) 2017 Amir Baserinia

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TYPE_KDTREE_H_
#define TYPE_KDTREE_H_
#pragma once

#include <vector>
#include "vectornd.h"

// template class for a K-D tree node, where K is the number of dimensions.
// REAL can be float or double, depending on the precision requred.
template <int DIM, typename REAL = double>
class KDTreeNode {
public:
//  default constructor
    KDTreeNode() :
        left_(nullptr), right_(nullptr), axis_(-1) {}

//  default destructor
    ~KDTreeNode();

private:
    // left and right children
    KDTreeNode<DIM, REAL>* left_;
    KDTreeNode<DIM, REAL>* right_;

    // coordinates of the point stored in this node. This is also the
    // cut value along the cut direction (axis_).
    // left branch <= cut value
    // right branch > cut value
    VectorND<DIM, REAL> point_;

    // the direction along which the data is cut:
    // 0 for x, 1 for y, 2 for z, ...
    // for final nodes (leaves) axis_ = -1
    unsigned char axis_;

    // we use this flag for recursive traversing
    bool isChecked_;

//  we may need this to keep track of node association with external data
//  structures. For example, an array may contain the list of all vertices.
//  The index of the vertex associated with this node would be stored here.
    unsigned id_;

};


template <int DIM, typename REAL = double>
class KDTree {
//  define Point type for convenience
    using Point = VectorND<DIM, REAL>;

//  define Node type for private operations on the tree. No one should use
//  this outside KDTree
    class Node {
        Node(const Point& point) :
            left_(nullptr),
            right_(nullptr),
            point_(point),
            id_(0),
            axis_(-1),
            isChecked_(false) {}
        Node* left_;
        Node* right_;
        Point point_;
        size_t size_;
        unsigned id_;
        short axis_;
        bool isChecked_;
        friend class KDTree<DIM, REAL>;
    };

//  pointer to the root node
    Node* root_;

//  vector of all points; this can be dynamically grow or shrink
    std::vector<Point> data_;

public: // methos
//  default constructor
    KDTree() : root_(nullptr) {}

//  default destructor
    ~KDTree() {}

//  insert a new point into the tree
    void insert(const Point& point) {
        root_ = insert(root_, point);
    }

//  get the current size
    size_t size() {
        return size(root_);
    }

//  This function is N^2 so it's very inefficient. It's included only for
//  testing purpose to confirm the correctness of algorithm. Otherwise,
//  it shouldn't be used in actual code.
    int findNearestBruteForce(const Point& pt);

//  This function is NlogN, so it should be used in actual code.
    int findNearest(const Point& pt);

private: // methods
//  private version of brute force find
//    int findNearestBruteForce(const VectorND<DIM, REAL>& ptKDTreeNode<DIM, REAL>* node
    size_t size(Node* node);
    Node* insert(Node* node, const Point& point);
    int findNearest(Node* node, const Point& point, REAL& minDist);
    Node* findParent(Node* node, const Point& point);
};

// private version of size
template <int DIM, typename REAL>
size_t KDTree<DIM, REAL>::size(Node* node)
{
    if (node == nullptr) return 0;
    return node->size_;
}

// private version of insert, used only by KDTree
template <int DIM, typename REAL>
typename KDTree<DIM, REAL>::Node*
KDTree<DIM, REAL>::insert(Node* node, const Point& point)
{
    if (!node) {
        return new Node(point);
    } else if (point[node->axis_] <= node->point_[node->axis_]) {
        node->left_ = insert(node->left_, point);
        node->left_->axis_ = (node->axis_ + 1) % DIM;
    } else {
        node->right_ = insert(node->right_, point);
        node->right_->axis_ = (node->axis_ + 1) % DIM;
    }
    node->size_ = 1 + size(node->left_) + size(node->right_);
    return node;
}


template <int DIM, typename REAL>
int KDTree<DIM, REAL>::findNearest(const Point& point)
{
    Node* parent = findParent(root_, point);
    if (!parent) return -1;
    REAL minDist = get_distance(point, parent->point_);
    Node* better = findNearest(root_, point, minDist);
    return (better >= 0) ? better->id_ : parent->id_;
}

template <int DIM, typename REAL>
int
KDTree<DIM, REAL>::findNearest(Node* node, const Point& point, REAL& minDist)
{
    if (!node) return -1;
    REAL d = get_distance(point, node->point_);

    int result = -1;
    if (d < minDist) {
        result = node->id_;
        minDist = d;
    }

    REAL dp = std::abs(node->point_[node->axis_] - point[node->axis_]);
    if (dp < minDist) {
        int pt = findNearest(node->left_, point, minDist);
        if (pt >= 0) result = pt;
        pt = findNearest(node->right_, point, minDist);
        if (pt >= 0) result = pt;
    } else if (point[node->axis_] <= node->point_[node->axis_]) {
        int pt = findNearest(node->left_, point, minDist);
        if (pt >= 0) result = pt;
    } else {
        int pt = findNearest(node->right_, point, minDist);
        if (pt >= 0) result = pt;
    }
    return result;
}

template <int DIM, typename REAL>
typename KDTree<DIM, REAL>::Node*
KDTree<DIM, REAL>::findParent(Node* node, const Point& point)
{
    if (!node) {
        return nullptr;
    } else if (node->left_ && node->right_) {
        return node;
    } else if (point[node->axis_] <= node->point_[node->axis_]) {
        return findParent(node->left_);
    } else {
        return findParent(node->right_);
    }
}

#endif // TYPE_KDTREE_H_
