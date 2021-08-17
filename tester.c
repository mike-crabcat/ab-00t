#include <stdio.h>
#include <stdlib.h>
#include "vulcan_tri_reader.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("missing filename\n");
    return 1;
  }
  char *filename = argv[1];

  void *t = MTK_Triangulation_Open(filename);

  int point_count = MTK_Triangulation_NumPoints(t);
  printf("point_count = %d\n", point_count);

  int triangle_count = MTK_Triangulation_NumTriangles(t);
  printf("triangle_count = %d\n", triangle_count);

  for (int i = 0; i < point_count; i ++) {
    double x, y, z;
    int res = MTK_Triangulation_GetPoint(t, &i, &x, &y, &z);
    if (res != 0) {
      printf("error fetching point %d\n", i);
      exit(1);
    }
    printf("fetching point %d, x = %f, y = %f, z = %f\n", i, x, y, z);
  }

  for (int j = 0; j < triangle_count; j ++) {
    int v1, v2, v3;
    int res = MTK_Triangulation_GetTriangle(t, &j, &v1, &v2, &v3);
    if (res != 0) {
      printf("error fetching triangle %d\n", j);
      exit(1);
    }
    printf("fetching triangle %d, v1 = %d, v2 = %d, v3 = %d\n", j, v1, v2, v3);
  }
}
