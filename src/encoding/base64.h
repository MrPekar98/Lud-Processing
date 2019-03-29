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
static inline char *decode64(const char *str);

// Encodes string into base64.
static inline char *encode64(const char *str)
{
    size_t length = strlen(str);
    unsigned i;
    char *result = (char *) malloc(sizeof(char) * length);

    for (i = 0; i < length; i++)
    {
        if ((str[i] >= ALPHA_BEG && str[i]) || (str[i] >= NUM_BEG && str[i] <= NUM_LIM))
            result[i] = str[i] - NUM_BEG;

        else
            return NULL;
    }

    return result;
}

// Decodes base64 string into base 256.
static inline char *decode64(const char *str)
{
    size_t length = strlen(str);
    char *result = (char *) malloc(sizeof(char) * length);
    unsigned i;

    for (i = 0; i < length; i++)
    {
        if (str[i] >= 0 && str[i] <= ALPHA_LIM - NUM_BEG)
            result[i] = str[i] + NUM_BEG;

        else
            return NULL;
    }

    return result;
}
