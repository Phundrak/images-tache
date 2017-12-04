#ifndef IMGTACHES_SRC_PROCESS_H_
#define IMGTACHES_SRC_PROCESS_H_

 void process(struct Image *img);
 void map_area(struct Pixel *pix, struct Image *img);
 void running_area(struct Pixel *pix, struct Image *img, struct Zone *zt);
 bool pix_to_add(struct Pixel *pix, struct Zone *zt);
 bool pix_already_in_area(struct Pixel *pix, struct Zone *zt);
 bool test_exist(struct Pixel *pix);

#endif
