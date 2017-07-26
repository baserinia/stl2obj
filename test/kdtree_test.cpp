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

#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include "../src/vectornd.h"
#include "../src/kdtree.h"


// Unit test
int main()
{
    KDTree<3, double> tree;

//  for consistency, use the same seed
    std::default_random_engine gen(0);

//  generate random double between 0 and 1.
    std::uniform_real_distribution<double> dis(0, 1);

    for (int i = 0; i < 100; i++) {
        VectorND<3, double> vec (dis(gen), dis(gen), dis(gen));
        tree.insert(vec);
    }

    std::cout << "Terminated successfully!" << std::endl;
}

