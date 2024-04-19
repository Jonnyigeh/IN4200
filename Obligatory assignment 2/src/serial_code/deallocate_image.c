#include "serial_functions.h"
#include <stdlib.h>

void deallocate_image(image *u)
{
    for (int i = 0; i < u->m; i++)
    {
        free(u->image_data[i]); // Freeing the allocated memory for the columns in image data
    }
    free(u->image_data);    // Freeing the allocated memory for the rows in image data
}
