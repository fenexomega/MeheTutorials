#include <iostream>
#include <GL/freeglut.h>
#include <FreeImage.h>

#define TITULO "Nehe 11"
#define XRES 1024
#define YRES 768
#define TEXTURE_FILE "tex.bmp"

GLuint texture[1];
typedef struct
{
	float x,y,z;
}POINT;

using namespace std;

void DrawGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	glBindTexture(GL_TEXTURE_2D,texture[0]);

	glTranslatef(0.0f,0.0f,-3.0f);
	

	
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f, 1.0f ,0.0f );
		glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f ,0.0f );
		glTexCoord2f(1.0f,0.0f); glVertex3f( 1.0f,-1.0f ,0.0f );
		glTexCoord2f(1.0f,1.0f); glVertex3f( 1.0f, 1.0f ,0.0f );
	}
	glEnd();

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

unsigned int LoadImageAsTexture(string filename)
{
	FREE_IMAGE_FORMAT imgtype = FreeImage_GetFileType(filename.c_str());
	FIBITMAP *img = FreeImage_Load(imgtype,filename.c_str());
	FIBITMAP *temp = img;

	if(img == NULL)
	{
		return 0;
	}

	int w = FreeImage_GetWidth(img);
	int h = FreeImage_GetHeight(img);

	img = FreeImage_ConvertTo32Bits(img);
	FreeImage_Unload(temp);

	//O 4 aqui é por causa do offset!
	GLubyte* textura = new GLubyte[4*h*w];
	char * pixels = (char *) FreeImage_GetBits( img);
	


	for(int i = 0; i < w*h; ++i)
	{
		textura[4*i + 0 ] = pixels[4*i + 2 ];
		textura[4*i + 1 ] = pixels[4*i + 1 ];
		textura[4*i + 2 ] = pixels[4*i + 0 ];
		textura[4*i + 3 ] = pixels[4*i + 3 ];
	}
	
	unsigned int tex;
	glGenTextures(1,&tex);
	glBindTexture(GL_TEXTURE_2D,tex);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,(GLvoid *) textura);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	FreeImage_Unload(img);
	return tex;	

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

	glutMainLoop();
 	return 0;
}
