#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "steganography.h"
#include "bmp_stego.h"

int bmp_encoder(const char *picture_path, char *input_text)
{
    struct BMPFileHeader file_header;
    struct DBIHeader dbi_header;
    char binary_text[MAX_BUFFER * 8];

    // read header
    FILE *picture_file = fopen(picture_path, "rb");
    fseek(picture_file, 0L, SEEK_SET);
    fread(&file_header, sizeof(file_header), 1, picture_file);
    fread(&dbi_header, sizeof(dbi_header), 1, picture_file);
    
    // write header
    FILE *encoded_picture = fopen("a_picture.bmp", "wb");
    fwrite(&file_header, sizeof(file_header), 1, encoded_picture);
    fwrite(&dbi_header, sizeof(dbi_header), 1, encoded_picture);
    /* 
    convert text to binary and check we have no compression, 24bpp and
    text bits dont exceed subpixels in image
    */
    int total_bits_text = binary_converter(input_text, binary_text);
    int total_pixels = dbi_header.biWidth * dbi_header.biHeight;
    if (total_bits_text > total_pixels * 3)
    {
        return 1;
    }
    if (dbi_header.biBitCount != 24 || dbi_header.biCompression != BI_RGB)
    {
        return 1;
    }

    // vars for modifying bits
    int padding_bytes = (dbi_header.biWidth * 3) % 4;
    int binary_text_index = 0;
    uint8_t *sub_pixel = (uint8_t *)malloc(dbi_header.biWidth * 3);
    
    //loop through each row in the image
    for (int i = 0; i < dbi_header.biHeight; i++)
    {
        // read row into subpixel array
        int sub_pixel_index = 0;
        fread(sub_pixel, 1, (dbi_header.biWidth * 3), picture_file);

        // loop through pixel
        for (int j = 0; j < dbi_header.biWidth; j++)
        {

            // loop through each subpixel
            for (int k = 0; k < 3; k++)
            {
                // check if we have no more characters to write
                if (binary_text_index < total_bits_text)
                {
                    // change the value of the sub pixel
                    sub_pixel[sub_pixel_index] = (sub_pixel[sub_pixel_index] & 0xFE) | binary_text[binary_text_index];
                    sub_pixel_index++;
                    binary_text_index++;
                }
            }
        }

        // write the new pixel row to the new file
        fwrite(sub_pixel, 1, dbi_header.biWidth * 3, encoded_picture);
        if (padding_bytes != 0)
        {
            uint8_t pad[3] = { 0 };
            fwrite(pad, 1, padding_bytes, encoded_picture);
            fseek(picture_file, padding_bytes, SEEK_CUR);
        }
    }
    free(sub_pixel);
    return 0;
}

/*
Convert input to binary
Depending on how many of these type of functions there are between
the three encoders, may add a new file call encoder/decoder helpers
or something like that
*/
int binary_converter(char *input_text, char *binary_text)
{
    char letter;
    int k = 0;
    int i = 0;

    do
    {
        letter = input_text[i];
        for (int j = 7; j >= 0; j--)
        {
            binary_text[k] = (letter >> j) & 1;
            k++;
        }
    } 
    while (input_text[i++] != '\0');
    return k;
}