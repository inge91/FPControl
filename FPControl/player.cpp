#include "stdafx.h"
#include "player.h"

Player::Player()
{
	mpositionx = 0;
	mpositionz = 0;
	mdegrees = 0 ;

	// set value of dirz and mdirx
	calculate_direction();
}

GLfloat prevx = 0;
GLfloat prevz = 0;

void Player::draw_player()
{

	// Rotate the camera towards right angle
	glRotatef(mdegrees, 0, 1, 0);

	if(prevx != mpositionx || prevz != mpositionz && 0)
	{

		cout<<"("<<mpositionx<<","<<mpositionz<<")"<<endl;
		prevx = mpositionx;
		prevz = mpositionz;


	}
	// Translate camera to right position
	glTranslatef(mpositionx, 0, mpositionz);
	
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