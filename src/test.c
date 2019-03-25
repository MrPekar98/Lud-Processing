#include <assert.h>
#include "encoding/base64.h"
#include "viProc.h"
#include "auProc.h"
#define LENGTH 10

// Prototypes
void test_base64_encoding();
void test_base64_decoding();
char *tochararray(const int *arr, size_t length);

// Main test function.
void main()
{
    // List of tests.
    test_base64_encoding();
    test_base64_decoding();
}

// Tests base64 encoding.
void test_base64_encoding()
{
    const char *str = "Hello1234";
    const int encoded_test[] = {7, 30, 37, 37, 40, 53, 54, 55, 56};
    const char *encoded = encode64(str);
    unsigned i;

    for (i = 0; i < 9; i++)
    {
        assert(encoded[i] == encoded_test[i]);
    }
}

// Tests base64 decoding.
void test_base64_decoding()
{
    const int arr[] = {7, 30, 37, 37, 40, 53, 54, 55, 56};
    const char *encoded = tochararray(arr, 9);
    const char *decoded = decode64(encoded);
    const char *decoded_test = "Hello1234";
    unsigned i;

    for (i = 0; i < 9; i++)
    {
        assert(decoded[i] == decoded_test[i]);
    }
}

// Converts int array into char array. Arrays may not be longer than 10.
char *tochararray(const int *arr, size_t length)
{
    char *result = (char *) malloc(sizeof(char) * length);
    unsigned i;

    for (i = 0; i < length; i++)
    {
        result[i] = (char) arr[i];
    }

    return result;
}
