#ifndef SERIAL_FUNCTIONs___
#define SERIAL_FUNCTIONs___

void dijkstra_serial_v1 (int n, int s, int **w, int *d);

void dijkstra_serial_v2 (int n, int s, int *row_ptr, int *col_idx, int *val, int *d);

void read_graph_from_file_v1 (char *filename, int *n, int ***w);

void read_graph_from_file_v2 (char *filename, int *n, int **row_ptr, int **col_idx, int **val);

int find_min_index(int *d, int *visited, int n);

#endif
