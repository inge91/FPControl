#include "Stdafx.h";
#include "alien.h";

Alien::Alien( GLfloat camerax, GLfloat cameraz)
{
	mposx = 30;
	mposz = 20;
	// Set the degrees
	calculate_degrees(camerax, cameraz); 
}


GLfloat prevxx;
GLfloat prevzz;
GLfloat prevdeg;
void Alien::calculate_degrees( GLfloat camerax, GLfloat cameraz)
{

	// Find relative position of player to cube
	GLfloat relposz = cameraz - -mposz;
	GLfloat relposx = -camerax - mposx;
	GLfloat rad = 0;
	GLfloat c = sqrt(pow(relposx,2) + pow(relposz,2));

	if(prevxx != camerax || prevzz != cameraz)
	{

	std::cout<<"positionz"<<endl;
	std::cout<<cameraz<<endl;
	std::cout<<"positionx"<<endl;
	std::cout<<camerax<<endl;
	std::cout<<"relposx"<<endl;
	std::cout<<relposx<<endl;
	std::cout<<"relposz"<<endl;
	std::cout<<relposz<<endl;
	std::cout<<"\n";
	prevxx = camerax;
	prevzz = cameraz;
	}
	if(relposx == 0 )
	{
		mdegrees = 0;
	}
	else if(relposz == 0)
	{
		mdegrees = 90;
	}
	else if(abs(relposx) < abs(relposz))
	{
		rad = asin(relposx/c);
		mdegrees = (rad * 180.0)/M_PI;
		if(relposz > 0&& relposx > 0)
		{
			mdegrees = (90 -mdegrees) + 90 ;
		}
		else if(relposx < 0 && relposz >0)
		{
			mdegrees = (-90 - mdegrees) -90;
		}


	}
	else{
		rad = asin(relposx/c);
		mdegrees = (rad * 180.0)/M_PI;
		if(relposz > 0&& relposx > 0)
		{
			//std::cout<<"HERE"<<endl;
			mdegrees = (90 -mdegrees) + 90 ;
		}
		else if(relposx < 0 && relposz >0)
		{
			mdegrees = (-90 - mdegrees) -90;
		}
	}
	if(prevdeg != mdegrees)
	{std::cout<<mdegrees<<endl;
	std::cout<<"\n";
	prevdeg = mdegrees;
	}

	/*
	else{
		rad = asin(relposx/c);
		mdegrees = (rad * 180.0)/M_PI;
		if(relposz > 0&& relposx > 0)
		{
			mdegrees = (90 -mdegrees) + 90 ;
		}
		else if(relposx < 0 && relposz >0)
		{
			mdegrees = (-90 - mdegrees) -90;
		}
	}
	*/

}

void Alien::draw_alien(GLfloat camerax, GLfloat cameraz)
{
	calculate_degrees(camerax, cameraz);

	glPushMatrix();
	glTranslatef(mposx, 0, mposz);
	glRotatef(mdegrees, 0, 1, 0);

	glColor4f(1,1,1, 0);
	//glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, t);
	
	glBegin(GL_QUADS);
	glVertex3f(6, -20, 0);
	glVertex3f(6, 15, 0);
	glVertex3f(-6, 15, 0);
	glVertex3f(-6, -20, 0);
	glEnd();
	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
	//glDepthMask(GL_TRUE);
	glPopMatrix();
}
