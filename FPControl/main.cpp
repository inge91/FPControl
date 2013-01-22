#include "StdAfx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>

using namespace std;

GLfloat boxsize = 2;
bool rotating = false;
GLfloat degrees = 1;
GLfloat position = 0;

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
		break;
	case 115:
		position -= 1;
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


void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glPushMatrix();
	glRotatef(degrees, 0, 1, 0);
	glTranslatef(0, 0, position);
	//glPopMatrix;


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

