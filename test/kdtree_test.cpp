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

#include <cstdio>
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <cassert>
#include "../src/vectornd.h"
#include "../src/kdtree.h"

// Unit test
int main()
{
//  for consistency, use the same seed
    std::default_random_engine gen(0);

//  generate random double between 0 and 1.
    std::uniform_real_distribution<double> dis(0, 1);

//  create a 3D-tree of double precision
    KDTree<3> tree; 
    for (int i = 0; i < 100000; i++) {
        VectorND<> vec (dis(gen), dis(gen), dis(gen));
        tree.insert(vec);
    }

    std::chrono::duration<double> delt1(0);
    std::chrono::duration<double> delt2(0);

//  let's find the nearest point to 1000 random points
    for (int i = 0; i < 1000; i++) {
        VectorND<> center (dis(gen), dis(gen), dis(gen));

//      reset timer
        auto t0 = std::chrono::high_resolution_clock::now();

//      we use brute force search for testing
        int index1 = tree.findNearestBruteForce(center);
        VectorND<> pt1 = tree.getPoint(index1);

//      measure brute force search time
        auto t1 = std::chrono::high_resolution_clock::now();
        delt1 += t1 - t0;

//      let's test the tree search
        int index2 = tree.findNearest(center);
        VectorND<> pt2 = tree.getPoint(index2);

//      measure KD tree search time
        auto t2 = std::chrono::high_resolution_clock::now();
        delt2 += t2 - t1;

//      fail if the search results are different
        assert(index1 == index2);
    }

    printf("Brute force time: %.6g sec\n", delt1.count());
    printf("KD tree time:     %.6g sec\n", delt2.count());
    printf("Terminated successfully!\n", delt2.count());
}

