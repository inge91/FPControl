#include "Stdafx.h";
#include "alien.h";

Alien::Alien( GLfloat camerax, GLfloat cameraz)
{
	mposx = 0;
	mposz = -40;
	mspeed = 0.4;
	// Set the degrees
	calculate_degrees(camerax, cameraz); 
	//set_texture();


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
			mdegrees = (90 -mdegrees) + 90 ;
		}
		else if(relposx < 0 && relposz >0)
		{
			mdegrees = (-90 - mdegrees) -90;
		}
	}

}

void Alien::draw_alien(GLfloat camerax, GLfloat cameraz)
{
	calculate_degrees(camerax, cameraz);

	glPushMatrix();
	glTranslatef(mposx, 0, mposz);
	glRotatef(mdegrees, 0, 1, 0);

	glColor4f(1,1,1, 1);

	glEnable(GL_TEXTURE_2D);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, malien);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(5,  -20, 0);
	glTexCoord2f(0, 1); glVertex3f(5,   8, 0);
	glTexCoord2f(1, 1); glVertex3f(-5,  8, 0);
	glTexCoord2f(1, 0); glVertex3f(-5, -20, 0);
	glEnd();
	glDisable (GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
	//glDepthMask(GL_TRUE);
	glPopMatrix();

	// Give new position to alien
	move_alien(camerax, cameraz);

}

GLfloat prevcx = 0;
GLfloat prevcz = 0;
GLfloat prevvv = 0;
void Alien::move_alien(GLfloat camerax, GLfloat cameraz)
{
	camerax = -camerax;
	cameraz = -cameraz;
	if(camerax !=prevcx || cameraz != prevcz && 0)
	{
		std::cout<<"camerax"<<endl;
		std::cout<<camerax<<endl;
		std::cout<<"cameraz"<<endl;
		std::cout<<cameraz<<endl;
		std::cout<<"mposx"<<endl;
		std::cout<<mposx<<endl;
		std::cout<<"mposz"<<endl;
		std::cout<<mposz<<endl;

		std::cout<<"\n";
		prevcz = cameraz;
		prevcx = camerax;
	}
	if (camerax > mposx )
	{
		if(cameraz > mposz)
		{
			mposx += mspeed/2;
			mposz += mspeed/2;
		}
		else if( cameraz < mposz)
		{
			mposx += mspeed/2;
			mposz -= mspeed/2;
		}
		else{
			mposx += mspeed;
		}
	}

	else if (camerax < mposx )
	{
		if(cameraz > mposz)
		{
			mposx -= mspeed/2;
			mposz += mspeed/2;
		}
		else if( cameraz < mposz)
		{
			mposx -= mspeed/2;
			mposz -= mspeed/2;
		}
		else{
			mposx -= mspeed;
		}
	}
	else{
		if(cameraz > mposz)
		{
			//std::cout<<cameraz<<std::endl;
			//std::cout<<mposz<<std::endl;
			mposz += mspeed;
		}
		else if( cameraz < mposz)
		{
			mposz -= mspeed;
		}
		else{
			// Nothing to do!
		}

	}
}

void Alien::set_texture()
{
	std::string a = "alien7.tga";
	malien = GetTexture(a);
}