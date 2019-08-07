#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "viProc.h"
#include "encoding/base64.h"
#define STRLENGTH 50

// Prototypes
void printwelcome();
void wait(unsigned seconds);
void imagemenu();
void videomenu();
int file_exists(const char *file);
void audiomenu();

// External prototypes.
extern image_t load_bmp(FILE *image);
extern void free_bmp(image_t *image);
extern void print_matrix(image_t image);
extern void write_bmp(FILE *file, image_t image);
extern video_t init_video(unsigned long frames, char *filename);

// Main function
void main()
{
    unsigned int choice;

    system("cls");
    //printwelcome();
    printf("\n1) - Image processing\n2) - Video processing\n3) - Audio processing\n\n: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            imagemenu();
            break;

        case 2:
            videomenu();
            break;

        case 3:
            audiomenu();
            break;

        default:
            printf("Invalid input\n");
            getchar();
    }
}

// Prints welcome message.
void printwelcome()
{
    char *message[] = {" o \n/|\\\n/ \\", "\\ o /\n  |  \n / \\ ", "_ o\n /\\\n| \\", "     \n ___\\o\n/)  | ", "__|  \n  \\o \n  ( \\", "\\ /\n | \n/o\\", "   |__\n o/   \n/ )   ", "     \no/__ \n|  (\\", "o _\n/\\ \n/ |"};
    unsigned i, j;

    printf("%s", message[0]);
    for (i = 0; i < 2; i++)
    {
        for (j = 1; j < 9; j++)
        {
            printf("%s\n", message[j]);
            wait(1);
            system("cls");
        }
    }
}

// Makes thread wait in specified amount of miliseconds.
void wait(unsigned seconds)
{
    time_t t = time(NULL);
    while (time(NULL) - t < seconds);
}

// Image processing menu.
void imagemenu()
{
    char path[STRLENGTH];
    printf("Path: ");
    scanf(" %s", path);

    FILE *f = fopen(path, "r");
    image_t image = load_bmp(f);

    fclose(f);
    f = fopen("new_image.bmp", "w");
    write_bmp(f, image);
    fclose(f);
}

// Video processing menu.
void videomenu()
{
    char filename[100];
    unsigned long frames;

    printf("File name: ");
    scanf("%s", filename);

    if (!file_exists(filename))
    {
        printf("File does not exist.\n");
        exit(1);
    }

    printf("Frames: ");
    scanf("%lu", &frames);

    video_t video = init_video(frames, filename);
    //print_matrix(video.frames[0]);
}

// Checks whether file exists.
int file_exists(const char *file)
{
    FILE *f = fopen(file, "r");

    if (f == NULL)
        return 0;

    fclose(f);
    return 1;
}

// Audio processing menu.
void audiomenu()
{
    
}
