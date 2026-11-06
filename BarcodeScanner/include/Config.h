/*
 * File    : Config.h
 * Purpose : Shared constants (array sizes) used by all classes.
 * Why     : We use fixed-size arrays instead of vectors, so every member
 *           must agree on the maximum sizes.
 */
#ifndef CONFIG_H
#define CONFIG_H

const int MAX_WIDTH = 600;  // max image width in pixels
const int MAX_HEIGHT = 200;  // max image height in pixels
const int MAX_ENCODED_LEN = 200;  // max length of encoded barcode string
const int MAX_RUNS = 200;  // max number of bars/spaces in one scan
const int BMP_HEADER_SIZE = 54;   // 14 bytes file header + 40 bytes DIB header

#endif