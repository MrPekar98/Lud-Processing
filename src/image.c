#include <setjmp.h>
#include <string.h>
#include "imProc.h"

// Prototypes
static void init_image(image_t *image);
static void load_header(image_t *image, FILE *file);
void free_bmp(image_t *image);
void print_matrix(image_t image);
void write_bmp(FILE *file, image_t image);

// Loads image into buffer.
image_t load_bmp(FILE *image_file)
{
    image_t image;
    load_header(&image, image_file);
    init_image(&image);

    return image;
}

// Initialises image buffer. Width and height of image parameter must be initialised.
static void init_image(image_t *image)
{
    image->matrix = (pixel_t **) malloc(sizeof(pixel_t) * image->height);
    unsigned i;

    for (i = 0; i < image->height; i++)
    {
        image->matrix[i] = (pixel_t *) malloc(sizeof(pixel_t) * image->width);
    }
}

// Loads header into image.
static void load_header(image_t *image, FILE *file)
{
    unsigned i;

    for (i = 0; i < IMAGEHEADER; i++)
    {
        image->header[i] = getc(file);
    }

    image->height = image->header[1];
    image->width = image->header[2];
}

// De-allocates image.
void free_bmp(image_t *image)
{
    free(image->matrix);
    free(image->header);
}

// Printf image as matrix.
void print_matrix(image_t image)
{
    unsigned i, j;

    for (i = 0; i < image.height; i++)
    {
        for (j = 0; j < image.width; j++)
        {
            printf("(%d, %d, %d) ", image.matrix[i][j].red, image.matrix[i][j].green, image.matrix[i][j].blue);
        }

        printf("\n");
    }
}

// Writes bmp into file.
void write_bmp(FILE *file, image_t image)
{
    // Write header.
    unsigned i, j;

    for (i = 0; i < IMAGEHEADER; i++)
    {
        fprintf(file, "%c", (char) image.header[i]);
    }

    // Write data.
    for (i = 0; i < image.height; i++)
    {
        for (j = 0; j < image.width; j++)
        {
            fprintf(file, "%c", (char) image.matrix[i][j].blue);
            fprintf(file, "%c", (char) image.matrix[i][j].green);
            fprintf(file, "%c", (char) image.matrix[i][j].red);
        }
    }
}
