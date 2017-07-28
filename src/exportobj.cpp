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
#include <chrono>
#include "exportobj.h"
#include "vectornd.h"


void ExportOBJ::save(Geometry& model)
{
    auto t0 = std::chrono::high_resolution_clock::now();

    std::ofstream fileOBJ (filename_.c_str(), std::ios::out);

    fileOBJ << "# Object name" << std::endl;
    fileOBJ << "o " << filename_ << std::endl;
    fileOBJ << std::endl;

    fileOBJ << "# Begin list of vertices" << std::endl;
    for (auto vec : model.verts_) {
        fileOBJ << "v " <<
            vec[0] << " " <<
            vec[1] << " " <<
            vec[2] << " 1.0" << std::endl;

    }
    fileOBJ << "# End list of vertices" << std::endl;
    fileOBJ << std::endl;

    fileOBJ << "# Begin list of faces" << std::endl;
    unsigned count = 0;
    for (auto ind : model.faces_) {
        if (count++ % 3 == 0) fileOBJ << "f ";
        fileOBJ << ind + 1 << " ";
        if (count % 3 == 0) fileOBJ << std::endl;
    }
    fileOBJ << "# End list of faces" << std::endl;
    fileOBJ << std::endl;

    std::chrono::duration<double> duration = 
        std::chrono::high_resolution_clock::now() - t0;
    std::cout << "Finished writing OBJ in " << (double)duration.count() <<
        " seconds!" << std::endl;
}

