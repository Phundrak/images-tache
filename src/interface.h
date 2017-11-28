#ifndef IMGTACHES_SRC_INTERFACE_H_
#define IMGTACHES_SRC_INTERFACE_H_

#include "utilities.h"
#include <GL/glu.h>
#include <GL/glut.h>

#define ESCAPE 27
#define SHIFTQ 81
#define LOWQ 113

void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
int Init(char* s);
int ReInit();
void Display(void);
void Reshape(int w, int h);
void menuFunc(int item);


#endif /* IMGTACHES_SRC_INTERFACE_H_ */
