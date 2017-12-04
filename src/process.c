#include "utilities.h"
#include <stdio.h>
#define TOLERANCE 15


//la fonction test si le pixel appartien a une Zone
bool test_exist(struct Pixel *pix){
	if(!pix->zone)
		return false;
	return true;
}


//la fonction test si le pixel appartien deja a la zone en argument
bool pix_already_in_area(struct Pixel *pix, struct Zone *zt){
	if ((pix->zone->R == zt->R) && (pix->zone->G == zt->G) && (pix->zone->B == zt->B))
		return true;
	return false;
}

//la fonction teste si le pixel appartien a la tolerance de la zone
bool pix_to_add(struct Pixel *pix, struct Zone *zt){
	int diff_R, diff_G, diff_B;
	diff_R = ((abs((int)(*zt).R - (int)(*pix).R)) * 100 / 255);
	diff_G = ((abs((int)(*zt).G - (int)(*pix).G)) * 100 / 255);
	diff_B = ((abs((int)(*zt).B - (int)(*pix).B)) * 100 / 255);
	return (((diff_R + diff_G + diff_B) / 3) <= TOLERANCE);
}

//la fonction parcour les pixel adjacant et les ajoute a la 
//zone si il font parti de sa tolerence
//elle iter sur ces dit pixel et les ajoute jusqua ce que le Pixel tester ne soit
//plus dans la tolerence
void running_area(struct Pixel *pix, struct Image *img, struct Zone *zt){
	if (test_exist(pix)){
		printf("test_exist de running_area ne segfault pas\n");
		//test si le pixel appartien deja a une zone
		if (pix_already_in_area(pix, zt)){
			printf("x = %lu\n", (*pix).x);
			printf("y = %lu\n", (*pix).y);
			printf("sizeX = %lu\n", (*img).sizeX);
			printf("sizeY = %lu\n", (*img).sizeY);
			printf("x - 1 = %lu\n", (*pix).x - 1);
			printf("x + 1 = %lu\n", (*pix).x + 1);
			printf("y - 1 = %lu\n", (*pix).y - 1);
			printf("y + 1 = %lu\n", (*pix).y + 1);
			printf("pix_already_in_area ne segfault pas\n");
			//test si le pixel de droite est dans les borne
			printf("entree dans le pixel de droite\n");
			if ((*pix).x + 1 < (*img).sizeX){
				printf("putin il rentre bien dedans\n");
				running_area(pix_at_img(img, pix->x + 1, pix->y), img, zt);
			}
			//test si le pixel du bas est dans les borne
			printf("entree dans le pixel du bas\n");
			if ((*pix).y + 1 < (*img).sizeY)
				running_area(pix_at_img(img, pix->x, pix->y + 1), img, zt);
			//test si le pixel de gauche est dans les borne
			printf("entree dans le pixel de gauche\n");
			if ((*pix).x - 1 < (*img).sizeX)
				running_area(pix_at_img(img, pix->x - 1, pix->y), img, zt);
			//test si le pixel du haut est dans les borne
			printf("entree dans le pixel du haut\n");
			if ((*pix).y - 1 < (*img).sizeY)
				running_area(pix_at_img(img, pix->x, pix->y - 1), img, zt);
		}
		else
			return;
	}
	if (pix_to_add(pix, zt)){
		printf("pix_to_add ne segfault\n");
		//ajoute le pixel a la liste des pixels de la zone et attribut la zone au Pixel
		zone_add_pix(zt, pix);
		printf("zone_add_pix ne segfault pas\n");
		running_area(pix, img, zt);
	}
}

//la fonction cree une nouvelle zone avec les caract du Pixel
//ajoute aussi la zone a img
void map_area(struct Pixel *pix, struct Image *img){
	struct Zone *zt;

	printf("avant la creation de la zone\n");
	zt = new_zone(img,pix);
	printf("apres la creation de la zone\n");
	printf("avant l ajout de la zone a l image\n");
	img_add_zone(img, zt);
	printf("apres l ajout de la zone a l image\n");
	printf("avan la fonction running_area\n");
	running_area(pix, img, zt);
	printf("apres la fonction running_area\n");
}

//la fonction parcour pixel par pixel l image
void process(struct Image *img){
	unsigned long x, y;
	printf("debut du parcour du tableau\n");
	for(y = 0; y < (*img).sizeY; y++){
		printf("parcoure de la ligne %lu : \n", y);
		for(x = 0; x < (*img).sizeX; x++){
			printf("parcour du pixel %lu : \n", x);
			//check si le pixel actuel possede deja une Zone
			if (test_exist(pix_at_img(img,x,y)) == false){
				printf("test_exist ne segfault pas\n");
				map_area(pix_at_img(img, x, y), img);
				printf("fin du mapping\n");
			}
		}
	}
}
