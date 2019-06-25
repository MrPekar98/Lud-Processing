#include "viProc.h"

// Global file for video output.
FILE *video_output;

// Prototypes
static void load_video(video_t *vid, char *filename, unsigned long frames);
static void alloc_buffer(unsigned char *** buffer, unsigned height, unsigned width);
static void read_video_data(FILE *f, unsigned char ***buffer, unsigned height, unsigned width);

// Initialises video frames.
video_t init_video(unsigned height, unsigned width, unsigned long frames, char *filename)
{
    video_t vid = {.frames = (image_t *) malloc(sizeof(image_t) * frames)};
    unsigned i, j;

    for (i = 0; i < frames; i++)
    {
        vid.frames[i].matrix = (pixel_t **) malloc(sizeof(pixel_t *) * height);
        vid.frames[i].height = height;
        vid.frames[i].width = width;
        
        for (j = 0; j < height; j++)
        {
            vid.frames[i].matrix[j] = (pixel_t *) malloc(sizeof(pixel_t) * width);
        }
    }

    load_video(&vid, filename, frames);
    return vid;
}

// Loads video into array.
static void load_video(video_t *vid, char *filename, unsigned long frames)
{
    char file_in[100];
    sprintf(file_in, "ffmpeg -i %s -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", filename);
    FILE *fin = popen(file_in, "r");
    video_output = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 352x640 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 Test/output.mp4", "w");
    unsigned i, j, k, height = vid->frames[0].height, width = vid->frames[0].width;
    unsigned char ***buffer;
    const size_t frame_size = height * width * 3;
    alloc_buffer(buffer, height, width);
    
    for (i = 0; i < frames; i++)
    {
        read_video_data(fin, buffer, height, width);

        for (j = 0; j < height; j++)
        {
            for (k = 0; k < width; k++)
            {
                vid->frames[i].matrix[j][k].red = buffer[j][k][0];
                vid->frames[i].matrix[j][k].green = buffer[j][k][1];
                vid->frames[i].matrix[j][k].blue = buffer[j][k][2];
            }
        }
    }

    fflush(fin);
    fflush(video_output);
    fclose(fin);
    fclose(video_output);
    free(buffer);
}

// Alocates memory for buffer.
static void alloc_buffer(unsigned char *** buffer, unsigned height, unsigned width)
{
    buffer = (unsigned char ***) malloc(sizeof(unsigned char **) * height);
    unsigned i, j;

    for (i = 0; i < height; i++)
    {
        buffer[i] = (unsigned char **) malloc(sizeof(unsigned char *) * width);

        for (j = 0; j < 3; j++)
        {
            buffer[i][j] = (unsigned char *) malloc(sizeof(unsigned char) * 3);
        }
    }
}

// Reads video file into buffer.
static void read_video_data(FILE *f, unsigned char ***buffer, unsigned height, unsigned width)
{
    unsigned i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            buffer[i][j][0] = fgetc(f);

            printf("%c\n", buffer[i][j][0]);

            buffer[i][j][1] = fgetc(f);
            buffer[i][j][2] = fgetc(f);
        }
    }
}
