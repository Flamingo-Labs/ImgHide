#ifndef ENCODE_H
#define ENCODE_H

#include <stdint.h>

int compare_file_type(uint8_t file_type[4]);
int encode(const char *picture_path, const char *text_path);


#endif