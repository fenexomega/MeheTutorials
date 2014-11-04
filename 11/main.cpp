#include <iostream>
#include <GL/freeglut.h>
#include <FreeImage.h>
#include <cmath>

#define TITULO "Nehe 11"
#define XRES 1024
#define YRES 768
#define TEXTURE_FILE "tex.bmp"
#define PI 3.141592654f
#define TORAD( x )  ( x ) *PI/180.0f

GLfloat rotx = 0;

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
	glLoadIdentity();
	
	glBindTexture(GL_TEXTURE_2D,texture[0]);

	glTranslatef(0.0f,0.0f,-20.0f);

	glRotatef(180.0f, 1.0f,0.0f,0.0f);

	GLfloat x_m, y_m, z_m;
	rotx++;

	glBegin(GL_QUADS);
	{
		for(int x = 0; x < 44; ++x)
		{
			for(int y = 0; y < 44; y++)
			{
					x_m = points[x][y].x;
					y_m = points[x][y].y;
					z_m = points[x][y].z;
					glVertex3f(x_m,y_m,z_m);	
					
					x_m = points[x][y+1].x;
					y_m = points[x][y+1].y;
					z_m = points[x][y+1].z;
					glVertex3f(x_m,y_m,z_m);	
					
					x_m = points[x+1][y+1].x;
					y_m = points[x+1][y+1].y;
					z_m = points[x+1][y+1].z;
					glVertex3f(x_m,y_m,z_m);	
					
					x_m = points[x+1][y].x;
					y_m = points[x+1][y].y;
					z_m = points[x+1][y].z;
					glVertex3f(x_m,y_m,z_m);	
			}
				
		}
	}
	glEnd();

	GLfloat hold;
	for(int x = 0; x < 45; ++x)
	{
		hold = points[0][x].z;
		for(int y = 0; y < 44; ++y)
		{	
			points[y][x].z = points[y+1][x].z;

		}
		points[44][x].z = hold;
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

	for(int x = 0; x < 45; x++)
	{
		for(int y = 0; y < 45; y++)
		{
			points[x][y].x = (float) (x/5.0f) - 4.5f;
			points[x][y].y = (float) (y/5.0f) - 4.5f;
			points[x][y].z = (float) sin( TORAD((x/5.0f)*40.0f)) ;
		}
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

	glutMainLoop();
 	return 0;
}
