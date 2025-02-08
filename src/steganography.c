// This file will handle figuring out the file type and calling the proper encoder or decoder for the file

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "steganography.h"
#include "bmp_stego.h"

static uint8_t file_type[4];
static FILE *picture_file;

// Will call the proper encoder depending on the format of the picture
int encode(char *picture_path)
{
	char input_text[MAX_BUFFER];
	printf("Enter passphrase to encrypt\n");
	if (fgets(input_text, MAX_BUFFER, stdin) == NULL)
	{
		return 1;
	}
	input_text[strcspn(input_text, "\n")] = '\0';

	grab_file_type(picture_path);
	if (picture_file == NULL)
	{
		return 1;
	}

	// Calls the specialized encoder based on file type
	if (compare_file_type(file_type) == 1)
	{
		return bmp_encoder(picture_file, input_text);
	}
	else if (compare_file_type(file_type) == 2)
	{
		printf("call PNG encoder");
	}
	else if(compare_file_type(file_type) == 3)
	{
		printf("call JPEG encoder");
	}
	else
	{
		printf("File not supported");
		return 1;
	}
	return 0;
}

// Will call the proper decoder depending on the format of the picture
int decode(char *picture_path)
{
	grab_file_type(picture_path);
	if (picture_file == NULL)
	{
		return 1;
	}

	// Calls the specialized encoder based on file type
	if (compare_file_type(file_type) == 1)
	{
		return bmp_decoder(picture_file);
	}
	else if (compare_file_type(file_type) == 2)
	{
		printf("call PNG encoder");
	}
	else if (compare_file_type(file_type) == 3)
	{
		printf("call JPEG encoder");
	}
	else
	{
		printf("File not supported");
		return 1;
	}

	return 0;
}

// Checks the type of file
int compare_file_type(uint8_t file_type[4])
{
	uint8_t bmp[2] = { 0x42,0x4D };
	uint8_t png[4] = { 0x89, 0x50, 0x4E, 0x47 };
	uint8_t jpeg[3] = { 0xFF, 0xD8, 0xFF };

	if (file_type[0] == bmp[0] && file_type[1] == bmp[1])
	{
		return 1;
	}
	if (
		file_type[0] == png[0] &&
		file_type[1] == png[1] &&
		file_type[2] == png[2] &&
		file_type[3] == png[3]
	)
	{
		return 2;
	}
	if (
		file_type[0] == jpeg[0] &&
		file_type[1] == jpeg[1] &&
		file_type[2] == jpeg[2]
	)
	{
		return 3;
	}

	return -1;
}

// Populate array used to check file type
void grab_file_type(char *picture_path)
{
	picture_file = fopen(picture_path, "rb");
	fread(file_type, sizeof(file_type), 1, picture_file);
}