#include "serial_functions.h"
#include <stdlib.h>

void allocate_image(image *u, int m, int n)
{
    u->m = m; // Assigning the number of rows to the image struct
    u->n = n; // Assigning the number of columns to the image struct

    u->image_data = (float **)malloc(m * sizeof(float *)); // Memory allocation for the rows in image data
    for (int i = 0; i < m; i++)
    {
        u->image_data[i] = (float *)malloc(n * sizeof(float)); // Memory allocation for the columns in image data
    }
}
