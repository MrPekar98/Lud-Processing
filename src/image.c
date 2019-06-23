#include <setjmp.h>
#include <string.h>
#include "imProc.h"

// Prototypes
static image_t init_image(unsigned height, unsigned width);
static void load_header(image_t *image, FILE *file);
void free_bmp(image_t *image);

// Loads image into buffer.
image_t load_bmp(FILE *image_file)
{
    image_t image;
    load_header(&image, image_file);

    return image;
}

// Initialises image buffer.
static image_t init_image(unsigned height, unsigned width)
{
    image_t image = {.height = height, .width = width, .matrix = (pixel_t **) malloc(sizeof(pixel_t) * height)};
    image.header = (int *) malloc(sizeof(int) * IMAGEHEADER);
    unsigned i;

    for (i = 0; i < height; i++)
    {
        image.matrix[i] = (pixel_t *) malloc(sizeof(pixel_t) * width);
    }

    return image;
}

// Loads header into image.
static void load_header(image_t *image, FILE *file)
{
    unsigned i;

    for (i = 0; i < IMAGEHEADER; i++)
    {
        image->header[i] = getc(file);
    }
}

// De-allocates image.
void free_bmp(image_t *image)
{
    free(image->matrix);
    free(image->header);
}
