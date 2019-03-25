#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define ALPHA_BEG 65
#define ALPHA_LIM 122
#define NUM_BEG 48
#define NUM_LIM 57
#define BASE_NUM_BEG 52
#define BASE_ALPHA_BEG 0

// Prototypes
char *decode64(const char *str);

// Encodes string into base64.
char *encode64(const char *str)
{
    size_t length = strlen(str);
    unsigned i;
    char *result = (char *) malloc(sizeof(char) * length);

    for (i = 0; i < length; i++)
    {
        if (isalpha(str[i]))
            result[i] = str[i] - ALPHA_BEG;

        else if (isdigit(str[i]))
            result[i] = str[i] - NUM_BEG + BASE_NUM_BEG;

        else
            return NULL;
    }

    return result;
}

// Decodes base64 string into base 256.
char *decode64(const char *str)
{
    size_t length = strlen(str);
    char *result = (char *) malloc(sizeof(char) * length);
    unsigned i;

    for (i = 0; i < length; i++)
    {
        if (str[i] < BASE_NUM_BEG)
            result[i] = str[i] + ALPHA_BEG;

        else if (str[i] >= BASE_NUM_BEG && str[i] <= 61)
            result[i] = str[i] - BASE_NUM_BEG + NUM_BEG;

        else
            return NULL;
    }

    return result;
}
