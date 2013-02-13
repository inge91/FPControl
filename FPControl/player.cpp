#include "stdafx.h"
#include "player.h"

Player::Player()
{
	mpositionx = 0;
	mpositiony = -12;
	mpositionz = 0;
	mprevx = mpositionx;
	mprevz = mpositionz;
	mdegrees = 0 ;

	// set value of dirz and mdirx
	calculate_direction();
	initiate_sounds();
}

void  Player::initiate_sounds()
{
	//init FMOD
	FMOD::System_Create(&msys);// create an instance of the game engine
	msys->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels


	//load sounds
	msys->createSound("walk5.mp3", FMOD_HARDWARE, 0, &mwalk1);
	mwalk1->setMode(FMOD_LOOP_OFF);
	msys->createSound("walk6.mp3", FMOD_HARDWARE, 0, &mwalk2);
	mwalk1->setMode(FMOD_LOOP_OFF);
	
    glEnable(GL_DEPTH_TEST); // check for depth
    

}

GLfloat prevx = 0;
GLfloat prevz = 0;
bool up = false;
bool first = true;

void Player::draw_player()
{

	// Rotate the camera towards right angle
	glRotatef(mdegrees, 0, 1, 0);

	if(prevx != mpositionx || prevz != mpositionz )
	{

		prevx = mpositionx;
		prevz = mpositionz;

		if(mpositiony <= -14)
		{
			mpositiony += 0.15;
			up = false;

		}
		else if(mpositiony >= -12)
		{


			if(first)
			{
				msys->playSound(FMOD_CHANNEL_FREE, mwalk1, false, 0);
				first = false;
			}
			else{				first = true;

			}
			mpositiony -= 0.15;
			up = true;


		}
		if(up)
		{
			mpositiony -= 0.15;
		}
		else{
			mpositiony +=0.15;
		}

	}
	else{
		if(mpositiony <= -12)
		{
			mpositiony += 0.15;
		}
	}

	// Translate camera to right position
	glTranslatef(mpositionx, mpositiony, mpositionz );
	mprevx = mpositionx;
	mprevz = mpositionz;
	
	glColor3f(1,0, 1);
	glBegin(GL_QUADS);
	glVertex3f(-2, -20 ,0);
	glVertex3f(-2, 10,0);
	glVertex3f(2 ,10,0);
	glVertex3f(2, -20, 0);
	glEnd();
	
}

void Player::calculate_direction_horizontal()
{
	// create less possibilities for mdegrees
	if (mdegrees > 180)
	{
		mdegrees -= 360;

	}
	else if(mdegrees <= -180)
	{
		mdegrees += 360;
	}
	// Works
	if(mdegrees == 0 || mdegrees == 180)
	{
		if(mdegrees ==180)
		{ mdirz = -1;
		}
		else{ mdirz = 1;
		}
		mdirx = 0;
	}
	// Works
	else if(mdegrees == 90 || mdegrees == -90)
	{
		mdirx = -mdegrees/90;
		mdirz = 0;
	}
	// Works
	else if(mdegrees > 0 && mdegrees < 90)
	{
		mdirx = -mdegrees/90.0;
		mdirz = 1 + mdirx;
	}
	// Works
	else if(mdegrees > 90 && mdegrees < 180)
	{
		// Just act like mdegrees is between 0 and 90
		mdirz = -((mdegrees/90.0) -1);
		mdirx = -(1 + mdirz);
	}
	// Works
	else if(mdegrees >-90 && mdegrees <0)
	{
		mdirx = (mdegrees/-90.0);
		mdirz = (1 - mdirx);
		//mdirx = 0;
	}
	// Works
	else if(mdegrees < -90 && mdegrees > -180)
	{ 
		mdirz = -((mdegrees/-90.0) -1);
		mdirx = (1 + mdirz);
	}
}

void Player::calculate_direction(){
	// create less possibilities for mdegrees
	if (mdegrees > 180)
	{
		mdegrees -= 360;

	}
	else if(mdegrees <= -180)
	{
		mdegrees += 360;
	}
	// Works
	if(mdegrees == 0 || mdegrees == 180)
	{
		if(mdegrees ==180)
		{ mdirz = -1;
		}
		else{ mdirz = 1;
		}
		mdirx = 0;
	}
	// Works
	else if(mdegrees == 90 || mdegrees == -90)
	{
		mdirx = mdegrees/90;
		mdirz = 0;
	}
	// Works
	else if(mdegrees > 0 && mdegrees < 90)
	{
		mdirx = mdegrees/90.0;
		mdirz = 1 - mdirx;
	}
	// Works
	else if(mdegrees > 90 && mdegrees < 180)
	{
		// Just act like mdegrees is between 0 and 90
		long temp = mdegrees - 90;
		mdirz = -((mdegrees/90.0) -1);
		mdirx = 1 + mdirz;
	}
	// Works
	else if(mdegrees >-90 && mdegrees <0)
	{
		mdirx = -(mdegrees/-90.0);
		mdirz = (1 + mdirx);
	}
	else if(mdegrees < -90 && mdegrees > -180)
	{ 
		long temp = mdegrees + 90;
		mdirz = -((mdegrees /-90.0)-1);
		mdirx = -(1 + mdirz);
	}

}