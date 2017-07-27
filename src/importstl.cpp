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

void ImportSTL::load(Geometry& model)
{
    std::ifstream fileSTL (filename_.c_str(), std::ios::in | std::ios::binary);

    char header[80];
    fileSTL.read (header, 80);

    char numStr[4];
    fileSTL.read(numStr, 4);
    unsigned numOfTris = *(uint32_t*)numStr;
    std::cout << numOfTris << std::endl;
}

