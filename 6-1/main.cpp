#include<iostream>
#include<GL/freeglut.h>
#include"SOIL/SOIL.h"
#include <string>

using namespace std;

uint8_t textureid[6];

float xrot = 0;
float yrot = 0;
float zrot = 0;

uint8_t LoadTexture(string filename)
{
	uint8_t texture_id =  SOIL_load_OGL_texture(
			filename.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
			);
		if(texture_id == 0) cout << SOIL_last_result() << endl;
	
	glBindTexture(GL_TEXTURE_2D,texture_id);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	return texture_id;

}

void InitGL()
{
	for(int i = 0; i < 6; ++i)
	 textureid[i] = LoadTexture("texture" + to_string(i) + ".bmp");
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR); //Default

	glClearDepth(1.0f);
}

void DrawGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0,0,-3.0f);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	glRotatef(zrot,0.0f,0.0f,1.0f);

	glBindTexture(GL_TEXTURE_2D,textureid[0]);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,1); glVertex3f(-0.5f, 0.5f, 0.5f);	
	 	glTexCoord2f(1,1); glVertex3f( 0.5f, 0.5f, 0.5f);	
		glTexCoord2f(1,0); glVertex3f( 0.5f,-0.5f, 0.5f);	
		glTexCoord2f(0,0); glVertex3f(-0.5f,-0.5f, 0.5f);	
		
	

	}
	glEnd();
	xrot += 0.6f;

	glBindTexture(GL_TEXTURE_2D,textureid[1]);
	
	glBegin(GL_QUADS);
	{

		glTexCoord2f(0,1); glVertex3f(-0.5f,-0.5f,-0.5f);	
		glTexCoord2f(1,1); glVertex3f( 0.5f,-0.5f,-0.5f);	
		glTexCoord2f(1,0); glVertex3f( 0.5f, 0.5f,-0.5f);	
		glTexCoord2f(0,0); glVertex3f(-0.5f, 0.5f,-0.5f);	
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,textureid[2]);
	
	glBegin(GL_QUADS);
	{

		glTexCoord2f(0,1); glVertex3f(-0.5f, 0.5f, 0.5f);	
		glTexCoord2f(0,0); glVertex3f(-0.5f, 0.5f,-0.5f);	
		glTexCoord2f(1,0); glVertex3f( 0.5f, 0.5f,-0.5f);	
		glTexCoord2f(1,1); glVertex3f( 0.5f, 0.5f, 0.5f);	
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,textureid[3]);
	
	glBegin(GL_QUADS);
	{

		glTexCoord2f(0,1); glVertex3f(-0.5f,-0.5f, 0.5f);	
		glTexCoord2f(0,0); glVertex3f(-0.5f,-0.5f,-0.5f);	
		glTexCoord2f(1,0); glVertex3f( 0.5f,-0.5f,-0.5f);	
		glTexCoord2f(1,1); glVertex3f( 0.5f,-0.5f, 0.5f);	
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,textureid[4]);
	
	glBegin(GL_QUADS);
	{

		glTexCoord2f(0,1); glVertex3f(-0.5f, 0.5f,-0.5f);	
		glTexCoord2f(0,0); glVertex3f(-0.5f,-0.5f,-0.5f);	
		glTexCoord2f(1,0); glVertex3f(-0.5f,-0.5f, 0.5f);	
		glTexCoord2f(1,1); glVertex3f(-0.5f, 0.5f, 0.5f);	
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,textureid[5]);
	
	glBegin(GL_QUADS);
	{

		glTexCoord2f(0,1); glVertex3f( 0.5f, 0.5f,-0.5f);	
		glTexCoord2f(0,0); glVertex3f( 0.5f,-0.5f,-0.5f);	
		glTexCoord2f(1,0); glVertex3f( 0.5f,-0.5f, 0.5f);	
		glTexCoord2f(1,1); glVertex3f( 0.5f, 0.5f, 0.5f);	
	}
	glEnd();

	xrot += 0.3f;
	yrot += 0.2f;
	zrot += 0.1f;

	glutSwapBuffers();
}

void ReshapeGL(int w, int h)
{
	if(h == 0) h = 1 ;

	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)w/(float)h,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	//GLUT Initialization
	glutInit(&argc,argv);
 	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Texture test - Nehe 6");

	InitGL();

	//Glut Function pointers
	glutDisplayFunc(DrawGL);
	glutReshapeFunc(ReshapeGL);
	glutIdleFunc(DrawGL);

	glutMainLoop();


	
	return 0;
}
