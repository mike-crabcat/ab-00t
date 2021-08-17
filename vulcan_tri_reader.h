void *MTK_Triangulation_Open(const char *filename);
void MTK_Triangulation_Close(void * reader);
int MTK_Triangulation_GetPoint(void * reader, int * n, double * x, double * y, double * z);
int MTK_Triangulation_GetTriangle(void * reader, int * n, int * a, int * b, int * c);
int MTK_Triangulation_NumPoints(void * reader);
int MTK_Triangulation_NumTriangles(void * reader);
