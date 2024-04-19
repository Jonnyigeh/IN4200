To compile the code, use the following command:
```console
   gcc serial_main.c read_graph_from_file_v2.c read_graph_from_file_v1.c dijkstra_serial_v1.c dijkstra_serial_v2.c find_min_index.c -fopenmp -o main
```
The -fopenmp flag to run the timer to compare runtimes of both regular matrix and CSR matrix version. Will output to main.

To run the code, use the following command:
```console
   ./main <file_path to .txt file with graph>
```
   Available filepaths for testing: 
   1. "../../txtfiles/5_nodes.txt"
   2. "../../txtfiles/congress_475_nodes.txt"
   3. "../../txtfiles/facebook_4039_nodes.txt"
