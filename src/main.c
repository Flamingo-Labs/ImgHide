#include <stdio.h>
#include <string.h>
#include "encrypt.h"
#include "decrypt.h"

// Function prototypes
int parse_arguments(int argc, char *argv[], char **picture_path, char **text_path, int *mode);

int main(int argc, char *argv[])
{
    char *picture_path = NULL;
    char *text_path = NULL;  // Optional now
    int mode = 0;  // 0: unset, 1: encrypt, 2: decrypt

    if (parse_arguments(argc, argv, &picture_path, &text_path, &mode) != 0)
    {
        return 1;
    }

    if (mode == 1)
    {
        return encrypt_text(text_path, picture_path);
    }
    else
    {
        return decrypt_text(picture_path, text_path);
    }
}

int parse_arguments(int argc, char *argv[], char **picture_path, char **text_path, int *mode)
{   //Loop through the args and give values to variables needed
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--encrypt") == 0)
        {
            *mode = 1;
        }
        else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decrypt") == 0)
        {
            *mode = 2;
        }
        else if ((strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--picture") == 0) && i + 1 < argc)
        {
            *picture_path = argv[++i];
        }
        else if ((strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--text") == 0) && i + 1 < argc)
        {
            *text_path = argv[++i];
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printf("Steganography tool to hide text in images\n\n");
            printf("Usage: %s -e|--encrypt -p <image_path> [-t <text_file>]\n", argv[0]);
            printf("       %s -d|--decrypt -p <image_path> [-t <output_file>]\n", argv[0]);
            printf("\nOptions:\n");
            printf("  -e, --encrypt         Encrypt mode: hide text in image\n");
            printf("  -d, --decrypt         Decrypt mode: extract text from image\n");
            printf("  -p, --picture <path>  Path to the image (required)\n");
            printf("  -t, --text <path>     Optional: Input text file for encryption\n");
            printf("                        or output file for decryption\n");
            printf("                        If not specified for encryption, will prompt for text\n");
            printf("                        If not specified for decryption, will print to console\n");
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
        fprintf(stderr, "Error: An image file (-p) is required for both encryption and decryption\n");
        return 1;
    }

    return 0;
}
