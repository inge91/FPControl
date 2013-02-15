#ifndef SIGNS_H_INCLUDED
#define SIGNS_H_INCLUDED
#include <GL/glut.h>
#include "StdAfx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <iostream>
#include "main.h"
#include "circular_array.h"

#include <cmath>
#include <fstream>

using namespace std;
class Signs
{

	public: 
		Signs();
		// Draw signs when the player is at poisition x z.
		void draw_signs(GLfloat x, GLfloat z);
		// Add sign with position x z
		void add_sign(GLfloat x, GLfloat z);
		void set_textures();
		

	private:
		// Find the orientation of the sign with poisition mposx, mposz
		GLfloat calculate_degrees(GLfloat x, GLfloat z, GLfloat mposx, GLfloat mposz);
		
		CircularArray<pair<GLfloat, GLfloat>> msigns;
		GLuint mtextures[5];
	
};

#endif