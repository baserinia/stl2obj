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


// template class for a K-D tree node, where K is the number of dimensions.
// Real can be float or double, depending on the precision requred.
template <int K, typename Real = double>
class KDTreeNode {
public:
//  default constructor
    KDTreeNode() :
        left_(nullptr), right_(nullptr), cutDir_(-1) {}

//  default destructor
    ~KDTreeNode();

private:
    // left and right children
    KDTreeNode<K, Real>* left_, right_;

    // cut value for points in the left and right branches.
    // left branch <= cut value
    // right branch > cut value
    Real cutValue_;

    // the direction along which the data is cut:
    // 0 for x, 1 for y, 2 for z, ...
    // for final nodes (leaves) cutDir_ = -1
    unsigned char cutDir_;

//  allow KDTree to access the interanals of this
    friend class KDTree<K, Real>;
};


template <int K, typename Real = double>
class KDTree {
public:
//  default constructor
    KDTree();

//  default destructor
    ~KDTree();

//  This function is N^2 so it's very inefficient. It's included only for
//  testing purpose to confirm the correctness of algorithm. Otherwise,
//  it shouldn't be used in actual code.
    int findNearestByBruteForce(const Point& pt);

//  This function is NlogN, so it should be used in actual code.
    int findNearest(const Point& pt);
   

//  Allow KDTreeNode access the internals of this class
    friend class KDTreeNode;
private:
//  pointer to the root node
    KDTreeNode<K, Real>* root_;

//  vector of all points; this can be dynamically grow or shrink
    std::vector<VectorND<K, Real>> data_;

};

#ifdef // TYPE_KDTREE_H_
