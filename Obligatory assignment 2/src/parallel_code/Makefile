CC = mpicc
CFLAGS = -O2 -g
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ = parallel_main
SRCS = ../serial_code/allocate_image.c ../serial_code/deallocate_image.c ../serial_code/convert_image_to_jpeg.c ../serial_code/convert_jpeg_to_image.c iso_diffusion_denoising_parallel.c parallel_main.c
OBJS = $(SRCS:.c=.o)

all: simple-jpeg $(PROJ)

$(PROJ): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@.exe $(LDFLAGS)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

obj-clean:
	$(RM) *.o

exec-clean:
	$(RM) $(PROJ)

autosave-clean:
	$(RM) *~

clean:
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
	$(MAKE) -C ../simple-jpeg clean
