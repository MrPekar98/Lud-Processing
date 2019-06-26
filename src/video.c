#include "viProc.h"

// Global file for video output.
FILE *video_output;

// Prototypes
static void load_video(video_t *vid, char *filename, unsigned long frames);
static void alloc_buffer(int *** buffer, unsigned height, unsigned width);
static void read_video_data(FILE *f, image_t *frame, unsigned height, unsigned width);

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
    const size_t frame_size = height * width * 3;
    
    for (i = 0; i < frames; i++)
    {
        read_video_data(fin, &vid->frames[i], height, width);
    }

    fflush(fin);
    fclose(fin);
}

// Reads video file into buffer.
static void read_video_data(FILE *f, image_t *frame, unsigned height, unsigned width)
{
    unsigned i, j;
    int first = fgetc(f);

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width && first >= 0; j++)
        {
            frame->matrix[i][j].red = first;
            frame->matrix[i][j].green = fgetc(f);
            frame->matrix[i][j].blue = fgetc(f);
            first = fgetc(f);
        }
    }
}
