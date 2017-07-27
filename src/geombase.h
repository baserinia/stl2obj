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

#ifndef TYPE_GEOMBASE_H_
#define TYPE_GEOMBASE_H_
#pragma once

// forward declaration
template<typename T> class Visitor;

template<typename T>
class GeomBase {
public:
    virtual void visit(Visitor<T>&& v) {
        static_cast<T*>(this)->visit(std::move(v));
    }
};

#endif // TYPE_GEOMBASE_H_
