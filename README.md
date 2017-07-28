# STL to OBJ Geometry Converter

## Overview
stl2obj is CAD utility for converting STL geometries to OBJ format. In addition,
to converting the geometry, stl2obj is capable of:
* Merging vertices;
* Filling holes and cracks; and
* Stitching single edges across surfaces.

## Compiler
The code depends on C++11 features heavily. Therefore, you need to use a
C++11 compliant compiler. If you're using older versions of GCC such as 4.9,
you need to use the flag "std=c++11". This is not necessary in GCC 6 though.

## Search Tree
We use a K-D tree (in this case a 3-D tree) to speed up the process of searching
and merging points. The K-D is parametrized as a template, so it can be used
in arbitrary dimension (2, 3, or higher dimensions).

## Design Pattern
The nice thing about STL and OBJ formats is that, the underlying data structures
are very similar. In both cases, we have a set of vertices, and a set of
polygons which connect those points. Since the undrlying data is similar, we
can avoid copying data thereby speeding up the translation.

The geometry data is stored as an instance of the "Geometry" template class. This
class is derived from "GeomBase<Geometry>" class using the CRTP design pattern.
This technique is very useful since we might want to create new geometry
data types in the future. Note that the class "Geometry" is designed only for
storing data, so it cannot read or write its content.

For importing STL files and exporing OBJ files, we use the visitor design
pattern. We create an abstract class, named "Visitor", which has a single
dispatch function. Every operation on the data, including STL import and OBJ
export, is defined as a type derived from Visitor. using this desing, we can
easily add new functionality to the geometry data type.

In summary, the final code for reading an STL file and writing it to OBJ format
becomes as simple as this:

```c++
//  create a geometry object
    Geometry tessel;

//  load STL (e.g. input.stl)
    tessel.visit (ImportSTL ("input.stl"));

//  save OBJ (e.g. output.obj)
    tessel.visit (ExportOBJ ("output.obj"));

