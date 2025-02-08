#ifndef BMP_STEGO_H
#define BMP_STEGO_H

#include <stdint.h>

// Enum for compression
typedef enum
{
    BI_RGB = 0,         // No compression 
    BI_RLE8 = 1,        // 8-bit Run-Length Encoding
    BI_RLE4 = 2,        // 4-bit Run-Length Encoding
    BI_BITFIELDS = 3,   // Bitfields (used for 16/32-bit bitmaps)
    BI_JPEG = 4,        // JPEG compression
    BI_PNG = 5          // PNG compression
} Compression;

#pragma pack(push, 1)

// Holds the header data
struct BMPFileHeader 
{
    uint16_t bfType;                // File signature, BM for .bmp
    uint32_t bfSize;                // File size including the header
    uint16_t bfReserved1;           // Unused    
    uint16_t bfReserved2;           // Unused
    uint32_t bfOffset;             // Size of file header and DBI
};

// Holds the DBI data
struct DBIHeader 
{
    uint32_t biSize;               // Size of the DBI header
    int32_t biWidth;               // Amount of horizontal pixels
    int32_t biHeight;              // Amount of vertical pixels
    uint16_t biPlanes;             // Number of planes, 1 in modern systems
    uint16_t biBitCount;           // Bits per pixel, color depth
    Compression biCompression;     // Compression used
    uint32_t biSizeImage;          // Size of just the image data
    int32_t biXPelsPerMeter;       // Horizontal pixels per meter
    int32_t biYPelsPerMeter;       // Vertical pixels per meter
    uint32_t biClrUsed;            // Colors used in the color palette, not used (0) in 24bpp
    uint32_t biClrImportant;       // How many colors are important (0) if biClrUsed is 0
};

#pragma pack(pop)

int bmp_encoder(FILE *picture_file, char *input_text);
int bmp_decoder(FILE *picture_file);
int binary_converter(char *input_text, char *binary_text);
#endif