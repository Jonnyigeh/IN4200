#include "para_functions.h"
#include "../serial_part/serial_functions.h"
#include <omp.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {
  // Check that a command line argument was provided
  if (argc != 2) {
    printf("Incorrect Usage - Provide .txt filepath for graph: %s <input_graph_file>\n", argv[0]);
    return 1;  // Indicate incorrect usage
  }
  char *filename = argv[1];  // Use the command-line argument as the input graph file
  double start, end;

  // Initialize the CRS matrix pointers and algortihm
  start = omp_get_wtime();        // Time the run to compare with the serial version
  int n1;
  int *row_ptr, *col_idx, *val;
  read_graph_from_file_v2(filename, &n1, &row_ptr, &col_idx, &val);
  int *d1 = (int *)malloc(n1 * sizeof(int));
  int s = 0;                      // Set the source vertex (for both algorithms)
  dijkstra_omp_v2(n1, s, row_ptr, col_idx, val, d1);
  end = omp_get_wtime();
  printf("Time CSR: %f\n", end-start);
  for (int i = 0; i < n1; i++)
  {
    printf("%d ", d1[i]);
  }
  printf("\n");
  free(d1);
  free(row_ptr);
  free(col_idx);
  free(val);

  // Initialize the connectivity matrix pointers and algorithm
  int n2;
  int **w;
  read_graph_from_file_v1(filename, &n2, &w);
  int *d2 = (int *)malloc(n2 * sizeof(int));
  start = omp_get_wtime();        // Time the run to compare with the serial version
  dijkstra_omp_v1(n2, s, w, d2);
  end = omp_get_wtime();
  printf("Time regular: %f\n", end-start);
  for (int i = 0; i < n2; i++)
  {
    printf("%d ", d2[i]);
  }
  printf("\n");
  free(d2);              // Free the allocated memory for d and w.
  for (int i = 0; i < n2; i++){
    free(w[i]);
  }
  free(w);  



}
