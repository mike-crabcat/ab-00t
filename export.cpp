#include "VulcanTriReader.h"

extern "C" {
#include "vulcan_tri_reader.h"

void *MTK_Triangulation_Open(const char *filename) {
  return new VulcanTriReader(filename);
}

void MTK_Triangulation_Close(void * reader) {
  delete static_cast<VulcanTriReader*>(reader);
}

int MTK_Triangulation_GetPoint(void * reader, int * n, double * x, double * y, double * z) {
  auto const& vertices = static_cast<VulcanTriReader*>(reader)->vertices();
  *x = vertices[*n*3+0];
  *y = vertices[*n*3+1];
  *z = vertices[*n*3+2];
  return 0;
}

int MTK_Triangulation_GetTriangle(void * reader, int * n, int * a, int * b, int * c) {
  auto const& triangles = static_cast<VulcanTriReader*>(reader)->triangles();
  *a = triangles[*n*3+0];
  *b = triangles[*n*3+1];
  *c = triangles[*n*3+2];
  return 0;
}

int MTK_Triangulation_NumPoints(void * reader) {
  return static_cast<VulcanTriReader*>(reader)->numVertices();
}

int MTK_Triangulation_NumTriangles(void * reader) {
  return static_cast<VulcanTriReader*>(reader)->numTriangles();
}

}
