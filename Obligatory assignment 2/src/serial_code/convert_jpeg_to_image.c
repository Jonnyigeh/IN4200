#include "serial_functions.h"

void convert_jpeg_to_image(const unsigned char* image_chars, image *u)
{
    // Extract rows and column information from the image struct
    int m = u->m;   
    int n = u->n;
    // Run over the image data matrix and assign pixel values from the image_chars vector to the image_data matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            u->image_data[i][j] = (float)image_chars[i * n + j];         // Convert the unsigned char to float, and assigns the correct "chunk" of the image_chars vector to the correct row and column in the image_data matrix
        }
    }
}
