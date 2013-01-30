

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <GL/glut.h>
class Player{

public:
	Player();

	// Postion of the player
	GLfloat mpositionx;
	GLfloat mpositionz; 
	GLfloat mdegrees;
	GLfloat mdirx;
	GLfloat mdirz;

	void draw_player();
	void calculate_direction_horizontal();
	void calculate_direction();

};

#endif