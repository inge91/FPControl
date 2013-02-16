#include "stdafx.h"
#include "signs.h"

using namespace std;
Signs::Signs()
	// Initializer list
	// Create the sign list
	:msigns()
{

	// TODO load textures
}


void Signs::set_textures()
{
		mtextures[0] = GetTexture("sign1.png");
		mtextures[1] = GetTexture("sign2.png");
		mtextures[2] = GetTexture("sign3.png");
		mtextures[3] = GetTexture("sign4.png");
		mtextures[4] = GetTexture("sign5.png");
}


// Calculates how the sign should be rotated to always face the player at the front
GLfloat Signs::calculate_degrees( GLfloat camerax, GLfloat cameraz, GLfloat mposx, GLfloat mposz)
{

	GLfloat mdegrees; 

	// Find relative position of player to cube
	GLfloat relposz = cameraz - -mposz;
	GLfloat relposx = -camerax - mposx;
	GLfloat rad = 0;

	// The distance between player and sign
	GLfloat c = sqrt(pow(relposx,2) + pow(relposz,2));

	// If only differing in the y position, angle = 0
	if(relposx == 0 )
	{
		mdegrees = 0;
	}
	// If only differing in the x position, angle = 90
	else if(relposz == 0)
	{
		mdegrees = 90;
	}
	// All oother cases
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
	return mdegrees;

}

// Check if element is in array
bool in(int arr[], int element)
{
	for(int i = 0; i < 5; i++)
	{
		if(arr[i] == element)
		{
			return true;
		}
	}
	return false;
}

void Signs::draw_signs(GLfloat camerax, GLfloat cameraz)
{
	

	//Sort the signs on distance to the player
	int arr[5]= {-1,-1, -1, -1, -1};
	pair<GLfloat, int> tempd (NULL, NULL);
	pair<GLfloat, GLfloat> tempp;
	for(int k = 0; k < 5; k++)
	{
		for(int l = 0; l < 5; l++)
		{
			// If index already in array skip it
			if( in(arr, l) )
			{
				continue;
			}
			else{

				tempp = msigns.get_element(l);
				GLfloat relposz = cameraz - tempp.second;
				std::cout<< cameraz<<endl;
				std::cout<< camerax<<endl;
				GLfloat relposx = camerax -tempp.first;
				GLfloat tempdist = sqrt(pow(relposx,2) + pow(relposz,2));
				// Check if tempd is not yet filled
				if(tempd.first == NULL)
				{

				
					tempd.first = tempdist;
					tempd.second = l;
				}
				else if(tempd.first > tempdist)
				{
					tempd.first = tempdist;
					tempd.second = l;
				}
			}
		}
		// Fill in array element
		arr[k] = tempd.second;
		tempd.first = NULL;
		tempd.second = NULL;
	}

	
	// You have to start at the back
	for(int i = 4; i > -1 ; i--)
	{
		
		pair<GLfloat, GLfloat> p = msigns.get_element(arr[i]);
		// temp mposx mposz
		GLfloat mposx = p.first;
		GLfloat mposz = p.second;
		if (mposx == 0 && mposz == 0)
		{
			continue;
		}
		// Loop  thourhg vector and do for all these signs

		glPushMatrix();
		glTranslatef(-mposx, 0, -mposz);
		GLfloat mdegrees = calculate_degrees(camerax, cameraz, -mposx, -mposz);

		glRotatef(mdegrees, 0, 1, 0);

		glColor4f(1,1,1, 1);

		glEnable(GL_TEXTURE_2D);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable (GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, mtextures[arr[i]]);
		glBegin(GL_QUADS);
		// Draw the rectangle the alien will be blitted on
		glTexCoord2f(1, 0); glVertex3f(5,  -20, 0);
		glTexCoord2f(1, 1); glVertex3f(5,   8, 0);
		glTexCoord2f(0, 1); glVertex3f(-5,  8, 0);
		glTexCoord2f(0, 0); glVertex3f(-5, -20, 0);
	
		glEnd();
		glDisable (GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		//glDisable(GL_BLEND);
		//glDepthMask(GL_TRUE);
		glPopMatrix();
	}
}

// Add new position to signs
void Signs::add_sign(GLfloat x, GLfloat z)
{
	pair<GLfloat, GLfloat> p (x,z);
	msigns.add_element(p);
}