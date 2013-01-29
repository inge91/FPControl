#include "StdAfx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>
#include "imageloader.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <cmath>
#include  "alien.h"
using namespace std;
void calculate_direction();
void calculate_direction_horizontal();
GLuint LoadTextureRAW( const char * filename, int wrap, int w, int h );

GLfloat boxsize = 2;
bool rotating = false;
GLfloat degrees = 0;
GLfloat position = 0;
GLfloat positionx;
GLfloat positionz;
GLfloat dirx;
GLfloat dirz;
bool a = false;
bool d = false;
bool w = false;
bool s = false;
bool q = false;
bool e = false;



void key_down_func(unsigned char key, int x, int y) {
	switch (key) {
	// a-key
	case 97:
		a = true;
		degrees -= 2;
		break;
	// d-key
	case 100:
		d  = true;
		degrees += 2;
		break;
	// w-key
	case 119:
		w = true;
	calculate_direction();
		positionx = positionx - (dirx);
		positionz = positionz + (dirz);
		break;
	// s-key
	case 115:
		s = true;
	calculate_direction();
		positionx = positionx + (dirx);
		positionz = positionz - (dirz);
		break;
	// q-key
	case 113:
		//positionz = positionx - (dirx);
		q = true;
		calculate_direction_horizontal();
		positionx = positionx + (dirz);
		positionz = positionz - (dirx);
		break;
	case 'e':
		e = true;
		//positionz = positionx - (dirx);
		calculate_direction_horizontal();
		positionx = positionx - (dirz);
		positionz = positionz + (dirx);
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
		degrees -= 2;
		break;
	// d-key
	case 100:
		d  = false;
		degrees += 2;
		break;
	// w-key
	case 119:
		w = false;
	calculate_direction();
		positionx = positionx - (dirx);
		positionz = positionz + (dirz);
		break;
	// s-key
	case 115:
		s = false;
	calculate_direction();
		positionx = positionx + (dirx);
		positionz = positionz - (dirz);
		break;
	// q-key
	case 113:
		q = false;
		calculate_direction_horizontal();
		//positionz = positionx - (dirx);
		positionx = positionx + (dirz);
		positionz = positionz - (dirx);
		break;
	case 'e':
		e = false;
		//positionz = positionx - (dirx);
		calculate_direction_horizontal();
		positionx = positionx - (dirz);
		positionz = positionz + (dirx);
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

void calculate_direction_horizontal()
{
	// create less possibilities for degrees
	if (degrees > 180)
	{
		degrees -= 360;

	}
	else if(degrees <= -180)
	{
		degrees += 360;
	}
	// Works
	if(degrees == 0 || degrees == 180)
	{
		if(degrees ==180)
		{ dirz = -1;
		}
		else{ dirz = 1;
		}
		dirx = 0;
	}
	// Works
	else if(degrees == 90 || degrees == -90)
	{
		dirx = -degrees/90;
		dirz = 0;
	}
	// Works
	else if(degrees > 0 && degrees < 90)
	{
		dirx = -degrees/90.0;
		dirz = 1 + dirx;
	}
	// Works
	else if(degrees > 90 && degrees < 180)
	{
		// Just act like degrees is between 0 and 90
		dirz = -((degrees/90.0) -1);
		dirx = -(1 + dirz);
	}
	// Works
	else if(degrees >-90 && degrees <0)
	{
		dirx = (degrees/-90.0);
		dirz = (1 - dirx);
		//dirx = 0;
	}
	// Works
	else if(degrees < -90 && degrees > -180)
	{ 
		dirz = -((degrees/-90.0) -1);
		dirx = (1 + dirz);
	}
	if(false)
	{ 
		std::cout<<"Dirz"<<endl;
		std::cout<<dirz<<endl;
    	std::cout<<"Dirx"<<endl;
	    std::cout<<dirx<<endl;
		std::cout<<"Positionx"<<endl;
		std::cout<<positionx<<endl;
		std::cout<<"Positionz"<<endl;
		std::cout<<positionz<<endl;
		std::cout<<"degrees"<<endl;
		std::cout<<degrees<<endl;
		std::cout<<"\n";
	   prevd = degrees;
	}
}

void calculate_direction(){
	// create less possibilities for degrees
	if (degrees > 180)
	{
		degrees -= 360;

	}
	else if(degrees <= -180)
	{
		degrees += 360;
	}
	// Works
	if(degrees == 0 || degrees == 180)
	{
		if(degrees ==180)
		{ dirz = -1;
		}
		else{ dirz = 1;
		}
		dirx = 0;
	}
	// Works
	else if(degrees == 90 || degrees == -90)
	{
		dirx = degrees/90;
		dirz = 0;
	}
	// Works
	else if(degrees > 0 && degrees < 90)
	{
		dirx = degrees/90.0;
		dirz = 1 - dirx;
	}
	// Works
	else if(degrees > 90 && degrees < 180)
	{
		// Just act like degrees is between 0 and 90
		long temp = degrees - 90;
		dirz = -((degrees/90.0) -1);
		dirx = 1 + dirz;
	}
	// Works
	else if(degrees >-90 && degrees <0)
	{
		dirx = -(degrees/-90.0);
		dirz = (1 + dirx);
	}
	else if(degrees < -90 && degrees > -180)
	{ 
		long temp = degrees + 90;
		dirz = -((degrees /-90.0)-1);
		dirx = -(1 + dirz);
	}
	if(false)
	{ 
		std::cout<<"Dirz"<<endl;
		std::cout<<dirz<<endl;
    	std::cout<<"Dirx"<<endl;
	    std::cout<<dirx<<endl;
		std::cout<<"Positionx"<<endl;
		std::cout<<positionx<<endl;
		std::cout<<"Positionz"<<endl;
		std::cout<<positionz<<endl;
		std::cout<<"degrees"<<endl;
		std::cout<<degrees<<endl;
		std::cout<<"\n";
	   prevd = degrees;
	}

}
GLfloat prevx = 0;
GLfloat prevz = 0;
GLuint t;
GLuint alien;
GLfloat prevdegr = 0;
Alien l = Alien(positionx, positionz);
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Rotate the che camera towards right angle
	glRotatef(degrees, 0, 1, 0);

	// Translate camera to right position
	glTranslatef(positionx, 0, positionz);
	prevd = degrees;


	l.draw_alien(positionx, positionz);

	glColor3f(1, 1, 1);
	glPushMatrix();
	GLfloat alienposx = 0;
	GLfloat alienposz = -20;
	glTranslatef(0, 0, -20);
	// Find relative position of player to cube
	GLfloat relposz = positionz - -alienposz;
	GLfloat relposx = -positionx - 0;
	GLfloat rad = 0;
	GLfloat degr;
	GLfloat c = sqrt(pow(relposx,2) + pow(relposz,2));
	if(prevx != positionx || prevz != positionz && 0)
	{

	std::cout<<"positionz"<<endl;
	std::cout<<positionz<<endl;
	std::cout<<"positionx"<<endl;
	std::cout<<positionx<<endl;
	std::cout<<"relposx"<<endl;
	std::cout<<relposx<<endl;
	std::cout<<"relposz"<<endl;
	std::cout<<relposz<<endl;
	std::cout<<"\n";
	prevx = positionx;
	prevz = positionz;
	}
	if(relposx == 0 )
	{
		degr = 0;
	}
	else if(relposz == 0)
	{
		degr = 90;
	}
	else if(abs(relposx) < abs(relposz))
	{
		rad = asin(relposx/c);
		degr = (rad * 180.0)/M_PI;
		if(relposz > 0&& relposx > 0)
		{
			degr = (90 -degr) + 90 ;
		}
		else if(relposx < 0 && relposz >0)
		{
			degr = (-90 - degr) -90;
		}


	}
	else{
		rad = asin(relposx/c);
		degr = (rad * 180.0)/M_PI;
		if(relposz > 0&& relposx > 0)
		{
			//std::cout<<"HERE"<<endl;
			degr = (90 -degr) + 90 ;
		}
		else if(relposx < 0 && relposz >0)
		{
			degr = (-90 - degr) -90;
		}
	}
	if(prevdegr != degr) 
	{
		//std::cout<<"degr"<<endl;
		//std::cout<<degr<<endl;
		prevdegr = degr;
	}


	glRotatef(degr, 0, 1, 0);

	glColor4f(1,1,1, 0);
	glEnable(GL_TEXTURE_2D);    glBindTexture(GL_TEXTURE_2D, t);
	
	glBegin(GL_QUADS);
	glTexCoord2f(1,1);
	glVertex3f(6, -20, 0);
	glTexCoord2f(1, 0);
	glVertex3f(6, 15, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 15, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-6, -20, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
	//glDepthMask(GL_TRUE);
	glPopMatrix();


	// THIS EXPERIMENT WORKS
	//Experiment for placement of object depending on rotated axis
	if(t == NULL)
	{
		std::cout<< "HELLOO"<<endl;
	}
	
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
	// glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, t);
	glBegin(GL_QUADS);
	glVertex3f(minx,miny, minz);
	glVertex3f(minx,maxy, minz);
	glVertex3f(minx,maxy, maxz);
	glVertex3f(minx,miny, maxz);
	glEnd();
	//glDisable(GL_TEXTURE_2D);
	
	
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
	degrees -= 2;
	}
	if(d)
	{
		degrees += 2;
	}
	if(w)
	{
	calculate_direction();
		positionx = positionx - (dirx);
		positionz = positionz + (dirz);
	}
	if(s){
	calculate_direction();
		positionx = positionx + (dirx);
		positionz = positionz - (dirz);
	}
	if(q)
	{
		calculate_direction_horizontal();
		positionx = positionx + (dirz);
		positionz = positionz - (dirx);

	}
	if(e)
	{
		calculate_direction_horizontal();
		positionx = positionx - (dirz);
		positionz = positionz + (dirx);
	}

	glutTimerFunc(25, update, 0);
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
	Image* image = loadBMP("alien.bmp");
	//alien = loadTexture(image);
	alien = LoadTextureRAW("alien.bmp", 1,90,90);

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(key_down_func);
	glutKeyboardUpFunc(key_up_func);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutIgnoreKeyRepeat(true);
	glutMainLoop();
	return 0;
}

