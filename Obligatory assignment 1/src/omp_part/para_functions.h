#ifndef PARA_FUNCTIONs___
#define PARA_FUNCTIONs___

void dijkstra_omp_v1 (int n, int s, int **w, int *d);

void dijkstra_omp_v2 (int n, int s, int *row_ptr, int *col_idx, int *val, int *d);

#endif
