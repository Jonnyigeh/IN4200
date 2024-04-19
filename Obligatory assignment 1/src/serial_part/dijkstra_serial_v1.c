#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>
#include "serial_functions.h"
#define min(a,b) ((a) < (b) ? (a) : (b))      // Define the min function macro for usage inside the dijsktra function


void dijkstra_serial_v1 (int n, int s, int **w, int *d)
{
  int *visited = (int *)malloc(n * sizeof(int));        // Array to store which vertices has been visited
  for (int i = 0; i < n; i++) {
    visited[i] = 0;                                      // Initialize the visited array to 0
    if (w[s][i] > 0){
      d[i] = w[s][i];                                     // Initialize the distance array from connectivety matrix
    } else {
      d[i] = INT_MAX;                                     // Set the distance to infinity if no connection
    }
  }
  d[s] = 0;                                             // Set the distance to the source vertex to 0
  visited[s] = 1;                                       // Set the source vertex as visited
  int min = INT_MAX;
  int min_index;
  for (int i = 0; i < n; i++){
    min_index = find_min_index(d, visited, n);          // Find the un-visited vertex with the smallest distance from source
    if (min_index == -1){
      break;                                            // Break if all vertices reachable from current vertex have been visited
    }
    visited[min_index] = 1;                             // Set the vertex with the smallest distance as visited
    for (int j = 0; j < n; j++){
      if (w[min_index][j] > 0){
        d[j] = min(d[j], d[min_index] + w[min_index][j]);  // Update the distance array with the (new) smallest distances
      }                                                    // from the source vertex via the visited vertex
    }
  } free(visited);
}

// int main(){
//   double start, end;
//   int n;
//   int **w;
//   read_graph_from_file_v1("../../txtfiles/facebook_4039_nodes.txt", &n, &w);
//   int *d = (int *)malloc(n * sizeof(int));
//   int s = 0;
//   start = omp_get_wtime();      // Time the run to compare with parallel version
//   dijkstra_serial_v1(n, s, w, d);
//   end = omp_get_wtime();
//   printf("Time: %f\n", end-start);
//   // for (int i = 0; i < n; i++)
//   // {
//   //   printf("%d ", d[i]);
//   // }
//   // printf("\n");
//   free(d);          // Free the allocated memory for d and w.
//   for (int i = 0; i < n; i++){
//     free(w[i]);
//   }
//   free(w);
//   return 0;
// }