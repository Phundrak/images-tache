#include "utilities.h"

bool pix_is_border(struct Image *img, struct Pixel *pix, struct Zone *z){
	Pixel *p;
	if ((*pix).x < (*img).sizeX + 1){
		p = pix_at_img(img , (*pix).x + 1, (*pix).y);
		if (strcomp(&p->zone->R, &z->R) == true)
			return true;
		if (strcomp(&p->zone->G, &z->G) == true)
			return true;
		if (strcomp(&p->zone->B, &z->B) == true)
			return true;
	}
	if ((*pix).x > 0){
		p = pix_at_img(img , pix->x - 1, pix->y);
		if (strcomp(&p->zone->R, &z->R) == true)
			return true;
		if (strcomp(&p->zone->G, &z->G) == true)
			return true;
		if (strcomp(&p->zone->B, &z->B) == true)
			return true;
	}
	if ((*pix).y < (*img).sizeY + 1){
		p = pix_at_img(img , pix->x, pix->y + 1);
		if (strcomp(&p->zone->R, &z->R) == true)
			return true;
		if (strcomp(&p->zone->G, &z->G) == true)
			return true;
		if (strcomp(&p->zone->B, &z->B) == true)
			return true;
	}
	if ((*pix).y > 0){
		p = pix_at_img(img , pix->x, pix->y - 1);
		if (strcomp(&p->zone->R, &z->R) == true)
			return true;
		if (strcomp(&p->zone->G, &z->G) == true)
			return true;
		if (strcomp(&p->zone->B, &z->B) == true)
			return true;
	}
	return false;
}

void put_pix_color(struct Pixel *pix, char r, char g, char b){
	(*pix->R) = r;
	(*pix->G) = g;
	(*pix->B) = b;
}

void black_border(struct Image *img, struct Zone *z){
	int y, x;
	
	for (y = 0; y < (*img).sizeY; y++){
		for (x = 0; x < (*img).sizeX; x++){
			if (pix_is_border(img, pix_at_img(img, x, y), z) == true)
				put_pix_color(pix_at_img(img, x, y), 0, 0, 0);
		}
	}
}
