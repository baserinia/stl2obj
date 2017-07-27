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

#include <fstream>
#include "importstl.h"
#include "vectornd.h"
#include "kdtree.h"

template<typename T>
T read(std::ifstream& stream)
{
    char buffer[sizeof(T)];
    stream.read(buffer, sizeof(T));
    return *(T*)buffer;
}

// specialization
template<>
VectorND<> read<VectorND<>>(std::ifstream& stream)
{
    return VectorND<>(
        read<float>(stream),
        read<float>(stream),
        read<float>(stream)
    );
}

void ImportSTL::load(Geometry& model)
{
    std::ifstream fileSTL (filename_.c_str(), std::ios::in | std::ios::binary);

    char header[80];
    fileSTL.read (header, 80);

    char numStr[4];
    fileSTL.read(numStr, 4);
    unsigned numOfTris = *(uint32_t*)numStr;
    std::cout << "Reading " << numOfTris << " triangles ..." << std::endl;

//  build search tree
    KDTree<3> tree;
    for (unsigned i = 0; i < numOfTris; i++) {
//      read the normal vector but ignore it.
        auto norm = read<VectorND<>>(fileSTL);

        for (unsigned j = 0; j < 3; j++) {
            unsigned index;
            auto vec = read<VectorND<>>(fileSTL);
            int ind = tree.findNearest(vec);
            if ((ind < 0) || (VectorND<>::get_dist(vec, tree.getPoint(ind)) > 1.0e-8)) {
                index = tree.size();
                tree.insert(vec);
                model.verts_.push_back(vec);
            } else {
                index = ind;
            }
            model.faces_.push_back(index);
        }

//      skip 2 bytes of dummy data
        char dummy[2];
        fileSTL.read(dummy, 2);
    }

    std::cout << "Points reduced from " << 3 * numOfTris << " to " << 
        tree.size() << " after merging!" << std::endl;
}

