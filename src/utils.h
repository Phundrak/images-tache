#ifndef IMAGESTACHE_SRC_UTILS_H_
#define IMAGESTACHE_SRC_UTILS_H_

typedef unsigned char uchar;
typedef unsigned long DWORD;
typedef unsigned short WORD;

typedef struct tagBITMAPFILEHEADER {
  WORD bfType;      // specifies the file type
  DWORD bfSize;     // specifies the size in bytes of the bitmap file
  WORD bfReserved1; // reserved; must be 0
  WORD bfReserved2; // reserved; must be 0
  DWORD bOffBits;   // species the offset in bytes from the bitmapfileheader to
                    // the bitmap bits
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;         // specifies the number of bytes required by the struct
  long biWidth;         // specifies width in pixels
  long biHeight;        // species height in pixels
  WORD biPlanes;        // specifies the number of color planes, must be 1
  WORD biBitCount;      // specifies the number of bit per pixel
  DWORD biCompression;  // spcifies the type of compression
  DWORD biSizeImage;    // size of image in bytes
  long biXPelsPerMeter; // number of pixels per meter in x axis
  long biYPelsPerMeter; // number of pixels per meter in y axis
  DWORD biClrUsed;      // number of colors used by th ebitmap
  DWORD biClrImportant; // number of colors that are important
} BITMAPINFOHEADER;

struct Zone;
typedef struct Zone Zone;
typedef struct Zone *Zone_t;
struct Pixel;
typedef struct Pixel Pixel;
typedef struct Pixel *Pixel_t;
struct Image;
typedef struct Image Image;
typedef struct Image *Image_t;

struct Pixel {
  uchar r;
  uchar g;
  uchar b;
  int x;
  int y;
  Zone_t zone; // zone in which the pixel is
};

struct Image {
  int width;
  int height;
  Pixel_t pixels;
};

struct Zone {
  unsigned long id; // ID of the zone
  uchar R;
  uchar G;
  uchar B;
  Pixel_t pixels; // list of pixels within the zone
};

void free_image(Image_t);

#endif /* IMAGESTACHE_SRC_UTILS_H_ */
