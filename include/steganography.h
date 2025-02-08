#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H
#define MAX_BUFFER 281
#include <stdint.h>

int compare_file_type(uint8_t file_type[4]);
int encode(char *picture_path);
int decode(char *picture_path);
void grab_file_type(char *picture_path);

#endif