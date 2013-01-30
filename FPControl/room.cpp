#include "Stdafx.h";
#include "room.h"

Room::Room()
{
    maxy = 50;
    miny = -20;
    minx = -150;
    maxx = 150;
    minz = -150;
    maxz = 150;
	update_level();
}

void Room::update_level()
{

	// This still needs to be implemented!
}


void Room::draw_level()
{

	
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

	glTexCoord2f(0, 1);
	glVertex3f(maxx,miny, minz);
	glTexCoord2f(0, 0);
	glVertex3f(maxx,maxy, minz);
	glTexCoord2f(1, 0);
	glVertex3f(maxx,maxy, maxz);
	glTexCoord2f(1, 1);
	glVertex3f(maxx,miny, maxz);

	glTexCoord2f(0, 1);
	glVertex3f(minx,miny, minz);
	glTexCoord2f(0, 0);
	glVertex3f(minx,maxy, minz);
	glTexCoord2f(1, 0);
	glVertex3f(maxx,maxy, minz);
	glTexCoord2f(1, 1);
	glVertex3f(maxx,miny, minz);

	glTexCoord2f(0, 1);
	glVertex3f(minx,miny, maxz);
	glTexCoord2f(0, 0);
	glVertex3f(minx,maxy, maxz);
	glTexCoord2f(1, 0);
	glVertex3f(maxx,maxy, maxz);
	glTexCoord2f(1, 1);
	glVertex3f(maxx,miny, maxz);
	glEnd();

    //glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	draw_roof();
	draw_floor();


}

void Room::draw_roof()
{

	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mroof);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(minx, maxy, minz);
	glTexCoord2f(1, 0);
	glVertex3f(maxx, maxy, minz);
	glTexCoord2f(1, 1);
	glVertex3f(maxx, maxy, maxz);
	glTexCoord2f(0, 1);
	glVertex3f(minx, maxy, maxz);
	glEnd();
	glDisable(GL_TEXTURE_2D);


}

void Room::draw_floor()
{
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mtile);
	glBegin(GL_QUADS);
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
	glDisable(GL_TEXTURE_2D);

}


void Room::set_textures()
{


	mtile = GetTexture("tile3.jpg");
	mwall = GetTexture("brick_wall2.jpg");
	mroof = GetTexture("roof.jpg");
}

