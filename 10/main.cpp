	/*

	Apertar o B para blending
	Apertar L para Luz
	Rotacionar com as setas!



	*/
#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include <fstream>
#include <sstream>
#include <cmath>

#define WINDOW_NAME "Nehe 10"
#define WORLD_FILE "WORLD.TXT"

using namespace std;

float posx = 0;
float posy = 0;
float posz = 0;

float walkbiasangle = 0;
float walkbias = 0;

bool fullscreen;
float vel = 0.1f;
const GLfloat PI = 3.1416f;

GLfloat LightAmbient[]  = { 0.5f, 0.5f,0.5f,0.5f};
GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f};

GLuint loop;
GLuint texture[1];

typedef struct
{
	float x, y, z;
	float u, v;
}VERTEX;

typedef struct
{
	VERTEX vertex[3];
}TRIANGLE;

typedef struct
{
	int numtriangles;	
	TRIANGLE* triangle;
}SECTOR;

typedef struct
{
	float x,y,z;
	float rotx;
	float roty;
}PLAYER;

PLAYER player = {
	0,1,0,0,0
};

SECTOR c;

void jumplines(ifstream &file,uint lines)
{
	string line;
	for(uint i = 0; i < lines; ++i)
	{
		getline(file,line);	
	}
}

void readstr(ifstream &file,string &stg )
{
	do
	{
		getline(file,stg);
		if(stg[0] == '/')
			cout << stg << endl;
	}while(stg[0] == '/' || stg[0] == '\0');
}

void SetupWorld()
{
	string line;
	int NUMBER_TRIG;
	ifstream file(WORLD_FILE);
	if(!file.is_open())
	{
		cout << "File not open. Error!" << endl;
		exit(EXIT_FAILURE);
	}

	jumplines(file,1);
	getline(file, line);
	sscanf(line.c_str(),"NUMPOLLIES %d\n", &NUMBER_TRIG);

	// Colocando dados no setor	
	c.triangle = new TRIANGLE[NUMBER_TRIG];
	c.numtriangles = NUMBER_TRIG;

	float x,y,z,u,v;

	jumplines(file,1);
	for(int l = 0; l < NUMBER_TRIG; ++l)
	{
		for(int i = 0; i < 3; ++i)
		{
			readstr(file,line);
			sscanf(line.c_str(),"%f	%f %f %f %f",&x,&y,&z,&u,&v);
			c.triangle[l].vertex[i].x = x;
			c.triangle[l].vertex[i].y = y;
			c.triangle[l].vertex[i].z = z;
			c.triangle[l].vertex[i].u = u;
			c.triangle[l].vertex[i].v = v;
		}
	}
}

void DrawGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D,texture[0]);
	
	GLfloat x_m,y_m,z_m,u_m,v_m;
/*
	GLfloat ytrans = -walkbias-0.25f;
	GLfloat sceneroty = 360.0f - yrot;


	glRotatef(lookupdown,1.0f,0.0f,0.0f);
	glRotatef(sceneroty, 0, 1.0f, 0.0);
*/

	glRotatef(360.0f - player.roty,0,1.0f,0.0);
	glTranslatef(player.x,-0.22f,player.z);

	int numtriangles = c.numtriangles;

	glColor3f(1,1,1);

	for(int i = 0; i < numtriangles ; ++i)
	{
		glBegin(GL_TRIANGLES);
		{
			glNormal3f(0.0f,0.0f,1.0f);
			x_m = c.triangle[i].vertex[0].x; 
			y_m = c.triangle[i].vertex[0].y; 
			z_m = c.triangle[i].vertex[0].z; 
			u_m = c.triangle[i].vertex[0].u; 
			v_m = c.triangle[i].vertex[0].v;
			
			glTexCoord2f(u_m,v_m);
			glVertex3f(x_m, y_m, z_m);
			
			x_m = c.triangle[i].vertex[1].x; 
			y_m = c.triangle[i].vertex[1].y; 
			z_m = c.triangle[i].vertex[1].z; 
			u_m = c.triangle[i].vertex[1].u; 
			v_m = c.triangle[i].vertex[1].v;
			
			glTexCoord2f(u_m,v_m);
			glVertex3f(x_m, y_m, z_m);
			
			x_m = c.triangle[i].vertex[2].x; 
			y_m = c.triangle[i].vertex[2].y; 
			z_m = c.triangle[i].vertex[2].z; 
			u_m = c.triangle[i].vertex[2].u; 
			v_m = c.triangle[i].vertex[2].v;
			
			glTexCoord2f(u_m,v_m);
			glVertex3f(x_m, y_m, z_m);

		}
		glEnd();
	}
	

	glutSwapBuffers();

}


bool LoadGLTextures(string filename)
{

	glGenTextures(1,texture);
		
	int w,h;
	cout << filename << endl;
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType( filename.c_str(),0);
	FIBITMAP* image = FreeImage_Load(format, filename.c_str());
	FIBITMAP* temp = image;
	

	image = FreeImage_ConvertTo32Bits(image);
	
	FreeImage_Unload(temp);

	
	w = FreeImage_GetWidth(image);
	h = FreeImage_GetHeight(image);	
	cout << "WIDTH = " << w << endl;

	cout << "HEIGHT = " << h  << endl;

	GLubyte* pixels = (GLubyte *)  FreeImage_GetBits(image);


	glBindTexture(GL_TEXTURE_2D,texture[0]);
	//Também poderia setar aqui GL_BGR em vez de RGBA, mas isso é putaria.
	//Talvez quebre alguma coisa do código no futuro. :P
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,h,0,GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) pixels);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);



	return true;

}
void InitGL()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth( 1.0f );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT1);
	LoadGLTextures("tex.bmp");
	/* Setup The Ambient Light */
	glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient );

	/* Setup The Diffuse Light */
	glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse );

	/* Position The Light */
	glLightfv( GL_LIGHT1, GL_POSITION, LightPosition );
}

void ReshapeGL(int w, int h)
{
	float ratio = (float) w/ (float) h;	
	glViewport(0,0,w,h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(100.0f,ratio,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void UpdateInput(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'w':
			player.x += sin(player.roty*PI/180) * vel;
			player.z += cos(player.roty*PI/180) * vel;
			break;
		case 's':
			player.x -= sin(player.roty*PI/180) * vel;
			player.z -= cos(player.roty*PI/180) * vel;
			break;
		case 'd':
			player.roty -= 3.0f;
			break;
		case 'a':
			player.roty += 3.0f;
			break;
		case 't':
			break;
		case 'l':
			  if(glIsEnabled(GL_LIGHTING))
					  glDisable(GL_LIGHTING);
				else
					glEnable(GL_LIGHTING);
	}

}

void UpdateSplInput(int key, int x, int y)
{
	switch(key)
	{
				
		case GLUT_KEY_F11:
			glutFullScreen();
			break;
	}
}

int main(int argc, char** argv)
{
	SetupWorld();
	glutInit(&argc,argv);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(WINDOW_NAME);
	
	InitGL();

	glutDisplayFunc(DrawGL);
	glutIdleFunc(DrawGL);
			
	glutReshapeFunc(ReshapeGL);
	glutKeyboardFunc(UpdateInput);
	glutSpecialFunc(UpdateSplInput);
	glutMainLoop();

	return 0;	
}
