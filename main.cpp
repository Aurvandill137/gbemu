#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "cpu.h"
#include "mmu.h"
#include <GL/freeglut.h>
#include <GL/glu.h>

#define WINDOW_TITLE "Chapter 1"
#define HEIGHT 144
#define WIDTH 160

using namespace std;

struct pixel{
  GLfloat r = 0.0;
  GLfloat g = 0.0;
  GLfloat b = 0.0;
};

pixel display[HEIGHT][WIDTH];


//TODO: add graphics
//TODO: add sound emulation
//TODO: add cpu cycle emulation

void idle(){                   
	glPointSize(((glutGet(GLUT_WINDOW_WIDTH)/WIDTH)+(glutGet(GLUT_WINDOW_HEIGHT)/HEIGHT))/2.0);
  //glOrtho(0,glutGet(GLUT_WINDOW_WIDTH),0,glutGet(GLUT_WINDOW_HEIGHT),-1,1);
	glutPostRedisplay();
}


void render(){
	
	for(uint8_t x = 0; x < HEIGHT; x++){
    for(uint8_t y = 0; y < WIDTH; y++){
      glColor3f(display[x][y].r, display[x][y].g, display[x][y].r); 
      glBegin(GL_POINTS);
        glVertex2i(x,y);
      glEnd();
    }
    cout<<(int)x<<endl;
  }
	

	glFlush();	
}

int main(int argc, char* argv[]){

   for(uint8_t x = 0; x < HEIGHT; x++){
    for(uint8_t y = 0; y < WIDTH; y++){
      display[x][y].r = (x+y)/255.0;
      display[x][y].g = (2*x+y)/255.0;
      display[x][y].b = (3*x+y)/255.0;
    }
  }

  extern uint8_t mem[];
    
  cout << "Hello, World!" << std::endl;
  
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutCreateWindow(WINDOW_TITLE);
  glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glDisable(GL_POINT_SMOOTH);
	glLoadIdentity();
  glOrtho(0,WIDTH,0,HEIGHT,-1,1);
  //glOrtho(0,glutGet(GLUT_WINDOW_WIDTH),0,glutGet(GLUT_WINDOW_HEIGHT),-1,1);
  glPointSize(1);
  glutDisplayFunc(render);
  glutIdleFunc(idle);

 
  glutMainLoop();
  return 0;
}