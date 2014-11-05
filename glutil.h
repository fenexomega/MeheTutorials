#include <FreeImage.h>
#include <GL/gl.h>
#include <iostream>

#define pi 3.141592654f
#define torad( x )  ( x ) *pi/180.0f

unsigned int LoadImageAsTexture(std::string filename)
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
