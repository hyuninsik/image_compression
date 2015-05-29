#ifndef pbm_rw_pbm_h
#define pbm_rw_pbm_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h> //for memcpy

struct image_header{
    int rows;       //Image height
    int cols;       //Image width
    char format[3]; //Image format, example: P5
    int levels;     //Number of gray/each color levels
};

unsigned char *readImage(const char *file_name, unsigned long *length, struct image_header *ih);
void writeImage(const char *filename, const unsigned char *image_data, const struct image_header ih);

#endif

