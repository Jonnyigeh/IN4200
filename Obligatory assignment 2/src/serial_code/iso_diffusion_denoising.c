#include "serial_functions.h"

void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters)
{
    // Extract information from the image struct(s)
    int m = u->m;
    int n = u->n;

    // Copy the boundary pixels from the original image to the denoised image, as these are not computed in the diffusion algorithm
    for (int i = 0; i < m; i++) {
        u_bar->image_data[i][0] = u->image_data[i][0];
        u_bar->image_data[i][n-1] = u->image_data[i][n-1];
    }
    for (int j = 0; j < n; j++) {
        u_bar->image_data[0][j] = u->image_data[0][j];
        u_bar->image_data[m-1][j] = u->image_data[m-1][j];
    }
    // Run the diffusion algorithm for the specified number of iterations
    for (int it = 0; it < iters; it++) {
        // Run over the image data matrix and apply the diffusion algorithm, but only the interior pixels
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                // Apply the diffusion algorithm to the pixel value
                u_bar->image_data[i][j] = u->image_data[i][j] + kappa * (u->image_data[i-1][j] + u->image_data[i][j-1] - 4 * u->image_data[i][j] + u->image_data[i][j+1] + u->image_data[i+1][j]);
            }
        }
        // Swap the two images, so that the denoised image becomes the original image for the next iteration
        image *tmp = u;
        u = u_bar;
        u_bar = tmp;
    }
}

