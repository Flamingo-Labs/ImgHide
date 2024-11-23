#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "decode.h"

// Function prototypes
int parse_arguments(int argc, char *argv[], char **picture_path, char **text_path, int *mode);

int main(int argc, char *argv[])
{
    char *picture_path = NULL;
    char *text_path = NULL;
    int mode = 0;  // 0: unset, 1: encrypt, 2: decrypt

    if (parse_arguments(argc, argv, &picture_path, &text_path, &mode) != 0)
    {
        return 1;
    }

    if (mode == 1)
    {
        return encode(picture_path, text_path);
    }
    else
    {
        return decode(picture_path, text_path);
    }
}

int parse_arguments(int argc, char *argv[], char **picture_path, char **text_path, int *mode)
{   //Loop through the args and give values to variables needed
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
        else if ((strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--text") == 0) && i + 1 < argc)
        {
            *text_path = argv[++i];
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printf("Steganography tool to hide text in images\n\n");
            printf("Usage: -e|--encode <image_path> -t|--text <text_file>\n");
            printf("       -d|--decode <image_path> -t|--text <output_file>\n");
            printf("\nOptions:\n");
            printf("  -e, --encode <path>   Encode mode: hide text in image\n");
            printf("  -d, --decode <path>   Decode mode: extract text from image\n");
            printf("                        Requires a path to an image\n");
            printf("  -t, --text <path>     Optional: Input path to a text file for encoding\n");
            printf("                        or output file for decoding\n");
            printf("                        If not specified for encoding, will prompt for text\n");
            printf("                        If not specified for decoding, will print to console\n");
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
