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
The nice thing about STL and OBJ formats is that the underlying data structures
are very similar. In both cases, we have a set of vertices, and a set of
polygons which connect those vertices. Since the undrlying data is similar, we
can avoid copying data, thereby speeding up the translation.

The geometry data is stored as an instance of the "Geometry" template class. This
class is derived from "GeomBase<Geometry>" class using the CRTP idiom.
This technique is very useful since we might want to create new geometry
data types in the future. Note that the class "Geometry" is designed only for
storing data, so it cannot read or write its content.

For importing STL files and exporing OBJ files, we use the visitor design
pattern. We create an abstract class, named "Visitor", which has a single
dispatch function. Every operation on the data, including STL import and OBJ
export, is defined as a new type derived from Visitor. using this pattern, we can
easily add new functions to the geometry data type. For example, we can
add another exporter for PLY data format, without changing anything in the code.

In summary, the final code for reading an STL file and writing it to OBJ format
becomes as simple as this:

```c++
//  create a geometry object
    Geometry tessel;

//  load STL (e.g. input.stl)
    tessel.visit (ImportSTL ("input.stl"));

//  save OBJ (e.g. output.obj)
    tessel.visit (ExportOBJ ("output.obj"));
```

## Sample Output
Here is a sample output for an STL file with 99030 triangles (source:
[Thingverse:1363827](https://www.thingiverse.com/thing:1363827)).
```
$ ./stl2obj Fidgit.stl Fidgit.obj
Loading STL file "Fidgit.stl"
Reading 33010 triangles ...
Points reduced from 99030 to 16523 after merging!
Finished reading STL in 0.740978 seconds!
Saving OBJ file: "Fidgit.obj"
Finished writing OBJ in 0.0668869 seconds
```
