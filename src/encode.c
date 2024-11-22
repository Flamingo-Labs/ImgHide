#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "encode.h"
#include "BMPHide.h"

#define MAX_BUFFER 51
//If no input file specified, grab user input
/*Make sure to verify that a the user has properly ended the string(check for \0) otherwise inform them
input may have been cut off*/
//This file will handle figuring out the file type and calling the proper encrypter for the file type
// Remove trailing newline if present can be done like so input_text[strcspn(input_text, "\n")] = "\0";

int encode(const char *picture_path, const char *text_path)
{
	uint8_t file_type[4];
	char input_text[MAX_BUFFER];

	//If text path wasnt provided get user input
	if (text_path == NULL)
	{
		printf("Enter passphrase to encrypt\n");
		if (fgets(input_text, MAX_BUFFER, stdin) == NULL)
		{
			return 1;
		}
		input_text[strcspn(input_text, "\n")] = "\0";
	}
	
	FILE *picture_file = fopen(picture_path, "rb");
	fread(file_type,sizeof(file_type),1,picture_file);
	
	//calls the specialized encoder based on file type
	if (compare_file_type(file_type) == 1)
	{
		printf("call BM encoder");
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
	}
	return 0;
}

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

