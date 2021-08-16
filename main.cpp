#include <iomanip>
#include <ios>
#include <iostream>

#include "VulcanTriReader.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " filename" << std::endl;
    return 1;
  }

  char *filename = argv[1];

  std::cerr << "opening " << filename << std::endl;

  VulcanTriReader reader(filename);

  int numVertex, numTriangles;
  reader.readHeader(numVertex, numTriangles);

  std::cerr << "vertex " << numVertex << " triangles " << numTriangles
            << std::endl;

  double *vertices = new double[numVertex * 3];
  reader.readVertexBuffer(vertices, sizeof(double) * numVertex * 3);

  std::cout << std::fixed << std::setprecision(3);
  for (size_t i = 0; i < numVertex; i++) {
    std::cout << vertices[i * 3 + 0] << " "
              << vertices[i * 3 + 1] << " "
              << vertices[i * 3 + 2] << std::endl;
  }

  uint32_t *triangles = new uint32_t[numTriangles * 3];
  reader.readTriangleBuffer(triangles, sizeof(uint32_t) * numTriangles * 3);

  for (size_t i = 0; i < numTriangles; i++) {
    std::cout << triangles[i * 3 + 0] << " " << triangles[i * 3 + 1] << " "
              << triangles[i * 3 + 2] << std::endl;
  }

  delete vertices;
  delete triangles;
}
