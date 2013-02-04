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
#include "player.h"
using namespace std;
class Room
{
public:
	Room(Player *p);
	// keeps track of the coordinates that make the building
	vector<pair<pair<GLfloat, GLfloat>, pair<GLfloat, GLfloat>>> mcoordinates;
	void draw_level();
	void set_textures();
	pair<GLfloat, GLfloat> detect_collision(pair<GLfloat, GLfloat>prev, pair<GLfloat, GLfloat>next);

private:
	void update_level();
	void draw_floor();
	void draw_walls();
	void draw_roof();
	void load_coords();
	void set_walls();
	void set_start();
	void set_end();
	void set_player_position(GLfloat x, GLfloat z);
	
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
	GLfloat beginx;
	GLfloat beginz;
	string mlevelno;
	Player *mp;

};
#endif