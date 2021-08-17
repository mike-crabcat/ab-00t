#ifdef __cplusplus
#define API extern "C"
#else
#define API
#endif

API void *MTK_Triangulation_Open(const char *filename);
API void MTK_Triangulation_Close(void * reader);
API int MTK_Triangulation_GetPoint(void * reader, int * n, double * x, double * y, double * z);
API int MTK_Triangulation_GetTriangle(void * reader, int * n, int * a, int * b, int * c);
API int MTK_Triangulation_NumPoints(void * reader);
API int MTK_Triangulation_NumTriangles(void * reader);
