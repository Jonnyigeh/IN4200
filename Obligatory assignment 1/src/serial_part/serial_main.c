#include "serial_functions.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int main (int argc, char *argv[]) {
  // Check that a command line argument was provided
  if (argc != 2) {
    printf("Incorrect Usage - Provide .txt filepath for graph: %s <input_graph_file>\n", argv[0]);
    return 1;  // Indicate incorrect usage
  }

  char *filename = argv[1];  // Use the command-line argument as the input graph file
  double start, end;
  
  start = omp_get_wtime();  // Start the timer
  // Initialize the CRS matrix pointers
  int n1;
  int *row_ptr, *col_idx, *val;
  read_graph_from_file_v2(filename, &n1, &row_ptr, &col_idx, &val);
  int *d1 = (int *)malloc(n1 * sizeof(int));
  int s = 0;
  dijkstra_serial_v2(n1, s, row_ptr, col_idx, val, d1);
  end = omp_get_wtime();  // End the timer
  printf("Time CRS: %f\n", end-start);  // Print the time taken to run the dijkstra function
  // Print the distance array after successfully running the dijkstra function
  for (int i = 0; i < n1; i++)
  {
    printf("%d ", d1[i]);
  }
  printf("\n");
  free(row_ptr);
  free(col_idx);
  free(val);
  free(d1);


  start = omp_get_wtime();  // Start the timer
  // Initialize the connectivity matrix pointers
  int n2;
  int **w;
  read_graph_from_file_v1(filename, &n2, &w);
  int *d2 = (int *)malloc(n2 * sizeof(int));
  dijkstra_serial_v1(n2, s, w, d2);
  end = omp_get_wtime();
  printf("Time regular: %f\n", end-start);
  // Print the distance array after successfully running the dijkstra function
  for (int i = 0; i < n2; i++)
  {
    printf("%d ", d2[i]);
  }
  printf("\n");
  for (int i = 0; i < n2; i++){
    free(w[i]);
  }
  free(w);
  free(d2);
  return 0;

}
