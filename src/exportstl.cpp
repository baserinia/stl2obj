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
#include <chrono>
#include "exportstl.h"
#include "vectornd.h"

//#include <cassert>
//assert(CHAR_BIT * sizeof (float) == 32);

// template<typename T>
// void write(std::ofstream& stream, T& item)
// {
//     //char buffer[sizeof(T)];
//     //auto s = std::to_string(item);
//     //s.copy(buffer, sizeof(T));
//     //out.write(reinterpret_cast<const char*>(&f), sizeof(float));
//     stream.write(reinterpret_cast<const char*>(&item), sizeof(T));
// }

// void write_vec(std::ofstream& stream, VectorND<> v)
// {
//     write<float>(stream, (float)v[0]);
//     write<float>(stream, (float)v[1]);
//     write<float>(stream, (float)v[2]);
// }
void write_vec(std::ofstream& stream, VectorND<> v)
{
    std::cout << "v";
    for (unsigned i=0; i<3; i++) {
        float f = (float) v[i];
        //char* s = reinterpret_cast<char*>(&f);
        stream.write(reinterpret_cast<char*>(&f), sizeof(float));

        //float f_recover = *(float*) s;
        //std::cout << " " << f << "(" << f_recover << ")";
    }
    std::cout << std::endl;
}

void ExportSTL::save_bin(Geometry& model)
{
    std::ofstream fileSTL (filename_.c_str(), std::ios::out | std::ios::binary);

    std::string signature("STLB OBJ to STL conveter");
    char header[80]{};
    signature.copy(header, sizeof signature);

    fileSTL.write(header, sizeof header);

    uint32_t numOfTris = model.faces_.size() / 3;
    fileSTL.write(reinterpret_cast<const char*>(&numOfTris), 4);

    //std::cout << "size (uint32_t): " << model.faces_.size() <<std::endl;
    //std::cout << "size (uint32_t): " << numOfTris <<std::endl;

    char dummy[2];
    uint32_t v_count = 0;
    //for (unsigned i=0; i < numOfTris; i++) {
    for (unsigned idx: model.faces_) {
        if ( v_count % 3 == 0 ) {
            auto norm = VectorND<>();
            write_vec(fileSTL, norm);
        }
        //for (unsigned j=0; j < 3; j++) {
        //unsigned index = model.faces_[v_count++];
        write_vec(fileSTL, model.verts_[idx]);
        //}
        fileSTL.write(dummy, 2);
        std::cout << "v_count: " << v_count;
        std::cout << "v_index: " << idx << std::endl;
        v_count++;
    }

    fileSTL.close();
    if(!fileSTL.good()) {
      std::cout << "Error occurred at writing!" << std::endl;
    }

}

void ExportSTL::save_ascii(Geometry& model) {
    std::ofstream fileSTL (filename_.c_str(), std::ios::out);

    fileSTL << "solid" <<std::endl;

    uint32_t v_count = 0;
    for (unsigned idx: model.faces_) {
        if ( v_count % 3 == 0 ) {
            fileSTL << "facet normal 0.0 0.0 0.0" << std::endl;
            fileSTL << "outer loop" << std::endl;
        }

        fileSTL << "vertex";
        // for (auto ind: model.verts_[idx]) {
        //     fileSTL << " " << ind;
        // }
        for (unsigned i=0; i< 3; i++) {
            float f = (float) model.verts_[idx][i];
             fileSTL << " " << f;
        }
        fileSTL << std::endl;

        v_count++;

        if ( v_count % 3 == 0 ) {
            fileSTL << "endloop" << std::endl;
            fileSTL << "endfacet" << std::endl;
        }
    }

    fileSTL << "endsolid" <<std::endl;
}

void ExportSTL::save(Geometry& model) {
    auto t0 = std::chrono::high_resolution_clock::now();

    //save_bin(model);

    save_ascii(model);

    std::chrono::duration<double> duration = 
        std::chrono::high_resolution_clock::now() - t0;
    std::cout << "Finished writing STL in " << (double)duration.count() <<
        " seconds!" << std::endl;
}