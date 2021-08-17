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

  int numVertices = reader.numVertices();
  int numTriangles = reader.numTriangles();

  std::cerr << "vertex " << numVertices << " triangles " << numTriangles
            << std::endl;

  std::cout << std::fixed << std::setprecision(3);
  for (size_t i = 0; i < numVertices; i++) {
    std::cout << reader.vertices()[i * 3 + 0] << " "
              << reader.vertices()[i * 3 + 1] << " "
              << reader.vertices()[i * 3 + 2] << std::endl;
  }

  for (size_t i = 0; i < numTriangles; i++) {
    std::cout << reader.triangles()[i * 3 + 0] << " "
              << reader.triangles()[i * 3 + 1] << " "
              << reader.triangles()[i * 3 + 2] << std::endl;
  }
}
