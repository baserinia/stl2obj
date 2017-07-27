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

template <int DIM, typename REAL = double>
class KDTree {
//  define Point type for convenience
    using Point = VectorND<DIM, REAL>;

//  define Node type for private operations on the tree. No one should use
//  this outside KDTree
    class Node {
        Node(int id) : id_(id) {}
        ~Node() { delete left_; delete right_; }
        Node* left_ = nullptr;
        Node* right_ = nullptr;
        unsigned id_;
        unsigned size_ = 0;
        signed char axis_ = 0;
        friend class KDTree<DIM, REAL>;
    };

//  pointer to the root node
    Node* root_;

//  vector of all points; this can dynamically grow or shrink
//  Note that this is the sinle data structure for storing points data. The
//  tree has access only to elements of this vector, but there is no point
//  data in the tree. This simplifies the algorithms and makes the API
//  easier to use.
    std::vector<Point> data_;

public: // methos
//  default constructor
    KDTree() : root_(nullptr) {}

//  default destructor
    ~KDTree() { delete root_; }

//  delete copy constructor, assignment operator, move constructor, and
//  move assignment operator. we don't want someone accidentally copies a
//  search tree
    KDTree(const KDTree&) = delete;
    KDTree(KDTree&&) = delete;
    KDTree& operator=(const KDTree&) = delete;
    KDTree& operator=(KDTree&&) = delete;

//  insert a new point into the tree
    void insert(const Point& point) {
        data_.push_back(point);
        root_ = insert(root_, size() - 1);
    }

//  get the current size
    size_t size() { return data_.size(); }

//  This function is N^2 so it's very inefficient. It's included only for
//  testing purpose to confirm the correctness of algorithm. Otherwise,
//  it shouldn't be used in actual code.
    int findNearestBruteForce(const Point& pt);

//  This function is NlogN, so it should be used in actual code.
    int findNearest(const Point& pt);

//  return the point from its id
    Point getPoint(int index) {
        return data_[index];
    }

private: // methods
    size_t size(Node* node);
    Node* insert(Node* node, int id);
    int findNearest(Node* node, const Point& point, REAL& minDist);
    Node* findParent(Node* node, const Point& point);
};


// private version of size, used only by KDTree
template <int DIM, typename REAL>
size_t KDTree<DIM, REAL>::size(Node* node)
{
    if (node == nullptr) return 0;
    return node->size_;
}

// private version of insert, used only by KDTree
template <int DIM, typename REAL>
typename KDTree<DIM, REAL>::Node*
KDTree<DIM, REAL>::insert(Node* node, int id)
{
    if (!node) {
        return new Node(id);
    } else if (data_[id][node->axis_] <= data_[node->id_][node->axis_]) {
        node->left_ = insert(node->left_, id);
        node->left_->axis_ = (node->axis_ + 1) % DIM;
    } else {
        node->right_ = insert(node->right_, id);
        node->right_->axis_ = (node->axis_ + 1) % DIM;
    }
    node->size_ = 1 + size(node->left_) + size(node->right_);
    return node;
}

//  Find the nearest point in the data set to "point".
//  This is the public version of this function. It does two things:
//  1) It finds the potential tree node were "point" to be inserted into tree.
//  2) It traverses the tree once more to find all points that might be closer
//     to point.
//  return value: index of the nearest node
template <int DIM, typename REAL>
int KDTree<DIM, REAL>::findNearest(const Point& point)
{
    Node* parent = findParent(root_, point);
    if (!parent) return -1;
    REAL minDist = Point::get_dist_sqr(point, data_[parent->id_]);
    int better = findNearest(root_, point, minDist);
    return (better >= 0) ? better : parent->id_;
//    return parent->id_;
}

//  Find the nearest point in the data set to "point"
//  This is the private version of this function. Although it works for
//  arbitrary large values of "minDist", it's only efficient for small values
//  of minDist. For large values of minDist, it behaves like a brute-force
//  search.
template <int DIM, typename REAL>
int
KDTree<DIM, REAL>::findNearest(Node* node, const Point& point, REAL& minDist)
{
    if (!node) return -1;
    REAL d = Point::get_dist_sqr(point, data_[node->id_]);

    int result = -1;
    if (d < minDist) {
        result = node->id_;
        minDist = d;
    }

    REAL dp = data_[node->id_][node->axis_] - point[node->axis_];
    if (dp * dp < minDist) {
        int pt = findNearest(node->left_, point, minDist);
        if (pt >= 0) result = pt;
        pt = findNearest(node->right_, point, minDist);
        if (pt >= 0) result = pt;
    } else if (point[node->axis_] <= data_[node->id_][node->axis_]) {
        int pt = findNearest(node->left_, point, minDist);
        if (pt >= 0) result = pt;
    } else {
        int pt = findNearest(node->right_, point, minDist);
        if (pt >= 0) result = pt;
    }
    return result;
}

//  Give a point "point" and a node "node", return the parent node if we were to
//  insert the point into the tree. This is useful because it gives us the
//  initial guess about the nearest point in the tree.
template <int DIM, typename REAL>
typename KDTree<DIM, REAL>::Node*
KDTree<DIM, REAL>::findParent(Node* node, const Point& point)
{
    if (!node) {
        return nullptr;
    } else if (point[node->axis_] <= data_[node->id_][node->axis_]) {
        return node->left_ ? findParent(node->left_, point) : node;
    } else {
        return node->right_ ? findParent(node->right_, point) : node;
    }
}

// This is just a brute force O(n) search. Use only for testing.
template <int DIM, typename REAL>
int
KDTree<DIM, REAL>::findNearestBruteForce(const Point& pt)
{
    int index = -1;
    REAL minD2 = std::numeric_limits<REAL>::max();
    for (int i = 0; i < data_.size(); i++) {
        REAL d2 = Point::get_dist_sqr(pt, data_[i]);
        if (d2 < minD2) {
            minD2 = d2;
            index = i;
        }
    }
    return index;
}


#endif // TYPE_KDTREE_H_
