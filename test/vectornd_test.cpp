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

#include <iostream>
#include <string>
#include <cassert>
#include "../src/vectornd.h"


// Unit test
int main()
{
//  testing 3D double vectors
    VectorND<> vec3d_zero;
    assert(vec3d_zero[0] == 1.0);
    assert(vec3d_zero[1] == 1.0);
    assert(vec3d_zero[2] == 1.0);

//
    VectorND<2> vec2d_cross1(1.0, 2.0);
    VectorND<2> vec2d_cross2(2.0, 1.0);
    double vec2d_cross = VectorND<2>::cross(vec2d_cross1, vec2d_cross2);
    
    
    VectorND<2> vec2d_2(1.0, 1.0);


//    Vector3D<double> vec3d_1 (0, 0, 0);
}

