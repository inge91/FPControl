#include "StdAfx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <cmath>
using namespace std;
void calculate_direction();
void calculate_direction_horizontal();
GLuint LoadTextureRAW( const char * filename, int wrap );

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
GLfloat prevdegr = 0;
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Rotate the che camera towards right angle
	glRotatef(degrees, 0, 1, 0);

	// Translate camera to right position
	glTranslatef(positionx, 0, positionz);
	prevd = degrees;



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
	if(prevx != positionx || prevz != positionz)
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

	}
	else{
		rad = asin(relposx/c);
		degr = (rad * 180.0)/M_PI;
	}
	if(prevdegr != degr) 
	{
		std::cout<<"rad"<<endl;
		std::cout<<rad<<endl;
		prevdegr = degr;
	}


	glRotatef(degr, 0, 1, 0);

	glBegin(GL_QUADS);
	glVertex3f(6, -20, 0);
	glVertex3f(6, 15, 0);
	glVertex3f(-6, 15, 0);
	glVertex3f(-6, -20, 0);
	glEnd();
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
	
	//glColor4f(1, 0,0, 0);
	  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, t);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(minx,miny, minz);
	glTexCoord2f(0, 20);
	glVertex3f(minx,maxy, minz);
	glTexCoord2f(20, 20);
	glVertex3f(minx,maxy, maxz);
	glTexCoord2f(20, 0);
	glVertex3f(minx,miny, maxz);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(minx, maxy, minz);
	glVertex3f(maxx, maxy, minz);
	glVertex3f(maxx, maxy, maxz);
	glVertex3f(minx, maxy, maxz);

	glColor3f(1, 0, 0);
	glVertex3f(minx, miny, minz);
	glVertex3f(maxx, miny, minz);
	glVertex3f(maxx, miny, maxz);
	glVertex3f(minx, miny, maxz);
	glEnd();

	
	glutSwapBuffers();
}
// load a 256x256 RGB .RAW file as a texture
// Taken from 
GLuint LoadTextureRAW( const char * filename, int wrap )
{
    GLuint texture;
    int width, height;
    BYTE * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer
    width = 400;
    height = 400;
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
	
	  t = LoadTextureRAW("bricks3.raw", 1);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(key_down_func);
	glutKeyboardUpFunc(key_up_func);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutIgnoreKeyRepeat(true);
	glutMainLoop();
	return 0;
}

