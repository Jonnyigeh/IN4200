#include "parallel_functions.h"
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

void iso_diffusion_denoising_parallel (image *u, image *u_bar, float kappa, int iters)
{
    // Extract information from the image struct(s)
    int m = u->m;
    int n = u->n;

    int my_rank, size, above_procs, below_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get the rank of the current process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes

    
    // Copy the boundary pixels from the original image to the denoised image, as these are not computed in the diffusion algorithm
    for (int i = 0; i < m; i++) {
        u_bar->image_data[i][0] = u->image_data[i][0];
        u_bar->image_data[i][n-1] = u->image_data[i][n-1];
    }
    for (int j = 0; j < n; j++) {
        u_bar->image_data[0][j] = u->image_data[0][j];
        u_bar->image_data[m-1][j] = u->image_data[m-1][j];
    }
    // Assign memory for "halo" rows
    float *row_below = (float*)malloc(n * sizeof(float));
    float *row_above = (float*)malloc(n * sizeof(float));

    // Run the diffusion algorithm for the specified number of iterations
    // We need to communicate the halo rows between the processes for each iteration
    for (int it = 0; it < iters; it++) {
        // Define the above and below neighbouring processes
        above_procs = my_rank - 1;
        below_procs = my_rank + 1;

        // First and last process will not have above/below processes, so we send to MPI_PROC_NULL
        if (my_rank == 0) {
            above_procs = MPI_PROC_NULL;
        }
        if (my_rank == size - 1) {
            below_procs = MPI_PROC_NULL;
        }
        // Send and receive the halo rows
        MPI_Sendrecv (u->image_data[0], n, MPI_INT, above_procs, 0, row_below, n, MPI_INT, below_procs, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Sendrecv (u->image_data[m-1], n, MPI_INT, below_procs, 0, row_above, n, MPI_INT, above_procs, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Compute the rows dependent on the halo rows, for upper rows we exclude rank 0, bottom rows we exclude rank size - 1
        if (my_rank != 0) {
            int i = 0; // First row is a halo row
            for (int j = 1; j < n - 1; j++) {
                // Apply the diffusion algorithm
                u_bar->image_data[i][j] = u->image_data[i][j] + kappa * (
                    row_above[j] + u->image_data[i][j-1] - 4 * u->image_data[i][j] + u->image_data[i][j+1] + u->image_data[i+1][j]);
            }
        } 
        if (my_rank != size - 1) {
            int i = m - 1; // Last row is a halo row
            for (int j = 1; j < n - 1; j++) {
                // Apply the diffusion algorithm
                u_bar->image_data[i][j] = u->image_data[i][j] + kappa * (
                    u->image_data[i-1][j] + u->image_data[i][j-1] - 4 * u->image_data[i][j] + u->image_data[i][j+1] + row_below[j]);
            }
        }
        // Run over the image data matrix and apply the diffusion algorithm, but only the interior pixels
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                // Apply the diffusion algorithm to the pixel value
                u_bar->image_data[i][j] = u->image_data[i][j] + kappa * (
                    u->image_data[i-1][j] + u->image_data[i][j-1] - 4 * u->image_data[i][j] + u->image_data[i][j+1] + u->image_data[i+1][j]);
            }
        }
        // Swap the two images, so that the denoised image becomes the original image for the next iteration
        image *tmp = u;
        u = u_bar;
        u_bar = tmp;
        
    }
    // Free the memory allocated for the halo rows
    free(row_below);
    free(row_above);

    
}
