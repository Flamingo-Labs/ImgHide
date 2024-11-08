#include "encrypt.h"

//If no input file specified, grab user input
/*Make sure to verify that a the user has properly ended the string(check for \0) otherwise inform them
input may have been cut off*/
//This file will handle figuring out the file type and calling the proper encrypter for the file type
// Remove trailing newline if present can be done like so input_text[strcspn(input_text, "\n")] = "\0";

int encrypt_text(const char *picture_path, const char *text_path)
{
	return 0;
}