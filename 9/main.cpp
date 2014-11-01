/*

Apertar o B para blending
Apertar L para Luz
Rotacionar com as setas!



*/
#include <iostream>
#include <GL/glut.h>
#include "SOIL/SOIL.h"
#include <unistd.h>

#define WINDOW_NAME "Nehe 9"

using namespace std;

GLuint textures[3];
float rotx = 0;
float roty = 0;
float rotz = 0;

bool fullscreen;
bool active;
bool keys[256];

bool twinkle = false;


GLfloat LightAmbient[]  = { 0.5f, 0.5f,0.5f,0.5f};
GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f};

// Número de estrelas!
const uint NUM = 50;

typedef struct
{
	int r,g,b;
	float dist;
	float angle;
}Star;

Star stars[NUM];

//Variáveis das estrelas:
float zoom = -15.0f;
float tilt = 90.0f;
float spin = 0;

GLuint loop;
GLuint texture[1];


void DrawGL()
{
	spin = 0;
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D,texture[0]);

	for(int loop = 0 ; loop < NUM ; ++loop)
	{
		glLoadIdentity();
		
		glTranslatef(0.0f,0.0f,zoom);
		
		glRotatef(tilt,1.0f,0.0f,0.0f);
		
		glRotatef(stars[loop].angle,0.0f,1.0f,0.0f);
		
		glTranslatef(stars[loop].dist,0.0f,0.0f);
		
		
		glRotatef(-stars[loop].angle,0.0f,1.0f,0.0f);
	
		glRotatef(-tilt,1.0f,0.0f,0.0f);

		if(twinkle)
		{
			glColor4ub(stars[NUM - loop - 1].r,stars[NUM - loop - 1].g,stars[NUM - loop - 1].b,255);
			glBegin(GL_QUADS);
				// Front Face
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
			glEnd();
		}

		glRotatef(spin,0.0f,0.0f,1.0f);

		glColor4ub(stars[loop].r,stars[loop].g,stars[loop].b,255);

		glBegin(GL_QUADS);
			// Front Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glEnd();

		stars[loop].angle += float(loop)/NUM;
		stars[loop].dist  -= 0.01f;
		spin += 0.01f;

		if(stars[loop].dist < 0.0f)
		{
			stars[loop].dist += 5.0f;
			stars[loop].r = rand( ) % 256;
		    /* Give It A New Green Value */
		    stars[loop].g = rand( ) % 256;
		    /* Give It A New Blue Value */
		    stars[loop].b = rand( ) % 256;
		}
	}

/* Rotate The Star On The Z Axis */


	glutSwapBuffers();

}

bool LoadGLTextures()
{
	texture[0]  = SOIL_load_OGL_texture(
			"Star.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
			);

	cout << SOIL_last_result() << endl;


	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	for( loop = 0; loop < NUM; ++loop)
	{
		stars[loop].angle = 0.0f;
		stars[loop].dist  = ((float) loop/ (float) NUM) * 5.0f;
		stars[loop].r = rand()%256;
		stars[loop].g = rand()%256;
		stars[loop].b = rand()%256;
	}

	return true;
}
void InitGL()
{
	LoadGLTextures();
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_BLEND);


	for(loop  = 0 ; loop < NUM ; ++loop)
	{
		stars[loop].angle=0.0f;
		stars[loop].dist=(float(loop)/NUM)*5.0f;
		stars[loop].r=rand()%256;
		stars[loop].g=rand()%256;
		stars[loop].b=rand()%256;
	}
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

void UpdateInput(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 't':
			twinkle = !twinkle;
			break;
	}

}

void UpdateSplInput(int key, int x, int y)
{
	switch(key)
	{
		
		
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(WINDOW_NAME);
	
	InitGL();

	glutDisplayFunc(DrawGL);
	glutIdleFunc(glutPostRedisplay);
	glutReshapeFunc(ReshapeGL);
	glutKeyboardFunc(UpdateInput);
	glutSpecialFunc(UpdateSplInput);
	glutMainLoop();

	return 0;	
}
