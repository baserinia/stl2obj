# STL to OBJ Geometry Converter
stl2obj is CAD utility for converting STL geometries to OBJ format. In addition,
to converting the geometry, stl2obj is capable of:
* Merging vertices;
* Filling holes and cracks; and
* Stitching single edges across surfaces.
We use a K-D tree (in this case a 3D tree) to speed up the process of searching
and merging points.
