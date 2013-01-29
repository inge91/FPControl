

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <GL/glut.h>
class Player{

public:
	Player();

	// Postion of the player
	GLfloat mpositionx;
	GLfloat mpositionz; 


	void draw_player();
	

};

#endif