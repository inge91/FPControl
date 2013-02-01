

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <GL/glut.h>
#include <iostream>
#include <windows.h> 
#include <mmsystem.h>
using namespace std;
class Player{

public:
	Player();

	// Postion of the player
	GLfloat mpositionx;
	GLfloat mpositiony; 
	GLfloat mpositionz; 
	GLfloat mprevx;
	GLfloat mprevz;
	GLfloat mdegrees;
	GLfloat mdirx;
	GLfloat mdirz;

	void draw_player();
	void calculate_direction_horizontal();
	void calculate_direction();

};

#endif