#include <iostream>
#include <GL/freeglut.h>
#include <FreeImage.h>
#include <cmath>
#include "../utilgl.h"

#define TITULO "Nehe 11"
#define XRES 1024
#define YRES 768
#define TEXTURE_FILE "bandeira-do-brasil.jpg"

GLfloat rotx = 0;
GLfloat roty = 0;

GLuint texture[1];
typedef struct
{
	float x,y,z;
}POINT;

using namespace std;

POINT points[45][45]; 

void DrawGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);



	glutSwapBuffers();
}


void ReshapeGL(int w, int h)
{
	if(h == 0) h = 1;

	float ratio = (float) w/h;

	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,ratio,0.1f,100.0f);

	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void initGL()
{
	glPolygonMode(GL_BACK, GL_FILL);
	glPolygonMode(GL_FRONT,GL_LINE);
	glEnable(GL_TEXTURE_2D);
	texture[0] = LoadImageAsTexture(TEXTURE_FILE);
	if(texture[0] == 0)
	{
		cout << "COULDN'T LOAD THE TEXTURE FROM FILE \"" << TEXTURE_FILE << endl;
	}	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
}

void KeyboardGL(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			rotx -= 3.0f;
			break;
		case GLUT_KEY_DOWN:
			rotx += 3.0f;
			break;
		case GLUT_KEY_RIGHT:
			roty -= 3.0f;
			break;
		case GLUT_KEY_LEFT:
			roty += 3.0f;
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(XRES,YRES);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(TITULO);
	initGL();

	glutDisplayFunc(DrawGL);
	glutIdleFunc(DrawGL);
	glutReshapeFunc(ReshapeGL);
	glutSpecialFunc(KeyboardGL);

	glutMainLoop();
 	return 0;
}
