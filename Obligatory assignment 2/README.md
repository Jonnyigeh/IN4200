## Second obligatory assignment IN4200: High Performance Computing spring 2024

In this assignment we've implemented a de-noising algorithm named _isotropic diffusion_. This uses an iterative procedure to compute "smoother" versions of each pixel by averaging from it's nearest neighbours. The algorithm has been implemented for both serial, and parallel code. For extracting the pixelvalues from grey-scale images, we've used the simple-jpg package, which is necessary for running our programs.

Procedures to compile & run programs are present in the README.txt files in their respective folders (src/parallel_code and src/serial_code). 