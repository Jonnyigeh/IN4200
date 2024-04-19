#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../serial_part/serial_functions.h"
#include <omp.h>


int find_min_index(int *d, int *visited, int n){  // Function to locate the index of the un-visited vertex with the smallest distance from source
  int min = INT_MAX;                              // Return -1 if all vertices have been visited
  int min_index = -1;
  for (int i = 0; i < n; i++){
    if (d[i] < min && visited[i] != 1){
      min = d[i];
      min_index = i;
    }
  }
  return min_index;
}