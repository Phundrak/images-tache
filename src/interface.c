#include "interface.h"
#include "ppm.h"
#include <stdio.h>

extern Image_t image;

void Keyboard(unsigned char key, int x, int y) {
  switch(key) {
  case ESCAPE:
  case SHIFTQ:
  case LOWQ:
    exit(0);
    break;
  default:
    fprintf(stderr, "Unused Key\n");
  }
}

void Mouse(int button, int state, int x, int y) {
  switch(button) {
  case GLUT_LEFT_BUTTON:
  case GLUT_MIDDLE_BUTTON:
  case GLUT_RIGHT_BUTTON:
    break;
  }
  glutPostRedisplay();
}

int Init(char *s) {
  image = (Image_t)malloc(sizeof(Image));
  if(!image){
    fprintf(stderr, "Out of memory\n");
    return -1;
  }
  if(ImageLoad_PPM(s, image) == -1)
    return -1;
  printf("Tailles: %d %d\n", (int)image->sizeX, (int)image->sizeY);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glutReshapeWindow(image->sizeX, image->sizeY);

  return 0;
}

int ReInit() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glutReshapeWindow(image->sizeX, image->sizeY);
  return 0;
}

void Display(void) {
  GLint w, h;

  glClear(GL_COLOR_BUFFER_BIT);

  w = glutGet(GLUT_WINDOW_WIDTH);
  h = glutGet(GLUT_WINDOW_HEIGHT);
  glDrawPixels(image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
               image->data);
  glFlush();
}
