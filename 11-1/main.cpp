#include <iostream>
#include <GL/freeglut.h>
#include <FreeImage.h>
#include <cmath>
#include "../glutil.h"

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

bool poligon_line = false;
bool wind = true;

POINT points[45][45]; 

void DrawGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	float mx,my,mz,mu,mv;

	glTranslatef(0.0f,0.0f,-20.0f);
	glRotatef(rotx,1.0f,0.0f,0.0f);
	

	glBegin(GL_QUADS);
	{
		for(int x = 0; x < 44; ++x)
		{
			for(int y = 0; y < 44; ++y)
			{
				mx = points[x+1][y+1].x;				
				my = points[x+1][y+1].y;				
				mz = points[x+1][y+1].z;				
				mu = (x+1)/44.0f;				
				mv = (y+1)/44.0f;		
				glTexCoord2d(mv,mu);
				glVertex3f(mx,my,mz);
				mx = points[x][y+1].x;				
				my = points[x][y+1].y;				
				mz = points[x][y+1].z;				
				mu = x/44.0f;				
				mv = (y+1)/44.0f;				
				glTexCoord2d(mv,mu);
				glVertex3f(mx,my,mz);
				mx = points[x][y].x;				
				my = points[x][y].y;				
				mz = points[x][y].z;				
				mu = x/44.0f;				
				mv = y/44.0f;				
				glTexCoord2d(mv,mu);
				glVertex3f(mx,my,mz);
				mx = points[x+1][y].x;				
				my = points[x+1][y].y;				
				mz = points[x+1][y].z;				
				mu = (x+1)/44.0f;				
				mv = y/44.0f;				
				glTexCoord2d(mv,mu);
				glVertex3f(mx,my,mz);
			}
		}
	}
	glEnd();

	float hold;
	if(wind)
	{
		for(int x = 0; x < 45 ; ++x)
		{
			hold = points[x][0].z;	
			for(int y = 0; y < 44; ++y)
			{
				points[x][y].z = points[x][y+1].z;	
			}
			points[x][44].z = hold;
		}

	}

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
	glEnable(GL_TEXTURE_2D);
	texture[0] = LoadImageAsTexture(TEXTURE_FILE);
	if(texture[0] == 0)
	{
		cout << "COULDN'T LOAD THE TEXTURE FROM FILE \"" << TEXTURE_FILE << endl;
	}	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);


	for(int x = 0; x < 45; ++x)
	{
		for(int y = 0; y < 45; ++y)
		{
			points[x][y].x = y/5.0f -4.5f;
			points[x][y].y = x/5.0f -4.5f;
			points[x][y].z = sin(torad(y)*8);
		}
	}
}

void KeyboardnGL(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'p':
			if(!poligon_line)
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			poligon_line = !poligon_line;
		break;

		case 'w':
			wind = !wind;
	}
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
	glutKeyboardFunc(KeyboardnGL);
	glutMainLoop();
 	return 0;
}
