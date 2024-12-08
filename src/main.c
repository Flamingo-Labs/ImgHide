// Entry point of the program handles, getting the proper commandline arguments and calling the an encoder or decoder

#include <stdio.h>
#include <string.h>
#include "encode.h"

// Function prototypes
int parse_arguments(int argc, char *argv[], char **picture_path,  int *mode);

// Parses arguments and calls the encoder or decoder 
int main(int argc, char *argv[])
{
    char *picture_path = NULL;
    int mode = 0;  // 0: unset, 1: encrypt, 2: decrypt

    if (parse_arguments(argc, argv, &picture_path, &mode) != 0)
    {
        return 1;
    }

    if (mode == 1)
    {
        return encode(picture_path);
    }
    else
    {
        return decode(picture_path);
    }
}

// Loops through the args and gives values to variables needed
int parse_arguments(int argc, char *argv[], char **picture_path, int *mode)
{   
    for (int i = 1; i < argc; i++)
    {
        if ((strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--encode") == 0) && i + 1 < argc)
        {
            *mode = 1;
            *picture_path = argv[++i];
        }
        else if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decode") == 0) && i + 1 < argc)
        {
            *mode = 2;
            *picture_path = argv[++i];
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printf("Steganography tool to hide text in images\n\n");
            printf("Usage: -e|--encode <image_path>\n");
            printf("       -d|--decode <image_path>\n");
            printf("\nOptions:\n");
            printf("  -e, --encode <path>   Encode mode: hide text and creates new image copy\n");
            printf("  -d, --decode <path>   Decode mode: extract text from image\n");
            printf("                        Requires a path to an image\n");
            printf("                        Encoding, will prompt for text\n");
            printf("                        Decoding, will print message to console\n");
            printf("  -h, --help            Show this help message\n");
            return 1;
        }
        else
        {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    // Validate arguments
    if (*mode == 0)
    {
        fprintf(stderr, "Error: Must specify either -e or -d\n");
        return 1;
    }
    if (!*picture_path)
    {
        fprintf(stderr, "Error: An image file is required for both encoding and decoding\n");
        return 1;
    }

    return 0;
}
