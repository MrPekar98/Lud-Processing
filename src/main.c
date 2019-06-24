#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "imProc.h"
#include "encoding/base64.h"
#define STRLENGTH 50

// Prototypes
void printwelcome();
void wait(unsigned seconds);
void imagemenu();
void videomenu();
void audiomenu();

// External prototypes.
extern image_t load_bmp(FILE *image);
extern void free_bmp(image_t *image);
extern void print_matrix(image_t image);
extern void write_bmp(FILE *file, image_t image);

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
    
}

// Audio processing menu.
void audiomenu()
{
    
}
