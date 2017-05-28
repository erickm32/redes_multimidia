// To get a header file for this, either cut and paste the header,
// or create jo_jpeg.h, #define JO_JPEG_HEADER_FILE_ONLY, and
// then include jo_jpeg.c from it.

// Returns false on failure
extern bool jo_write_jpg(const char *filename, const void *data, int width, int height, int comp, int quality);
