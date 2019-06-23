#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include "jpeg-9/jpeglib.h"
#define IMAGE_BUFFER 20
#define IMAGESIZE 1024
#define IMAGEHEADER 54

typedef struct __pixel_t
{
    int red;
    int green;
    int blue;
} pixel_t;

typedef struct __image_t
{
    int *header;
    pixel_t **matrix;
    unsigned width;
    unsigned height;
} image_t;
