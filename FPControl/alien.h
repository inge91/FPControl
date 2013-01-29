#ifndef PLATFORM_H_INCLUDED

#define PLATFORM_H_INCLUDED

#include <GL/glut.h>
#include "StdAfx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class Alien
{
public:
	Alien(GLfloat camerax, GLfloat camera);
	// x and y position of the alien
	GLfloat mposx;
	GLfloat mposz;
	// Rotation of the alien
	GLfloat mdegrees;
	void draw_alien(GLfloat camerax, GLfloat camer�az);


private:
	void calculate_degrees(GLfloat camerax, GLfloat cameraz);
	

};
#endif