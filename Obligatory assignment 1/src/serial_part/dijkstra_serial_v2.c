#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>
#include "serial_functions.h"
#define min(a,b) ((a) < (b) ? (a) : (b))      // Define the min function macro for usage inside the dijsktra function


void dijkstra_serial_v2 (int n, int s, int *row_ptr, int *col_idx, int *val, int *d)
{
  int *visited = (int *)malloc(n * sizeof(int));        // Array to store which vertices has been visited
  for (int i = 0; i < n; i++){
    visited[i] = 0;                                     // Initialize the visited array to 0
    d[i] = INT_MAX;                                     // Set the distance to infinity if no connection
  }
  for (int i = row_ptr[s]; i < row_ptr[s+1]; i++){
    d[col_idx[i]] = val[i];                             // Initialize, and overwrite, the distance array from connectivety matrix
  }
  visited[s] = 1;                                       // Set the source vertex as visited
  d[s] = 0;                                             // Set the distance to the source vertex to 0
  int min = INT_MAX;
  int min_index = -1;
  for (int i=0; i<n;i++){
    min_index = find_min_index(d, visited, n);
    if (min_index == -1){
      break;
    } visited[min_index] = 1;
    for (int j = row_ptr[min_index]; j < row_ptr[min_index+1] && j < row_ptr[n]; j++){
      d[col_idx[j]] = min(d[col_idx[j]], d[min_index] + val[j]);
    }
  } free(visited);
}

// int main(){
//   double start, end;
//   int n;
//   int *row_ptr, *col_idx, *val;
//   read_graph_from_file_v2("../../txtfiles/facebook_4039_nodes.txt", &n, &row_ptr, &col_idx, &val);
//   printf("n: %d\n", n);
//   int *d = (int *)malloc(n * sizeof(int));
//   int s = 0;
//   start = omp_get_wtime();      // Time the run to compare with parallel version
//   dijkstra_serial_v2(n, s, row_ptr, col_idx, val, d);
//   end = omp_get_wtime();
//   printf("Time: %f\n", end-start);
//   // for (int i = 0; i < n; i++)
//   // {
//   //   printf("%d ", d[i]);
//   // }
//   // printf("\n");
//   free(d);
//   free(row_ptr);
//   free(col_idx);
//   free(val);
//   return 0;
// }