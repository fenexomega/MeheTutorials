/*

Apertar o B para blending
Apertar L para Luz
Rotacionar com as setas!



*/
#include<iostream>
#include<GL/glut.h>
#include"SOIL/SOIL.h"
#include<unistd.h>

using namespace std;

GLuint textures[3];
float rotx = 0;
float roty = 0;
float rotz = 0;

bool fullscreen;
bool active;
bool keys[256];

bool light;
bool lp;
bool lf;
bool blend = false;

GLfloat LightAmbient[]  = { 0.5f, 0.5f,0.5f,0.5f};
GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f};

GLuint filter = 0;
GLuint texture[3];

float xcof = 0;
float ycof = 0;

typedef struct GIMAGE
{
	const char *filename;
	int width;
	int height;
	int *channels;
	unsigned char* DATA;
	int force_channels;
}gImage;

int as = 0;

void DrawGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
		
	glTranslatef(0,0,-5.0f);
	glRotatef(rotx,1.0f,0,0);
	glRotatef(roty,0,1.0f,0);

	glBindTexture(GL_TEXTURE_2D,texture[filter]);

	glBegin(GL_QUADS);
		// Front Face
		glNormal3f(0.0f,0.0f,1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f(0.0f,0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f(0.0f,1.0f,0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f(0.0f,-1.0f,1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glNormal3f(1.0f,0.0f,1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f(-1.0f,0.0f,1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

	rotx += xcof;
	roty += ycof;

	glutSwapBuffers();

}

bool LoadGLTextures()
{
	gImage image;
	/*for(int i = 0 ; i < 3; ++i)
	{
	 	aux = texture[i]  = SOIL_load_OGL_texture(
			"Crate.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
			);

		
		if(aux == 0)
		{
				cout << SOIL_last_result() << endl;
		}
	}*/

  	image.DATA = 
		SOIL_load_image("Glass.bmp",
		&image.width,&image.height,0,
		SOIL_LOAD_RGB);

	cout << SOIL_last_result() << endl;

	glGenTextures(3,texture);

	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,3,image.width,image.height,0,GL_RGB,GL_UNSIGNED_BYTE,image.DATA);

	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,image.width,image.height,0,GL_RGB,GL_UNSIGNED_BYTE,image.DATA);
	glBindTexture(GL_TEXTURE_2D,texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D,3,image.width,image.height,GL_RGB,GL_UNSIGNED_BYTE,image.DATA);


	return true;
}
void InitGL()
{
	LoadGLTextures();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);

	glColor4f(1.0f,1.0f,1.0f,0.5f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_LIGHT1);
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
		case 'l':
			glIsEnabled(GL_LIGHTING) == 1 ?
				glDisable(GL_LIGHTING) : glEnable(GL_LIGHTING);
			break;
		case 'f':
			filter = (filter+1)%3;
			break;
		case 'b':
			if(!glIsEnabled(GL_BLEND))
			{
				glEnable(GL_BLEND);
				glDisable(GL_DEPTH_TEST); 
			}
			else
			{
				glEnable(GL_DEPTH_TEST);
				glDisable(GL_BLEND); 
			}
	}

}

void UpdateSplInput(int key, int x, int y)
{
	switch(key)
	{
		
		case GLUT_KEY_RIGHT:
			ycof -= 0.1f;
			break;
		case GLUT_KEY_LEFT:
			ycof += 0.1f;
			break;
		case GLUT_KEY_UP:
			xcof -= 0.1f;
			break;
		case GLUT_KEY_DOWN:
			xcof += 0.1f;
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Nehe 8 - Blending");
	
	InitGL();

	glutDisplayFunc(DrawGL);
	glutIdleFunc(DrawGL);
	glutReshapeFunc(ReshapeGL);
	glutKeyboardFunc(UpdateInput);
	glutSpecialFunc(UpdateSplInput);
	glutMainLoop();

	return 0;	
}
