#include "../serial_code/serial_functions.h"
#include "parallel_functions.h"
#include <mpi.h>
/* other needed header files */
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
  int m, n, c, iters;
  int my_m, my_rank, num_procs;
  float kappa;
  image u, u_bar;
  unsigned char *image_chars, *my_image_chars;
  char *input_jpeg_filename, *output_jpeg_filename;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num_procs);


  /* read from command line: kappa, iters, input_jpeg_filename, output_jpeg_file name 
    This is only done by the main process (rank 0)                                  */
  if (my_rank==0) {
    if (argc != 5) {
      printf("Wrong input. Please provide the following arguments: kappa, iters, input_jpeg_filename, output_jpeg_filename\n");
      exit(1);
      }
  else {
    kappa = atof(argv[1]);
    iters = atoi(argv[2]);
    input_jpeg_filename = argv[3];
    output_jpeg_filename = argv[4];
    }
  }
  
  /* Extract the values of m, n and also the image pixel arrays */
  if (my_rank==0) {
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    // allocate_image (&whole_image, m, n);
    printf("Rank %d: kappa = %f, iters = %d, dimensions: m = %d, n = %d\n", my_rank, kappa, iters, m, n);
  }

  // Cast the m, n, iters, and kappa variables to from root to all MPI subprocesses.
  MPI_Bcast (&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (&iters, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (&kappa, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

  /* 1D horizontal decomposition of the m x n pixels evenly among the MPI processes */
  /* If there is a neighbor from below, allocate one more row; Same if there is neighbor from above */
  int *sendcounts = (int *)malloc(num_procs * sizeof(int)); // Number of elements to send to each process, needed for scatterv
  int *displacement = (int *)malloc(num_procs * sizeof(int)); // Displacement of the elements to send to each process, needed for scatterv
  int *row_counts = (int *)malloc(num_procs * sizeof(int)); // Number of rows for each process, needed for scatterv
  int n_rows = m / num_procs; // Number of rows per process
  int n_extra_rows = m % num_procs; // Number of extra rows

  // Find the number of rows for each process
  for (int i = 0; i < num_procs; i++) {
    row_counts[i] = n_rows;
    if (i < n_extra_rows) {
      row_counts[i]++;      // Add extra row to the first n_extra_rows processes
    }
    sendcounts[i] = row_counts[i] * n;  // Number of elements to send to each process
  }
  my_m = row_counts[my_rank]; // Number of rows for the current process
  
  // Find the displacement for each process
  displacement[0] = 0;  // Displacement for the first process
  for (int i = 1; i < num_procs; i++) {
    displacement[i] = displacement[i - 1] + row_counts[i - 1] * n;  // Displacement for the rest of the processes, for the 1D horizontal decomposition
  }
  
  allocate_image (&u, my_m, n);
  allocate_image (&u_bar, my_m, n);
  my_image_chars = (unsigned char*)malloc(my_m * n * sizeof(unsigned char));


  /* each process asks process 0 for a partitioned region */
  /* of image_chars and copy the values into u */
  // Scatter the image_chars array to all processes
  MPI_Scatterv (image_chars, sendcounts, displacement, MPI_UNSIGNED_CHAR, my_image_chars, sendcounts[my_rank], MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

  // Convert the partitioned image_chars to image struct, and apply the diffusion algorithm
  convert_jpeg_to_image (my_image_chars, &u);
  iso_diffusion_denoising_parallel (&u, &u_bar, kappa, iters);

  /* each process sends its resulting content of u_bar to process 0 */
  /* process 0 receives from each process incoming values and */
  /* copy them into the designated region of struct whole_image */

  // Convert the u_bar image struct to a 1D array prior to gathering, then we do not need to write to the whole_image struct
  convert_image_to_jpeg(&u_bar, my_image_chars);

  // Gather the u_bar image data from all processes to the whole_image struct
  MPI_Gatherv (my_image_chars, sendcounts[my_rank], MPI_UNSIGNED_CHAR, image_chars, sendcounts, displacement, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

  // Free the memory allocated for the arrays used in the scatterv and gatherv functions
  free (sendcounts);
  free (displacement);
  free (row_counts);


  if (my_rank==0) {
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
  }

  // Free the memory allocated for the image structs and the 1D arrays
  deallocate_image (&u);
  deallocate_image (&u_bar);
  free(image_chars);
  free(my_image_chars);

  MPI_Finalize ();
  return 0;
}