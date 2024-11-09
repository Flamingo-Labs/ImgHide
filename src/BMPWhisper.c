#include "BMPWhisper.h"

/*We will have to do fread() on each row meaning our buffer will be the horizontal resolution of the image
  then we will have to loop through as many horizontal pixels at a maximum or until we reach the end of the
  text they want to encrypt. We will need to deal with padding */
//will handle encoding and decoding of text in a BMP file
//Will have to calculate if picture can hold the text
//Will need to call fseek to populate the file header struct as we called fread in encode.c
