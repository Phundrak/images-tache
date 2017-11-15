#include "filehandling.h"
#include <stdlib.h>

uchar* readBMP(FILE *fp) {
  BITMAPFILEHEADER bitmapFileHeader;
  BITMAPINFOHEADER bitmapInfoReader;
  uchar *img;
  DWORD imageIdx = 0;
  uchar tempRGB;

  // Open filename in read binary mode
  /* fp = fopen(filename, "rb"); */
  if (!fp)
    return NULL;

  // read the file heaer
  fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);

  // verify it's a bmp file
  if (bitmapFileHeader.bfType != 0x4D42) {
    fclose(fp);
    printf("Not a BMP file.\n");
    return NULL;
  }

  // read the bitmap info header
  fread(&bitmapInfoReader, sizeof(BITMAPINFOHEADER), 1, fp);

  // move file point to the beginnig of the bitmap data
  fseek(fp, bitmapFileHeader.bOffBits, SEEK_SET);

  // allocate enough memory for the bitmap image data
  img = (uchar *)malloc(bitmapInfoReader.biSizeImage);

  // verify memory allocation
  if (!img) {
    free(img);
    fclose(fp);
    return NULL;
  }

  // read in the bitmap image data
  fread(img, bitmapInfoReader.biSizeImage, 1, fp);

  // make sure bitmap image data was read
  if (!img) {
    fclose(fp);
    return NULL;
  }

  // swap the r and b values to get RGB (bitmap is BGR)
  for(imageIdx = 0; imageIdx < bitmapInfoReader.biSizeImage; imageIdx += 3){
    tempRGB = img[imageIdx];
    img[imageIdx] = img[imageIdx + 2];
    img[imageIdx + 2] = tempRGB;
  }

  // close file and return bitmap image data
  fclose(fp);
  return img;
}
