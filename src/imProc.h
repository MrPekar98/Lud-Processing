#include <stdlib.h>

// Represents an object in an image.
struct image_object
{

};

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

// Prototypes
void clear_image(image_t *image);

// Initialized image.
image_t default_image(unsigned width, unsigned height)
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
