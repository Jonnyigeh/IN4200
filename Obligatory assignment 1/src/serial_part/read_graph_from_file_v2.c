#include <stdio.h>
#include <stdlib.h>
#include "serial_functions.h"

// Define struct and compare function for qsort
typedef struct {
  int row;
  int col;
  int val;
} Data;

int compare(const void *a, const void *b){
  Data *dataA = (Data *)a;
  Data *dataB = (Data *)b;
  return dataA->row - dataB->row;
}


void read_graph_from_file_v2 (char *filename, int *n, int **row_ptr, int **col_idx, int **val)
{
  // Open the file
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    fprintf (stderr, "Error: Unable to open file %s\n", filename);
    exit (1);
  }
  char line[1000];
  int nodes, edges;
  for (int i = 0; i < 4; i++){
    fgets(line, 1000, file);
    // Check the information in line 3 in the graph file
    if (i == 2){
      sscanf(line, "# Nodes: %d Edges: %d", &nodes, &edges);
    }
  }
  // Sort the input data before creating the CRS matrix
  int size = edges;
  Data *data = (Data *)malloc(size * sizeof(Data));
  int a, b, c, i=0;

  while(fgets(line, 1000, file) != NULL){
    sscanf(line, "%d %d %d", &a, &b, &c);
    if (a == b){                      // Skip the self-connections
      continue; 
    }
    data[i].row = a;
    data[i].col = b;
    data[i].val = c;
    i++;
  }
  qsort(data, size, sizeof(Data), compare);
  // // Print the sorted data to check if it is sorted
  //   for (int i = 0; i < size; i++) {
  //     printf("%d %d %d\n", data[i].row, data[i].col, data[i].val);
  // }

  // The data is now sorted by row index, and we can easily construct the CRS matrix
  // and close the file
  fclose(file);
  *n = nodes;                           // Save the number of nodes to the n-pointer
  // Allocate memory for the 2D array
  *row_ptr = (int*)malloc((nodes + 1) * sizeof(int));  // Array to store the row pointers
  *col_idx = (int*)malloc(edges * sizeof(int));        // Array to store the column indices of the edges
  *val = (int*)malloc(edges * sizeof(int));            // Array to store the values of the edges  
  int current_row = 0;                                    // Initialize the row counter
  (*row_ptr)[0] = 0;                                   // Initialize the first row pointer
  // Initialize the row pointers

  for (int i = 0; i < edges; i++){
    if (data[i].row != current_row){
      current_row = data[i].row;
      (*row_ptr)[current_row] = i;
    }
    (*col_idx)[i] = data[i].col;
    (*val)[i] = data[i].val;
  }
  (*row_ptr)[nodes] = edges;                          // Set the last row pointer to the number of edges (i.e last element)
  free(data);                                         // Free the memory allocated for the data array 
}




// int main() {
//   int n;
//   int *row_ptr, *col_idx, *val;
//   read_graph_from_file_v2("../../txtfiles/5_nodes.txt", &n, &row_ptr, &col_idx, &val);
//   for (int i = 0; i < n+1; i++){
//     for (int j = row_ptr[i]; j < row_ptr[i+1] && j<row_ptr[n]; j++){
//       printf("%d\n", col_idx[j]);
    
//     }
//   } 
//   return 0;
// }