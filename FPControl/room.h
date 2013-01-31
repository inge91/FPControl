#ifndef ROOM_H_INCLUDED

#define ROOM_H_INCLUDED

#include <GL/glut.h>
#include "StdAfx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "main.h"
using namespace std;
class Room
{
public:
	Room();
	// keeps track of the coordinates that make the building
	vector<pair<pair<GLfloat, GLfloat>, pair<GLfloat, GLfloat>>> mcoordinates;
	void draw_level();
	void set_textures();
	bool detect_collision(pair<GLfloat, GLfloat>prev, pair<GLfloat, GLfloat>next);

private:
	void update_level();
	void draw_floor();
	void draw_walls();
	void draw_roof();
	void load_coords();
	
	// Textures
	GLuint mtile;
	GLuint mwall;
	GLuint mroof;

	GLfloat maxy;
	GLfloat miny;
	GLfloat minx;
	GLfloat maxx;
	GLfloat minz;
	GLfloat maxz;
	string mlevelno;

};
#endif