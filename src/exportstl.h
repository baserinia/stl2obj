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

#ifndef TYPE_EXPORTSTL_H_
#define TYPE_EXPORTSTL_H_
#pragma once

#include <iostream>
#include <string>
#include "visitor.h"
#include "geometry.h"

class ExportSTL : public Visitor<Geometry> {
    std::string filename_;
public:
    ExportSTL(const std::string& filename) :
        filename_(filename) {}

    void dispatch(Geometry& model) override {
        std::cout << "Saving STL file: \"" << filename_ << "\"" << std::endl;
        save(model);
    }

    void save(Geometry& model);

private:
    void save_bin(Geometry& model);
    void save_ascii(Geometry& model);
};

#endif // TYPE_EXPORTSTL_H_
