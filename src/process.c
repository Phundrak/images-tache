#include "utilities.h"
#include <stdio.h>
#define TOLERANCE 15


bool test_exist(struct Pixel *pix){
	if(!pix->zone)
		return false;
	return true;
}


bool pix_already_in_area(struct Pixel *pix, struct Zone *zt){
	return pix->zone == zt;
}

bool pix_to_add(struct Pixel *pix, struct Zone *zt){
	int diff_R, diff_G, diff_B;
	diff_R = ((abs((int)(*zt).R - (int)(*pix).R)) * 100 / 255);
	diff_G = ((abs((int)(*zt).G - (int)(*pix).G)) * 100 / 255);
	diff_B = ((abs((int)(*zt).B - (int)(*pix).B)) * 100 / 255);
	return (((diff_R + diff_G + diff_B) / 3) <= TOLERANCE);
}

void running_area(struct Pixel *pix, struct Image *img, struct Zone *zt){
	PDEB("debut du running area\n");
	if (test_exist(pix)){
		PDEB("test_exist de running_area ne segfault pas\n");
		if (pix_already_in_area(pix, zt)){
			DEBUG {
        printf("x = %lu\n", (*pix).x);
        printf("y = %lu\n", (*pix).y);
        printf("sizeX = %lu\n", (*img).sizeX);
        printf("sizeY = %lu\n", (*img).sizeY);
        printf("x - 1 = %lu\n", (*pix).x - 1);
        printf("x + 1 = %lu\n", (*pix).x + 1);
        printf("y - 1 = %lu\n", (*pix).y - 1);
        printf("y + 1 = %lu\n", (*pix).y + 1);
      }
			if ((*pix).x + 1 < (*img).sizeX && (*pix).y < (*img).sizeY){
				PDEB("lacement de runnig_area avec x + 1\n");
				running_area(pix_at_img(img, pix->x + 1, pix->y), img, zt);
			}
			if ((*pix).y + 1 < (*img).sizeY && (*pix).x < (*img).sizeX){
				PDEB("lacement de runnig_area avec y + 1\n");
				running_area(pix_at_img(img, pix->x, pix->y + 1), img, zt);
			}
			if ((*pix).x - 1 < (*img).sizeX && (*pix).y < (*img).sizeY){
			  PDEB("lacement de runnig_area avec x - 1\n");
				running_area(pix_at_img(img, pix->x - 1, pix->y), img, zt);
			}
			if ((*pix).y - 1 < (*img).sizeY && (*pix).x < (*img).sizeX){
			  PDEB("lacement de runnig_area avec y - 1\n");
				running_area(pix_at_img(img, pix->x, pix->y - 1), img, zt);
			}
		}
		else
			return;
	}
	if (pix_to_add(pix, zt)){
	  PDEB("pix_to_add ne segfault\n");
		zone_add_pix(zt, pix);
	  PDEB("zone_add_pix ne segfault pas\n");
		running_area(pix, img, zt);
	}
}

void map_area(struct Pixel *pix, struct Image *img){
	struct Zone *zt;

  PDEB("avant la creation de la zone\n");
	zt = new_zone(img,pix);
  PDEB("apres la creation de la zone\n");
  PDEB("avant l ajout de la zone a l image\n");
	img_add_zone(img, zt);
  PDEB("apres l ajout de la zone a l image\n");
	running_area(pix, img, zt);
  PDEB("fin running_area\n");
}

void process(struct Image *img){
	unsigned long x, y;
  PDEB("debut du parcour du tableau\n");
	for(y = 0; y < (*img).sizeY; y++){
	  PDEB("parcoure de la ligne %lu : \n", y);
		for(x = 0; x < (*img).sizeX; x++){
		  PDEB("parcour du pixel %lu : \n", x);
			if (test_exist(pix_at_img(img,x,y)) == false){
			  PDEB("test_exist ne segfault pas\n");
				map_area(pix_at_img(img, x, y), img);
			  PDEB("fin du mapping\n");
			}
		}
	}
}
