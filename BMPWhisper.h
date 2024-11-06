#ifndef BMP_WHISPER_H
#define BMP_WHISPER_H

#include <stdint.h>

//Holds the header data
struct BMPFileHeader 
{
    unsigned char bfType[2];        // File signature, BM for .bmp
    uint32_t bfSize;                // File size including the header
    uint16_t bfReserved1;           // Unused    
    uint16_t bfReserved2;           // Unused
    uint32_t bfOffBits;             // Size of file header and DBI
};

//holds the DBI data
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

//enum for compression
typedef enum
{
    BI_RGB = 0,         // No compression 
    BI_RLE8 = 1,        // 8-bit Run-Length Encoding
    BI_RLE4 = 2,        // 4-bit Run-Length Encoding
    BI_BITFIELDS = 3,   // Bitfields (used for 16/32-bit bitmaps)
    BI_JPEG = 4,        // JPEG compression
    BI_PNG = 5          // PNG compression
} Compression;

#endif