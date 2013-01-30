#include "Stdafx.h";
#include "room.h"

Room::Room()
{
	update_level();
}

void Room::update_level()
{

	// This still needs to be implemented!
}


void Room::draw_level()
{


	GLfloat maxy = 50;
	GLfloat miny = -20;
	GLfloat minx = -150;
	GLfloat maxx = 150;
	GLfloat minz = -150;
	GLfloat maxz = 150;
	GLfloat lengthx = std::abs(minx) +maxx;
	GLfloat lengthy = std::abs(miny) +maxy;
	
	
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1,1, 0);
    glBindTexture(GL_TEXTURE_2D, mwall);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(minx,miny, minz);
	glTexCoord2f(0, 0);
	glVertex3f(minx,maxy, minz);
	glTexCoord2f(1, 0);
	glVertex3f(minx,maxy, maxz);
	glTexCoord2f(1, 1);
	glVertex3f(minx,miny, maxz);
	glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(minx, maxy, minz);
	glVertex3f(maxx, maxy, minz);
	glVertex3f(maxx, maxy, maxz);
	glVertex3f(minx, maxy, maxz);

    //glBindTexture(GL_TEXTURE_2D, mtile);
	glColor4f(1,1,1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(minx, miny, minz);
	glTexCoord2f(40, 0);
	glVertex3f(maxx, miny, minz);
	glTexCoord2f(40, 40);
	glVertex3f(maxx, miny, maxz);
	glTexCoord2f(0, 40);
	glVertex3f(minx, miny, maxz);
	glEnd();
}

void Room::set_textures()
{


	mtile = GetTexture("tile.tga");
	mwall = GetTexture("brick_wall.jpg");
}


