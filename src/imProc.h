#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include "jpeg-9/jpeglib.h"
#define IMAGE_BUFFER 20

typedef struct __pixel_t
{
    int red;
    int green;
    int blue;
} pixel_t;

typedef struct __image_t
{
    pixel_t **matrix;
    unsigned width;
    unsigned height;
} image_t;

// Represents an object in an image.
struct image_object
{
    char key[IMAGE_BUFFER];
    image_t parent;
    image_t child;
};

// Prototypes
int genpic(const char *filename, image_t *image);
static inline int isjpg(const char *filename);
void clear_image(image_t *image);

// Initialized image.
image_t empty_image(unsigned width, unsigned height)
{
    unsigned i;
    image_t image;
    image.matrix = (pixel_t **) calloc(height, sizeof(pixel_t *));

    for (i = 0; i < height; i++)
    {
        image.matrix[i] = (pixel_t *) calloc(width, sizeof(pixel_t));
    }

    return image;
}

// Generates image from input file name. File must be of jpg format.
int genpic(const char *filename, image_t *image)
{
    if (!isjpg(filename))
        return 0;

    return 1;
}

// Boolean function checking file whether it is a jpg file.
static inline int isjpg(const char *filename)
{
    unsigned length = strlen(filename), i;

    for (i = 0; i < length; i++)
    {
        if (filename[i] == '.')
        {
            if (strcmp(filename + i + 1, "jpg") == 0 || strcmp(filename + i + 1, "jpeg") == 0)
                return 1;
        }
    }

    return 0;
}

// Clear image.
void clear_image(image_t *image)
{
    unsigned i;

    for (i = 0; i < image->height; i++)
    {
        free(image->matrix[i]);
    }

    free(image->matrix);
    image->height = 0;
    image->width = 0;
}
