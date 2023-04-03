// Copyright (c) 2021 Hoa Lu

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
#include <sstream>
#include <chrono>
#include "importobj.h"
#include "vectornd.h"

void ImportOBJ::load(Geometry& model)
{
//  let's time the OBJ import
    auto t0 = std::chrono::high_resolution_clock::now();

    std::ifstream fileOBJ (filename_.c_str(), std::ios::binary);
	if (!fileOBJ.is_open()) {
		std::cerr << "Failed to open file " << filename_ << std::endl;
	}

	std::string row;
	int v_count = 0;
    bool first_face = true;
    bool has_texture = false;

    while (getline(fileOBJ, row)) {
		std::istringstream srow(row);
        std::string tempst;

        if (row.substr(0,2) == "v ") {  // Vertices
            double x,y,z;
            srow >> tempst >> x >> y >> z;
            auto vec = VectorND<>(x, y, z);
            model.verts_.push_back(vec);
            ++v_count;
        }
        else if (row.substr(0,2) == "f ") {
            int v, vt;
			char slash;
            std::string::size_type slashpos;

            srow >> tempst;
            if (first_face) {
                // check if face as texture 'v/vt'
                first_face = false;
                slashpos = row.find('/', 2);
                has_texture = (slashpos != std::string::npos);
            }
            if (has_texture) {
                while(srow >> v >> slash >> vt) {
                    int index = ( v > 0 )? v: v_count + v;
                    model.faces_.push_back(index - 1);
                }
            } else {
                while(srow >> v) {
                    int index = ( v > 0 )? v: v_count + v;
                    model.faces_.push_back(index - 1);
                }
            }
        }
    }

    std::chrono::duration<double> duration = 
        std::chrono::high_resolution_clock::now() - t0;
    std::cout << "Finished reading OBJ in " << (double)duration.count() <<
        " seconds!" << std::endl;
        
}
