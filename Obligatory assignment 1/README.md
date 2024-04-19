## First obligatory assignment IN4200: High Performance Computing spring 2024

In this assignment we've implemented the Dijkstra's algorithm to compute shortest path from source vertex to all other vertices in a graph tree. This has been done for 
two separate cases: When the graph tree is presented as a dense matrix, and when the graph tree is presented as a sparse CSR matrix.
These two cases are also done both using serialized code, and parallelized code (using the OpenMP library).

Procedures to compile & run programs are present in the README.txt files in their respective folders (src/omp_part and src/serial_part). 

Comments on the implementation:
In creating the CSR matrix, the qsort algortihm is used to sort the graph dataset, which introduces some overhead - this may result (for various size datasets) 
in skewed runtimes for the dense/sparse matrix case. To show properly the increase in performance when doing parallel computing, one should move the timers around the
Dijkstra algorithm function calls. This is also an area available for improvement, to make the algorithm work even for unsorted datasets - to prevent this overhead.