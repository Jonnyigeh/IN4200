To compile the code, use the following command:
   > gcc omp_main.c dijkstra_omp_v1.c dijkstra_omp_v2.c ../serial_part/read_graph_from_file_v1.c ../serial_part/read_graph_from_file_v2.c ../serial_part/find_min_index.c -fopenmp -o main

Will output to main. Necessary to include the files from the serial_part folder for processing graph .txt files

To run the code, use the following command:
   ./main <file_path to .txt file with graph>

   Available filepaths for testing: 
   1. "../../txtfiles/5_nodes.txt"
   2. "../../txtfiles/congress_475_nodes.txt"
   3. "../../txtfiles/facebook_4039_nodes.txt"
