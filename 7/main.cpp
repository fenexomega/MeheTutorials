#include<iostream>
#include<GL/glut.h>
#include"SOIL/SOIL.h"

using namespace std;

int textures[6];
float rotx = 0;
float roty = 0;
float rotz = 0;


void DrawGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
		
	glTranslatef(0,0,-2.0f);
	glRotatef(rotx,1.0f,0,0);
	glRotatef(roty,0,1.0f,0);
	glRotatef(rotz,0,0,1.0f);

	glutWireCube(1.0f);
	
	glutSwapBuffers();

	rotx += 0.6f;
	roty += 0.2f;
	rotz += 0.22f;
}

void InitGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearDepth(1.0f);
}

void ReshapeGL(int w, int h)
{
	float ratio = (float) w/ (float) h;	
	glViewport(0,0,w,h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,ratio,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Nehe 7 - Lighinting");
	
	InitGL();

	glutDisplayFunc(DrawGL);
	glutIdleFunc(DrawGL);
	glutReshapeFunc(ReshapeGL);

	glutMainLoop();


	return 0;	
}
