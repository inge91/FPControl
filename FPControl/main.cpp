#include "StdAfx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>
#include <vector>

using namespace std;

GLfloat boxsize = 2;
bool rotating = false;
GLfloat degrees = 0;
GLfloat position = 0;
GLfloat positionx;
GLfloat positionz;
GLfloat dirx;
GLfloat dirz;

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 97:
		degrees -= 5;
		break;
	case 100:
		degrees += 5;
		break;
	case 119:
		position += 1;
		std::cout<<"dirz and dirx"<<endl;
		std::cout<<dirz<<endl;
		std::cout<<dirx<<endl;
		std::cout<<"\n";
		positionx = positionx - (dirx);
		positionz = positionz + (dirz);
		std::cout<<"position z and x"<<endl;
		std::cout<<positionx<<endl;
		std::cout<<positionz<<endl;
		std::cout<<"\n";
		break;
	case 115:
		position -= 1;
		positionx = positionx + (dirx);
		positionz = positionz - (dirz);
		std::cout<<positionx<<endl;
		std::cout<<positionz<<endl;
		std::cout<<"\n";
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
void calculate_direction(int degrees){

	// Works
	if(degrees == 0 || degrees == 180 || degrees == -180 || degrees == 360 || degrees == -360)
	{
		dirx = 0;
		dirz = 1;
	}
	// Works
	else if(degrees == 90 || degrees == -90)
	{
		dirx = degrees/90;
		dirz = 0;
	}
	// Works
	else if (degrees == 270 || degrees == -270)
	{
		dirx = degrees/-270;
		dirz = 0;
	}
	// Works
	else if(degrees > 0 && degrees < 90)
	{
		dirx = degrees/90.0;
		dirz = 1 - dirx;
	}
	else if(degrees < -270 && degrees > -360)
	{
		dirz = degrees / -360.0;
		dirx = 1 - dirz;
	}

	else if(degrees > 90 && degrees < 180)
	{
		dirz = degrees/180.0;
		dirx = 1 - dirz;
	}
	else if(degrees >-90 && degrees <0)
	{
		dirx = -(degrees/-90.0);
		dirz = (1 + dirx);
	}
	else if(degrees < -90 && degrees > -180)
	{ 
		dirz = degrees /-180.0;
		dirx = 1-dirz;
	}
	if(prevd != degrees)
	{
		std::cout<<"New dirx"<<endl;
		std::cout<<dirx<<endl;
		std::cout<<"New dirz"<<endl;
		std::cout<<dirz<<endl;
		std::cout<<degrees<<endl;
		std::cout<<"\n";

	}

}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Rotate the che camera towards right angle
	glRotatef(degrees, 0, 1, 0);

	calculate_direction(degrees);

	// Translate camera to right position
	glTranslatef(positionx, 0, positionz);
	prevd = degrees;

	// THIS EXPERIMENT WORKS
	//Experiment for placement of object depending on rotated axis
	glPushMatrix();
	// Rotate 90 degrees around y axis( x = z, z = x)
	glRotatef(90, 0, 1, 0);
	// Put the object in the distance
	glTranslatef(0, 0, -100);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glNormal3f(0, 0, 1);
	glVertex3f(-20, -20, 20 );
	glVertex3f( 20, -20, 20 );
	glVertex3f( 20,  20, 20 );
	glVertex3f(-20,  20, 20 );
	glEnd();
	glPopMatrix();



	glPushMatrix();
	// Rotate 90 degrees around y axis( x = z, z = x)
	glRotatef(90, 0, 1, 0);
	// Put the object in the distance
	glTranslatef(0, 0, 100);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glNormal3f(0, 0, 1);
	glVertex3f(-20, -20, 20 );
	glVertex3f( 20, -20, 20 );
	glVertex3f( 20,  20, 20 );
	glVertex3f(-20,  20, 20 );
	glEnd();
	glPopMatrix();



	// glTranslatef(0, 0, -position);
	glBegin(GL_QUADS);

	// Cube around camera
	// Front
	glColor3f(1, 0, 0);
	glNormal3f(0, 0, 1);
	glVertex3f(-20, -20, 20 );
	glVertex3f( 20, -20, 20 );
	glVertex3f( 20,  20, 20 );
	glVertex3f(-20,  20, 20 );
	
	// Back
	glNormal3f(0, 0, 1);
	glColor3f(0, 1, 0);
	glVertex3f(-20, -20, -20 );
	glVertex3f( 20, -20, -20 );
	glVertex3f( 20,  20, -20 );
	glVertex3f(-20,  20, -20 );

	// Left 
	glColor3f(0, 0, 1);
	glNormal3f(1, 0, 0);
	glVertex3f(-20, -20, -20 );
	glVertex3f(-20,  20, -20 );
	glVertex3f(-20,  20,  20 );
	glVertex3f(-20,  -20,  20 );
	glEnd();

	glutSwapBuffers();
}

//Called every 25 milliseconds
void update(int value) {
	glutPostRedisplay();
	if(degrees >360)
	{
		degrees -= 360;
	}
	else if(degrees < -360)
	{
		degrees += 360;
	}
	glutTimerFunc(2, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("FPS");
	//glutFullScreen();
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	
	glutMainLoop();
	return 0;
}

