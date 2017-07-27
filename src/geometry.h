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

#ifndef TYPE_GEOMETRY_H_
#define TYPE_GEOMETRY_H_
#pragma once

#include <vector>
#include "vectornd.h"
#include "geombase.h"
#include "visitor.h"

// CRTP is used to avoid dynamic polymorphism
class Geometry : public GeomBase<Geometry> {
//  list of vertices as a vector of 3D points
    std::vector<VectorND<>> verts_;
//  list of triangular faces as a vector of 3 indices. The indices point to
//  the vertices in verts_.
    std::vector<unsigned[3]> faces_;
public:
    Geometry() {}

    void visit(Visitor<Geometry>&& v) {
        v.dispatch(*this);
    }
};

#endif // TYPE_GEOMETRY_H_
