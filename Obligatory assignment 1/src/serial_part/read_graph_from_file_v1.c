#include <stdio.h>
#include <stdlib.h>
#include "serial_functions.h"

void read_graph_from_file_v1 (char *filename, int *n, int ***w)
{
  // Open the file
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    fprintf(stderr, "Error: Unable to open file %s\n", filename);
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
  *n = nodes;                           // Save the number of nodes to the n-pointer
  int rows = nodes;                     // Initialize parameters for the connectivity matrix
  int columns = nodes;
  *w = malloc(rows * sizeof(int *));    // Allocate memory for the 2D array
  for (int i = 0; i < rows; i++) {
      (*w)[i] = malloc(columns * sizeof(int));
  }
  int unconnected = -1;                  // Initialize the w-array to -1 for un-connected vertices
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < columns; j++){
      (*w)[i][j] = unconnected;
    }
  }

  // Read the vertex connectivety information from .txt to the pre-initialised w-array (with -1 values for unconnected vertices)
  int a, b, c;                              // Save the vertex info to slice w-array
  while (fgets(line, 1000, file) != NULL){
    // Read from each line, and write the vertex connectivety information to the w-array
    sscanf(line, "%d %d %d", &a, &b, &c);   // Assume equal spacing between numbers (1 whitespace)
    if (a == b){                            // Skip the self-connections
      continue;
    }
    (*w)[a][b] = c;
    
  }
  fclose(file);    // Close the file
}

// int main (int nargs, char **args)
// {
//   int n;
//   int **w;
//   read_graph_from_file_v1("../../5_nodes.txt", &n, &w);     // Check that the function works as intended
//   for (int i = 0; i < n; i++){
//     for (int j = 0; j < n; j++){
//       printf("%d ", w[i][j]);
//     }
//     printf("\n");
//   }
//   return 0;
// }