#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include <cmath>

using namespace std;

const float PI = 3.1416f;
GLfloat xrot = 0;
uint tex[1];
float posz = -10.0f;
float posx = 0;
float roty = 0;
float vel = 0.2f;


void LoadTexture(string filename)
{
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.c_str(),0);
    FIBITMAP* img = FreeImage_Load(format,filename.c_str());
    FIBITMAP * temp = img;

    int w, h;

    w = FreeImage_GetWidth(img);
    h = FreeImage_GetHeight(img);


    img = FreeImage_ConvertTo32Bits(img);

    char * pixels = (char * )FreeImage_GetBits(img);

    FreeImage_Unload(temp);

    glGenTextures(1,tex);

    glBindTexture(GL_TEXTURE_2D,tex[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,h,0,GL_RGBA, GL_UNSIGNED_BYTE,  pixels);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

}

void DrawGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //Rotacionar Câmera
    glRotatef(360.0f - roty,0,1.0f,0);
    glTranslatef(posx, 0, posz);

    //Rotacionar Triangulos
    glRotatef(xrot, 1.0f,0,0);

    glBindTexture(GL_TEXTURE_2D,tex[0]);

    glBegin(GL_TRIANGLES);
       glTexCoord2f(0,1); glVertex3f(-1.0f,1.0f,1.0f);
       glTexCoord2f(0,0); glVertex3f(-1.0f,-1.0f,1.0f);
       glTexCoord2f(1,0); glVertex3f(1.0f,-1.0f,1.0f);

       glTexCoord2f(0,1); glVertex3f(-1.0f,1.0f,1.0f);
       glTexCoord2f(1,1); glVertex3f( 1.0f,1.0f,1.0f);
       glTexCoord2f(1,0); glVertex3f( 1.0f,-1.0f,1.0f);
    glEnd();

    glutSwapBuffers();

    xrot += 0.5f;
}

void InitGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    LoadTexture("tex.jpg");
}

void Resize(int w, int h)
{
    if(h == 0)
        h = 1;
    float ratio = float(w)/h;

    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,ratio,1,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Input(unsigned char keys, int x, int y)
{
    switch(keys)
    {
        case 'w':
            posx += vel*sin(roty*PI/180);
            posz += vel*cos(roty*PI/180);break;
        case 's':
            posx += -vel*sin(roty*PI/180);
            posz += -vel*cos(roty*PI/180); break;
        case 'a':
            roty += 1.0f;
            break;
        case 'd':
            roty -= 1.0f;
            break;
    }
}

int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(800,600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
    glutCreateWindow("Daora a vida");
    InitGL();

    glutDisplayFunc(DrawGL);
    glutIdleFunc(DrawGL);
    glutReshapeFunc(Resize);
    glutKeyboardFunc(Input);
    glutMainLoop();

    return 0;
}

