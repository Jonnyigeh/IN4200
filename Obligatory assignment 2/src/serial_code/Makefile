CC = gcc
CFLAGS = -O2 -g
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ = serial_main
SRCS = allocate_image.c deallocate_image.c convert_image_to_jpeg.c convert_jpeg_to_image.c iso_diffusion_denoising.c serial_main.c
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
