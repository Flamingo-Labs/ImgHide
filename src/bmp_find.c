#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "steganography.h"
#include "bmp_stego.h"

int bmp_decoder(FILE *picture_file)
{
	struct BMPFileHeader file_header;
	struct DBIHeader dbi_header;
	
	// Read header data and read head to make sure we are at start of image data
	fseek(picture_file, 0L, SEEK_SET);
	fread(&file_header, sizeof(file_header), 1, picture_file);
	fread(&dbi_header, sizeof(dbi_header), 1, picture_file);
	fseek(picture_file, file_header.bfOffset, SEEK_SET);

	if (dbi_header.biBitCount != 24 || dbi_header.biCompression != BI_RGB)
	{
		return 1;
	}


}
