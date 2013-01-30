#include "StdAfx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>
#include "imageloader.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include  "alien.h"
#include "player.h"
#include "lodepng.h" 
#include <SOIL.h>




using namespace std;
GLuint LoadTextureRAW( const char * filename, int wrap, int w, int h );
 GLuint raw_texture_load(const char *filename, int width, int height);
GLfloat boxsize = 2;
bool a = false;
bool d = false;
bool w = false;
bool s = false;
bool q = false;
bool e = false;

Player p = Player();


void key_down_func(unsigned char key, int x, int y) {
	switch (key) {
	// a-key
	case 97:
		a = true;
		p.mdegrees -= 2;
		break;
	// d-key
	case 100:
		d  = true;
		p.mdegrees += 2;
		break;
	// w-key
	case 119:
		w = true;
	p.calculate_direction();
		p.mpositionx = p.mpositionx - (p.mdirx);
		p.mpositionz = p.mpositionz + (p.mdirz);
		break;
	// s-key
	case 115:
		s = true;
	p.calculate_direction();
		p.mpositionx = p.mpositionx + (p.mdirx);
		p.mpositionz = p.mpositionz - (p.mdirz);
		break;
	// q-key
	case 113:
		//p.mpositionz = p.mpositionx - (p.mdirx);
		q = true;
		p.calculate_direction_horizontal();
		p.mpositionx = p.mpositionx + (p.mdirz);
		p.mpositionz = p.mpositionz - (p.mdirx);
		break;
	case 'e':
		e = true;
		//p.mpositionz = p.mpositionx - (p.mdirx);
		p.calculate_direction_horizontal();
		p.mpositionx = p.mpositionx - (p.mdirz);
		p.mpositionz = p.mpositionz + (p.mdirx);
		break;
	case 27: //Escape key
			exit(0);
	}
}

void key_up_func(unsigned char key, int x, int y) {
	switch (key) {
	// a-key
	case 97:
		a = false;
		p.mdegrees -= 2;
		break;
	// d-key
	case 100:
		d  = false;
		p.mdegrees += 2;
		break;
	// w-key
	case 119:
		w = false;
	p.calculate_direction();
		p.mpositionx = p.mpositionx - (p.mdirx);
		p.mpositionz = p.mpositionz + (p.mdirz);
		break;
	// s-key
	case 115:
		s = false;
	p.calculate_direction();
		p.mpositionx = p.mpositionx + (p.mdirx);
		p.mpositionz = p.mpositionz - (p.mdirz);
		break;
	// q-key
	case 113:
		q = false;
		p.calculate_direction_horizontal();
		//p.mpositionz = p.mpositionx - (p.mdirx);
		p.mpositionx = p.mpositionx + (p.mdirz);
		p.mpositionz = p.mpositionz - (p.mdirx);
		break;
	case 'e':
		e = false;
		//p.mpositionz = p.mpositionx - (p.mdirx);
		p.calculate_direction_horizontal();
		p.mpositionx = p.mpositionx - (p.mdirz);
		p.mpositionz = p.mpositionz + (p.mdirx);
		break;
	case 27: //Escape key
			exit(0);
	}
}



//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture

}
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}
int prevd = 0;
GLuint t;
GLuint alien;
GLfloat prevdegr = 0;
Alien l= Alien(p.mpositionx, p.mpositionz);
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	p.draw_player();


	l.draw_alien(p.mpositionx, p.mpositionz);
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60, 1, 0.1, 1000.0 );

	GLfloat maxy = 50;
	GLfloat miny = -20;
	GLfloat minx = -150;
	GLfloat maxx = 150;
	GLfloat minz = -150;
	GLfloat maxz = 150;
	GLfloat lengthx = std::abs(minx) +maxx;
	GLfloat lengthy = std::abs(miny) +maxy;
	
	glColor4f(1, 0,0, 0);
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, t);
	glBegin(GL_QUADS);
	glVertex3f(minx,miny, minz);
	glVertex3f(minx,maxy, minz);
	glVertex3f(minx,maxy, maxz);
	glVertex3f(minx,miny, maxz);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	
	glEnable(GL_TEXTURE_2D);
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(minx, maxy, minz);
	glVertex3f(maxx, maxy, minz);
	glVertex3f(maxx, maxy, maxz);
	glVertex3f(minx, maxy, maxz);


	glEnable(GL_TEXTURE_2D);
	glColor4f(1,1,1, 0);
    glBindTexture(GL_TEXTURE_2D, t);
	glTexCoord2f(0, 0);
	glVertex3f(minx, miny, minz);
	glVertex3f(maxx, miny, minz);
	glVertex3f(maxx, miny, maxz);
	glTexCoord2f(1, 1);
	glVertex3f(minx, miny, maxz);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}
// load a 256x256 RGB .RAW file as a texture
// Taken from http://www.nullterminator.net/gltexture.html
GLuint LoadTextureRAW( const char * filename, int wrap, int w, int h )
{
    GLuint texture;
    int width, height;
    BYTE * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer
    width = w;
    height = h;
    data = (BYTE*) malloc( width * height * 3 );

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

	/*
	glTexImage2D(GL_TEXTURE_2D, 0, 
		GL_RGBA,
		width,
		height, 
		0, 
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data);
		*/
    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    free( data );

    return texture;
}

//Called every 25 milliseconds
void update(int value) {
	glutPostRedisplay();
	if(a)
	{
	p.mdegrees -= 2;
	}
	if(d)
	{
		p.mdegrees += 2;
	}
	if(w)
	{
	
		p.calculate_direction();
		if(q||e){
		
			p.mpositionx = p.mpositionx - (p.mdirx/2);
			p.mpositionz = p.mpositionz + (p.mdirz/2);
		}
		else{

			p.mpositionx = p.mpositionx - (p.mdirx);
			p.mpositionz = p.mpositionz + (p.mdirz);
		}
	}
	if(s){
	p.calculate_direction();
		if(q||e){
		
			p.mpositionx = p.mpositionx + (p.mdirx/2);
			p.mpositionz = p.mpositionz - (p.mdirz/2);
		}
		else{
		p.mpositionx = p.mpositionx + (p.mdirx);
		p.mpositionz = p.mpositionz - (p.mdirz);
		}
	}
	if(q)
	{
		p.calculate_direction_horizontal();
		if(w||s)
		{
			p.mpositionx = p.mpositionx + (p.mdirz/2);
			p.mpositionz = p.mpositionz - (p.mdirx/2);
		}
		else{

		p.mpositionx = p.mpositionx + (p.mdirz);
		p.mpositionz = p.mpositionz - (p.mdirx);
		}

	}
	if(e)
	{
		p.calculate_direction_horizontal();
		if(w||s)
		{
		p.mpositionx = p.mpositionx - (p.mdirz/2);
		p.mpositionz = p.mpositionz + (p.mdirx/2);
		}
		else{

		p.mpositionx = p.mpositionx - (p.mdirz);
		p.mpositionz = p.mpositionz + (p.mdirx);
		}
	}

	glutTimerFunc(25, update, 0);
}


 GLuint raw_texture_load(const char *filename, int width, int height)
 {
     GLuint texture;
     unsigned char *data;
     FILE *file;
 
     // open texture data
     file = fopen(filename, "rb");
     if (file == NULL) return 0;
 
     // allocate buffer
     data = (unsigned char*) malloc(width * height * 4);
 
     // read texture data
     fread(data, width * height * 4, 1, file);
     fclose(file);
 
     // allocate a texture name
     glGenTextures(1, &texture);
 
     // select our current texture
     glBindTexture(GL_TEXTURE_2D, texture);
 
     // select modulate to mix texture with color for shading
     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
 
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
 
     // when texture area is small, bilinear filter the closest mipmap
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
     // when texture area is large, bilinear filter the first mipmap
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
     // texture should tile
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 
     // build our texture mipmaps
     gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
 
     // free buffer
     free(data);
 
     return texture;
 }


GLuint GetTexture(std::string Filename)
{
	GLuint tex_ID;

	tex_ID = SOIL_load_OGL_texture(
				Filename.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_POWER_OF_TWO
				| SOIL_FLAG_MIPMAPS
				| SOIL_FLAG_MULTIPLY_ALPHA
				| SOIL_FLAG_COMPRESS_TO_DXT
				| SOIL_FLAG_DDS_LOAD_DIRECT
				| SOIL_FLAG_INVERT_Y
				);

		if( tex_ID > 0 )
		{
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, tex_ID );
			
			return tex_ID;
		}
		else
			return 0;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("FPS");
	//glutFullScreen();
	initRendering();
	
	// t = LoadTextureRAW("bricks3.raw", 1);
	t = LoadTextureRAW("tile.raw", 1,90,90);
	//alien = loadTexture(image);
	//alien = LoadTextureRAW("alien5.png", 1, 120,350);
	alien = GetTexture("alien5.png");
	//alien = raw_texture_load("alien.raw",  120, 350);

	l.set_texture(alien);

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(key_down_func);
	glutKeyboardUpFunc(key_up_func);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutIgnoreKeyRepeat(true);
	glutMainLoop();
	return 0;
}

