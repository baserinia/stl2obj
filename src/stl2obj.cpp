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
#include <cstdlib>
#include <getopt.h>

#include "vectornd.h"
#include "geometry.h"
#include "importstl.h"
#include "exportobj.h"

// The name of this program
static const char* PROGRAM_NAME = "stl2obj";

// author
static const char* AUTHOR = "Amir Baserinia";

// usage help
void usage (int status)
{
    printf ("Usage: %s [OPTION]... [FILE]...\n", PROGRAM_NAME);
    printf ("Converts CAD STL models to OBJ format.\n");
    printf (
        "Options:\n"
        "  -m, --merge-vertices     merge vertices\n"
        "  -f, --fill-holes         file holes in surface\n"
        "  -s, --stich-cureves      stick curves between surfaces\n"
        "  -t, --tolerance          merge tolerance\n");
    printf (
        "Examples:\n"
        "  %s input.stl output.obj  convert input from STL to OBJ and write "
        "to output.\n", PROGRAM_NAME);
    exit (status);
}

// version information
void version ()
{
    printf ("%s converts an STL CAD file to OBJ format.\n", PROGRAM_NAME);
    printf ("Copyright (c) 2017 %s\n", AUTHOR);
}

int main (int argc, char **argv)
{
//  command line options
    static struct option const long_options[] = {
        {"merge-vertices", no_argument, NULL, 'm'},
        {"fill-holes", no_argument, NULL, 'f'},
        {"stich-curves", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };

// Variables that are set according to the specified options.
    bool merge_vertices = false;
    bool fill_holes     = false;
    bool stich_curves   = false;
    bool tolerance_val  = false;

// Parse command line options.
    int c; 
    while ((c = getopt_long (argc, argv, "mfsvh", long_options, NULL)) != -1) {
        switch (c) {
        case 'm':
            merge_vertices = true;
            break;
        case 'f':
            fill_holes = true;
            break;
        case 's':
            stich_curves = true;
            break;
        case 'v':
            version();
            break;
        default:
            usage (EXIT_FAILURE);
        }
    }

//  create a geometry tesselation object
    Geometry tessel;

//  fill up the tesselation object with STL data (load STL)
    tessel.visit (ImportSTL ("Fidgit.stl"));

//  write down the tesselation object into OBJ file (save OBJ)
    tessel.visit (ExportOBJ ("file.obj"));


    return EXIT_SUCCESS;
}

