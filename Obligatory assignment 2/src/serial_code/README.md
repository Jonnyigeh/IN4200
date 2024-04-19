## Serial code implementation

### Content
This directory holds the implementation for the serial program.
- serial_functions.h: Definition of header files needed for the main program to run.
- convert_image_to_jpeg.c, convert_jpeg_to_image.c, deallocate_image.c, allocate_image.c: Helper functions to the program.
- serial_main.c: Main program where all the magic happens.

### Summary of program
The denoising algorithm works by smoothing out each pixel value, by averaging from its nearest neighbours. This is done by looping over all the interior pixels, while keeping the outer row/column constant. 
A grey-scale image is necessary for the program to work properly, with decent dimensions (as to now cause memory-problems), and the image is read into the program, converted into image (a struct) so we can perform denoising, and then converted back and exported to JPEG. All this mappens in serial_main.c and all the helper functions are declared in the header file serial_functions.h

### Compiling & running the program
The program is easily compiled using 
```console
make parallel_main
```
and then it can be ran, with proper parameters $\kappa$, number of iterations, infile, outfile (in that order) - also stating how many cores should be used as
```console
mpirun -np 4 0.1 25 \path\to\infile.jpg \path\to\outfile.jpg
```
where this example uses 4 cores, $\kappa=0.1$ and 25 iterations. 