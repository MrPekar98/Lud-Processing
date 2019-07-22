#include "viProc.h"

// Global file for output video.
FILE *video_output;

// Prototypes
static char *video_resolution(char *filename);
static unsigned video_width(char *filename);
static unsigned video_height(char *filename);
static void load_video(video_t *vid, char *filename, unsigned long frames);
static void alloc_buffer(int *** buffer, unsigned height, unsigned width);
static void read_video_data(FILE *f, image_t *frame, unsigned height, unsigned width);
void free_video(video_t *video);

// Initialises video frames.
video_t init_video(unsigned long frames, char *filename)
{
    video_t vid = {.frames = (image_t *) malloc(sizeof(image_t) * frames)};
    unsigned i, j, height = video_height(filename), width = video_width(filename);

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

// Returns video resolution as string.
static char *video_resolution(char *filename)
{
    char command[100];
    unsigned i;
    char *output = (char *) malloc(10);
    sprintf(command, "ffprobe -v error -show_entries stream=width,height -of csv=p=0:s=x %s", filename);
    FILE *read = popen(command, "r");
    fscanf(read, "%s", output);
    
    return output;
}

// Gets width of video.
static unsigned video_width(char *filename)
{
    char *res = video_resolution(filename);
    char result[5];
    unsigned i;

    for (i = 0; i < strlen(res); i++)
    {
        if (res[i] == 'x')
            break;

        result[i] = res[i];
    }

    free(res);
    return atoi(result);
}

// Gets height of video.
static unsigned video_height(char *filename)
{
    char *res = video_resolution(filename);
    char result[5];
    unsigned i, counter = 0;
    int met;

    for (i = 0; i < strlen(res); i++)
    {
        if (res[i] == 'x')
            met = 1;

        else if (met)
            result[counter++] = res[i];
    }

    free(res);
    return atoi(result);
}

// Loads video into array.
static void load_video(video_t *vid, char *filename, unsigned long frames)
{
    char file_in[100];
    sprintf(file_in, "ffmpeg -i %s -r 1 -f image2 %2d.png", filename);
    FILE *fin = popen(file_in, "r");
    //video_output = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 352x640 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 Test/output.mp4", "w");
    //video_output = popen("ffmpeg -y -f rawvideo -pixel_format gbrp -video_size 1024x768 -i - -c:v h264 -pix_fmt yuv420p video.mov", "w");
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

// De-allocates video from memory.
void free_video(video_t *video)
{
    free(video->frames);
}
