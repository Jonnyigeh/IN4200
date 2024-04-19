#include "serial_functions.h"

void convert_image_to_jpeg(const image *u, unsigned char* image_chars)
{
    // Extract rows and column information from the image struct
    int m = u->m;
    int n = u->n;
    // Run over the image data matrix and assign pixel values from the image_data matrix to the image_chars vector
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            image_chars[i * n + j] = (unsigned char)(int)u->image_data[i][j]; // Convert the float to unsigned char, and assigns the correct pixel value from the image_data matrix to the correct "chunk" of the image_chars vector
        }
    }
}
