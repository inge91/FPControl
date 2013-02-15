#include "Stdafx.h"
#include "room.h"

Room::Room(Player *p)
{
	mp = p;
    maxy = 30;
    miny = -20;
    minx = -150;
    maxx = 150;
    minz = -150;
    maxz = 150;
	mlevelno ="16";
	update_level();
	set_sound();
}


void Room::set_sound()
{
//init FMOD
	FMOD::System_Create(&msys);// create an instance of the game engine
	msys->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels


	//load sounds
	msys->createSound("end.mp3", FMOD_HARDWARE|FMOD_LOOP_NORMAL, 0, &mend);
	msys->playSound(FMOD_CHANNEL_FREE, mend, true, &mc2);
	mc2->setVolume(0.9);
	mc2->setPaused(false);

    
}

// Draw the room
void Room::draw_level()
{
	draw_walls();
	draw_roof();
	draw_floor();
}

// Draw the walls
void Room::draw_walls()
{
	glDisable(GL_LIGHTING);
	
	GLfloat x1;
	GLfloat y1;
	GLfloat x2;
	GLfloat y2;

	pair <pair<GLfloat, GLfloat>, pair<GLfloat, GLfloat>>  p;
	for (unsigned i=0; i<mcoordinates.size(); i++)
	{
		p = mcoordinates.at(i);
		x1 = p.first.first;
		y1 = p.first.second;
		x2 = p.second.first;
		y2 = p.second.second;


	if (x1 == x2)
		{
			GLfloat size = abs(y2- y1);
			GLfloat repeat = size/90;
			
			//std::cout<< y2<<","<<y1<< endl;
			//std::cout<< size<<endl;
			glEnable(GL_TEXTURE_2D);
			//glEnable(GL_TEXTURE_2D);
			glColor4f(1, 1,1, 0);
			glBindTexture(GL_TEXTURE_2D, mwall);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(x1,miny, y1);
			glTexCoord2f(0, 0);
			glVertex3f(x1,maxy, y1);
			glTexCoord2f(repeat, 0);
			glVertex3f(x2,maxy, y2);
			glTexCoord2f(repeat, 1);
			glVertex3f(x2,miny, y2);
			glEnd();
		}
		else{
			glEnable(GL_TEXTURE_2D);
			//glEnable(GL_TEXTURE_2D);
			glColor4f(1, 1,1, 0);
			glBindTexture(GL_TEXTURE_2D, mwall);
			glBegin(GL_QUADS);

			GLfloat size = abs(x2- x1);
			GLfloat repeat = size/90;
			
			glTexCoord2f(0, 1);
			glVertex3f(x1,miny, y1);
			glTexCoord2f(0, 0);
			glVertex3f(x1,maxy, y1);
			glTexCoord2f(repeat, 0);
			glVertex3f(x2,maxy, y2);
			glTexCoord2f(repeat, 1);
			glVertex3f(x2,miny, y2);
			glEnd();

		}
		
	}
}

void Room::draw_roof()
{

	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mroof);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(minx - mp->mpositionx, maxy - mp->mpositiony , minz - mp->mpositionz);
	glTexCoord2f(3, 0);
	glVertex3f(maxx - mp->mpositionx, maxy - mp->mpositiony, minz - mp->mpositionz);
	glTexCoord2f(3, 3);
	glVertex3f(maxx - mp->mpositionx, maxy - mp->mpositiony , maxz - mp->mpositionz);
	glTexCoord2f(0, 3);
	glVertex3f(minx - mp->mpositionx, maxy - mp->mpositiony, maxz - mp->mpositionz);
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
	glVertex3f(minx * 10, miny, minz * 10);
	glTexCoord2f(80, 0);
	glVertex3f(maxx * 10, miny, minz * 10);
	glTexCoord2f(80, 80);
	glVertex3f(maxx * 10, miny, maxz * 10);
	glTexCoord2f(0, 80);
	glVertex3f(minx * 10, miny, maxz * 10);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}


void Room::set_textures()
{

	//mtile = GetTexture("tile3.jpg");
	mtile = GetTexture("grass_tile4.png");
	mwall = GetTexture("brick_wall2.jpg");
	//mroof = GetTexture("roof.jpg");
	mroof = GetTexture("stars.jpg");
}

void Room::set_aliens()
{

}

void Room::set_end()
{
	std::cout<<"putting in the end position"<<endl;
string leveltxt = string("level") +  string(mlevelno) + string("end.txt");
	ifstream myfile (leveltxt);

	if( myfile == NULL)
	{
		std::cout<<"Couldn't find the file"<<endl;

	}
	else{

	string line;
	
while(getline(myfile, line))
		{

		GLfloat a = -1;
		GLfloat b = -1; 
		string temp;

		
		for(int i = 0; i < line.length(); i++)
		{
			if(line[i]== ' ' || line[i] == ',')
			{
				if(temp.length() > 0)
				{
					// Fill the next number
					if(a == -1)
					{
						a = atoi(temp.c_str());
					}
					else if (b == -1)
					{
						b = atoi(temp.c_str());
					}
					else
					{
						std::cout<<"Too many numbers for start"<<endl;
					}

					// Reset temp
					temp = "";
				}
			}
			else{
				temp += line[i];
			}

		}

		// Fill the next number
		if(a == -1)
		{
			a = atoi(temp.c_str());
		}
		else if (b == -1)
		{
			b = atoi(temp.c_str());
		}
		else
		{
			std::cout<<"Too many numbers for start"<<endl;
		}
		if(a == -1 || b == -1)
		{
			std::cout<<"too few numbers to start"<<endl;
		}
		else{

			// create a tile like structure
			GLfloat tempa = a;
			GLfloat tempb = b;
			a = ((a - 15) * 10) - 5;
			b = ((b - 15) * 10) - 5;
			int c = ((tempa - 15) * 10) + 5;
			int d = ((tempb - 15) * 10) + 5;
			pair <GLfloat, GLfloat> p1 (a,b);
			pair <GLfloat, GLfloat> p2 (c,d);
			pair <pair<GLfloat, GLfloat>, pair<GLfloat, GLfloat>>  p3 (p1, p2);
			mendpositions.push_back(p3);	
			std::cout<<"tile: "<<a<< ", " <<b<< " "<< c<< ","<< d <<endl;
		}
	}
	}
	// Done with the file
	myfile.close();
}

// Fill mcoordinates with the coords from file level[]coords.txt
void Room::set_walls()
{

// Clear the coordinate vector
	mcoordinates.clear();

	string leveltxt = string("level") +  string(mlevelno) + string("coords.txt");
	std::cout<<leveltxt<<endl;
	ifstream myfile (leveltxt);

	if( myfile == NULL)
	{
		std::cout<<"Couldn't find the file"<<endl;

	}
	else{

	string line;
	while(getline(myfile, line))
	{
		std::cout<<line<<endl;
		GLfloat a = -1;
		GLfloat b = -1; 
		GLfloat c = -1;
		GLfloat d = -1;
		string temp;

		for(int i = 0; i < line.length(); i++)
		{
			if(line[i]== ' ' || line[i] == ',')
			{
				if(temp.length() > 0)
				{
					// Fill the next number
					if(a == -1)
					{
						a = atoi(temp.c_str());
					}
					else if (b == -1)
					{
						b = atoi(temp.c_str());
					}
					else if (c == -1)
					{
						c = atoi(temp.c_str());
					}
					else if (d = -1)
					{
						d = atoi(temp.c_str());
					}
					else
					{
						std::cout<<"Too many numbers"<<endl;
					}

					// Reset temp
					temp = "";
				}
			}
			else{
				temp += line[i];
			}

		}

		// Fill the next number
		if(a == -1)
		{
			a = atoi(temp.c_str());
		}
		else if (b == -1)
		{
			b = atoi(temp.c_str());
		}
		else if (c == -1)
		{
			c = atoi(temp.c_str());
		}
		else if (d = -1)
		{
			d = atoi(temp.c_str());
		}
		else
		{
			std::cout<<"Too many numbers"<<endl;
		}
		// Make the right size conversion
		a = (a - 15) * 10;
		b = (b - 15) * 10;
		c = (c - 15) * 10;
		d = (d - 15) * 10;
		pair <GLfloat, GLfloat> p1 (a,b);
		pair <GLfloat, GLfloat> p2 (c,d);
		pair <pair<GLfloat, GLfloat>, pair<GLfloat, GLfloat>>  p3 (p1, p2);
		mcoordinates.push_back(p3);	
	}
	
	// Done with the file
	myfile.close();

}

}


void Room::set_start()
{
	string leveltxt = string("level") +  string(mlevelno) + string("start.txt");
	ifstream myfile (leveltxt);

	if( myfile == NULL)
	{
		std::cout<<"Couldn't find the file"<<endl;

	}
	else{

	string line;
	getline(myfile, line);
	
	// Done with the file
	myfile.close();
		GLfloat a = -1;
		GLfloat b = -1; 
		string temp;

		for(int i = 0; i < line.length(); i++)
		{
			if(line[i]== ' ' || line[i] == ',')
			{
				if(temp.length() > 0)
				{
					// Fill the next number
					if(a == -1)
					{
						a = atoi(temp.c_str());
					}
					else if (b == -1)
					{
						b = atoi(temp.c_str());
					}
					else
					{
						std::cout<<"Too many numbers for start"<<endl;
					}

					// Reset temp
					temp = "";
				}
			}
			else{
				temp += line[i];
			}

		}

		// Fill the next number
		if(a == -1)
		{
			a = atoi(temp.c_str());
		}
		else if (b == -1)
		{
			b = atoi(temp.c_str());
		}
		else
		{
			std::cout<<"Too many numbers for start"<<endl;
		}
		if(a == -1 || b == -1)
		{
			beginx = NULL;
			beginz = NULL;
		}
		else{

			// Make the right size conversion
			beginx = (a - 15) * 10;
			beginz = (b - 15) * 10;
		}
	}


}


void Room::set_player_position(GLfloat x, GLfloat z)
{
	mp->mpositionx = x;
	mp->mpositionz = z;
}


void Room::update_level()
{
	set_walls();
	set_start();
	if(beginx != NULL && beginz != NULL)
	{
		std::cout<<"set player positon\n";
		std::cout<<beginx<<beginz<<endl;
		set_player_position(-beginx, -beginz);
	}
	set_end();
}

pair <GLfloat, GLfloat> Room::detect_collision(pair<GLfloat, GLfloat>prev, pair<GLfloat, GLfloat>next)
{

	GLfloat x1;
	GLfloat z1;
	GLfloat x2;
	GLfloat z2;

	GLfloat prevx = prev.first;
	GLfloat prevz = prev.second;
	GLfloat nextx = next.first;
	GLfloat nextz = next.second;

	pair <pair<GLfloat, GLfloat>, pair<GLfloat, GLfloat>>  p;
	for (unsigned i=0; i<mcoordinates.size(); i++)
	{
		p = mcoordinates.at(i);
		x1 = p.first.first;
		z1 = p.first.second;
		x2 = p.second.first;
		z2 = p.second.second;

		// Horizontal wall
		if (z1 == z2)
		{
			// Sort on smallest
			if(x1 < x2)
			{
				// If nextx is positioned next to wall see if y value changes
				if( -nextx >= x1 && -nextx <= x2 )
				{

					z1 = z1 - 4;
					z2 = z2 + 4;

					
					if(-nextz >z1 && -nextz < z2 )
					{
						if(abs(abs(-nextz) - abs(z1)) <  abs(abs(-nextz) - abs(z2)))
						{
							next.second = prevz+0.2 ;
						}
						else{
							next.second = prevz-0.2 ;
						}
					}
					
				}
			}
			else{
				// If nextx is positioned next to wall see if y value changes
				if( -nextx >= x2 && -nextx <= x1 )
				{
			
					z1 = z1 -4;
					z2 = z2 + 4;
					if(-nextz >z1 && -nextz < z2 )
					{
						
						if(abs(abs(-nextz) - abs(z1)) <  abs(abs(-nextz) - abs(z2)))
							{
								next.second = prevz +0.2 ;
							}
							else{
								next.second = prevz - 0.2 ;
							}

					}
				}

			}
		}
		if (x1 == x2)
		{
			// Sort on smallest
			if(z1 < z2)
			{
				// If nextx is positioned next to wall see if y value changes
				if( -nextz >= z1 && -nextz <= z2 )
				{

					x1 = x1 - 4;
					x2 = x2 + 4;

					if(-nextx >x1 && -nextx < x2 )
					{
						if(abs(abs(-nextx) - abs(x1)) <  abs(abs(-nextx) - abs(x2)))
						{
							next.first = prevx +0.2;
						}
						else{
							next.first = prevx -0.2;
						}
					}
				}
			}
			else{

				// If nextx is positioned next to wall see if y value changes
				if( -nextz >= z2 && -nextz <= z1 )
				{
				
					x1 = x1 - 4;
					x2 = x2 + 4;
					
					if(-nextx >x1 && -nextx < x2 )
					{
						if(abs(abs(-nextx) - abs(x1)) <  abs(abs(-nextx) - abs(x2)))
						{
							next.second = prevx +0.2;
						}
						else{
							next.second = prevx -0.2;
						}
					}


				}

			}
		}
		// Vertical wall
		
	}
	return next;

}

GLfloat prevvx = 0;
GLfloat prevvz = 0;
bool Room::at_goal(pair<GLfloat, GLfloat> pos)
{
		GLfloat x1;
		GLfloat z1;
		GLfloat x2;
		GLfloat z2;

		GLfloat posx = -pos.first;
		GLfloat posz = -pos.second;

		// Determine distance to change sound intensity
		GLfloat distancex = 99999;
		GLfloat distancez = 99999;
	
		

		pair <pair<GLfloat, GLfloat>, pair<GLfloat, GLfloat>>  p;
		for (unsigned i=0; i<mendpositions.size(); i++)
		{
			p = mendpositions.at(i);
			x1 = p.first.first;
			z1 = p.first.second;
			x2 = p.second.first;
			z2 = p.second.second;
			
		
			// If fits in tile return true
			if(posx > x1 && posz > z1  && posx < x2 && posz < z2)
			{
			
				return true;
			}
			// Else calculate distance to that tile
			else{

				if(abs(x1 - posx) < distancex)
				{
					distancex = abs(x1 - posx);
				}
				if(abs(x2 - posx) < distancex);
				{
					distancex = abs(x2 - posx);
				}
				if(abs(z1 - posz) < distancez)
				{
					distancez = abs(z1 - posz);
				}
				if(abs(z2 - posz) < distancez)
				{
					distancez = abs(z2 - posz);
				}
			}

		}

		GLfloat final_distance = distancex + distancez;
		if(final_distance > 500)
		{
			mc2->setVolume(0);
			mc2->setPaused(false);

		}
		if(final_distance < 500)
		{
			mc2->setVolume(0.2);
			mc2->setPaused(false);
		}
		if(final_distance < 250)
		{
			mc2->setVolume(0.4);
			mc2->setPaused(false);
		}
		if(final_distance < 150)
		{
			mc2->setVolume(0.6);
			mc2->setPaused(false);
		}
		if(final_distance < 100)
		{
			mc2->setVolume(0.8);
			mc2->setPaused(false);
		}
		if(final_distance < 50)
		{
			mc2->setVolume(1.8);
			mc2->setPaused(false);
		}			
		// Determine the approximate position from the end
		return false;

}
