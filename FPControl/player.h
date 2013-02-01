

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <GL/glut.h>
#include <iostream>
#include <windows.h> 
#include <mmsystem.h>
#include "fmod.hpp" //fmod c++ header
#pragma comment( lib, "fmodex_vc.lib" ) // fmod library
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

	void initiate_sounds();
	FMOD::System     *msys; //handle to FMOD engine
	FMOD::Sound      *mwalk1; //sound that will be loaded and played
	FMOD::Sound      *mwalk2; //sound that will be loaded and played

};

#endif