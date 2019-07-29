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
    video_t vid = {.frames = (image_t *) malloc(sizeof(image_t) * frames), .duration = frames};
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

// TODO: Read each image.
// Loads video into array.
static void load_video(video_t *vid, char *filename, unsigned long frames)
{
    char image_com[100], file_in[100];
    system("mkdir Data");
    sprintf(image_com, "ffmpeg -i %s Data/in%d.png", filename);
    system(image_com);

    unsigned i, j, k, height = vid->frames[0].height, width = vid->frames[0].width;
    const size_t frame_size = height * width * 3;
}

// TODO: Read each image as frame in folder Data.
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
    unsigned i, j;

    for (i = 0; i < video->duration; i++)
    {
        for (j = 0; j < video->frames[i].height; j++)
        {
            free(video->frames[i].matrix[j]);
        }

        free(video->frames[i].matrix);
    }

    free(video->frames);
}
