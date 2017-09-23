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

#include <memory>
#include <limits>
#include <vector>
#include "vectornd.h"

template <int Dim, typename Real = double>
class KDTree {
//  define Point type for convenience
    using Point = VectorND<Dim, Real>;

//  define Node type for private operations on the tree. No one should use
//  this outside KDTree
    class Node {
        Node(int id, signed char axis = 0) : id_(id), axis_(axis) {}
        std::unique_ptr<Node> left_ = nullptr;
        std::unique_ptr<Node> right_ = nullptr;
        uint32_t id_;
        int8_t axis_;
        friend class KDTree<Dim, Real>;
    };

    using NodePtr = Node*;

//  pointer to the root node
    std::unique_ptr<Node> root_ = nullptr;

//  vector of all points; this can dynamically grow or shrink
//  Note that this is the sinle data structure for storing points data. The
//  tree has access only to elements of this vector, but there is no point
//  data in the tree. This simplifies the algorithms and makes the API
//  easier to use.
    std::vector<Point> data_;

public: // methos
//  default constructor
    KDTree() = default;

//  default destructor
    ~KDTree() = default;

//  delete copy constructor, assignment operator, move constructor, and
//  move assignment operator. we don't want someone accidentally copies a
//  search tree
    KDTree(const KDTree&) = delete;
    KDTree(KDTree&&) = delete;
    KDTree& operator=(const KDTree&) = delete;
    KDTree& operator=(KDTree&&) = delete;

//  insert a new point into the tree
    void insert(const Point& point) {
        uint32_t id = data_.size();
        data_.push_back(point);
        if (!root_) {
            root_ = std::unique_ptr<Node>(new Node(0));
        } else {
            Node* node = root_.get();
            Node* parent = nullptr;
            while (node) {
                parent = node;
                node = (data_[id][node->axis_] <= data_[node->id_][node->axis_])
                    ? node->left_.get() : node->right_.get();
            }

            if (data_[id][parent->axis_] <= data_[parent->id_][parent->axis_]) {
                parent->left_ = std::unique_ptr<Node>(new Node(id, (parent->axis_ + 1) % Dim));
            } else {
                parent->right_ = std::unique_ptr<Node>(new Node(id, (parent->axis_ + 1) % Dim));
            }
        }
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
    int findNearest(Node* node, const Point& point, Real& minDist);
    const Node* findParent(const Point& point) const;
};


//  Find the nearest point in the data set to "point".
//  This is the public version of this function. It does two things:
//  1) It finds the potential tree node were "point" to be inserted into tree.
//  2) It traverses the tree once more to find all points that might be closer
//     to point.
//  return value: index of the nearest node
template <int Dim, typename Real>
int KDTree <Dim, Real>::findNearest(const Point& point)
{
    const Node* parent = findParent(point);
    if (!parent) return -1;
    Real minDist = Point::get_dist_sqr(point, data_[parent->id_]);
    int better = findNearest(root_.get(), point, minDist);
    return (better >= 0) ? better : parent->id_;
}

//  Find the nearest point in the data set to "point"
//  This is the private version of this function. Although it works for
//  arbitrary large values of "minDist", it's only efficient for small values
//  of minDist. For large values of minDist, it behaves like a brute-force
//  search.
template <int Dim, typename Real>
int
KDTree<Dim, Real>::findNearest(Node* node, const Point& point, Real& minDist)
{
    if (!node) return -1;
    Real d = Point::get_dist_sqr(point, data_[node->id_]);

    int result = -1;
    if (d < minDist) {
        result = node->id_;
        minDist = d;
    }

    Real dp = data_[node->id_][node->axis_] - point[node->axis_];
    if (dp * dp < minDist) {
        int pt = findNearest(node->left_.get(), point, minDist);
        if (pt >= 0) result = pt;
        pt = findNearest(node->right_.get(), point, minDist);
        if (pt >= 0) result = pt;
    } else if (point[node->axis_] <= data_[node->id_][node->axis_]) {
        int pt = findNearest(node->left_.get(), point, minDist);
        if (pt >= 0) result = pt;
    } else {
        int pt = findNearest(node->right_.get(), point, minDist);
        if (pt >= 0) result = pt;
    }
    return result;
}

//  Give a point "point" and a node "node", return the parent node if we were to
//  insert the point into the tree. This is useful because it gives us the
//  initial guess about the nearest point in the tree.

template <int Dim, class Real>
const typename KDTree<Dim, Real>::Node*
KDTree<Dim, Real>::findParent(const Point& point) const
{
    Node* node = root_.get();
    Node* parent = nullptr;
    while (node) {
        parent = node;
        node = (point[node->axis_] <= data_[node->id_][node->axis_])
            ? node->left_.get() : node->right_.get();
    }
    return parent;
}


// This is just a brute force O(n) search. Use only for testing.
template <int Dim, typename Real>
int
KDTree<Dim, Real>::findNearestBruteForce(const Point& pt)
{
    int index = -1;
    Real minD2 = std::numeric_limits<Real>::max();
    for (int i = 0; i < data_.size(); i++) {
        Real d2 = Point::get_dist_sqr(pt, data_[i]);
        if (d2 < minD2) {
            minD2 = d2;
            index = i;
        }
    }
    return index;
}


#endif // TYPE_KDTREE_H_
