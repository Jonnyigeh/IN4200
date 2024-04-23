## Parallelization using MPI (Message Passing Interface)

### Contents
This directory holds the implementation for the parallel program
- parallel_functions.h: Header file for the program (calls to the header files in serial_functions.h).
- iso_diffusion_denoising_parallel.c: The parallelized version of the denoising algorithm.
- parallel_main.c: Main program where all the magic happens.

### Summary of parallelization
Here we've parallelized our program using MPI - by partitioning the image into chunks of pixel rows, so that each subprocess handles it own set of rows. 
Since each pixel needs it's nearest neighbours in the denoising algorithm, we need to communicate across processes the upper/lower rows in between each iteration. For this, we've made halo rows to store the incoming/outgoing messages. After running the algorithm, each process sends their respective "cleaned" rows to the main process, which gathers into the bigger image - and subsequently writes it to JPEG.

### Compiling & running the program
The program is easily compiled using 
```console
make parallel_main
```
and then it can be ran, with proper parameters $\kappa$, number of iterations, infile, outfile (in that order) - also stating how many cores should be used as
```console
mpirun -np 4 ./parallel_main.exe 0.1 25 \path\to\infile.jpg \path\to\outfile.jpg
```
where this example uses 4 cores, $\kappa=0.1$ and 25 iterations. 
