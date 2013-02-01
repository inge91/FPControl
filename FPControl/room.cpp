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
	mlevelno ="10";
	update_level();
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
		//std::cout<<"x1,y1 x2,y2"<<endl;
		//std::cout<<x1 << ","<<y1<<" "<<x2 <<"," <<y2<<endl;


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
			
			//std::cout<< x2<<","<<x1<< endl;
			//std::cout<< size<<endl;
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
	
	/*
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mroof);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(minx , maxy , minz );
	glTexCoord2f(2, 0);
	glVertex3f(maxx , maxy , minz );
	glTexCoord2f(2, 2);
	glVertex3f(maxx , maxy , maxz );
	glTexCoord2f(0, 2);
	glVertex3f(minx , maxy , maxz );
	glEnd();
	glDisable(GL_TEXTURE_2D);
	*/

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

void Room::update_level()
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
	
	if(prevx!= nextx || prevz!= nextz )
	{
	//	std::cout<<"\n"<<endl;
	//	std::cout<<"-nextx"<<endl;
	//	std::cout<<-nextx<<endl;
	//	std::cout<<"-nextz"<<endl;
	//	std::cout<<-nextz<<endl;
	}

	pair <pair<GLfloat, GLfloat>, pair<GLfloat, GLfloat>>  p;
	for (unsigned i=0; i<mcoordinates.size(); i++)
	{
		p = mcoordinates.at(i);
		x1 = p.first.first;
		z1 = p.first.second;
		x2 = p.second.first;
		z2 = p.second.second;

	if(prevx!= nextx || prevz!= nextz)
	{
		//std::cout<<"walls"<<endl;
	//	std::cout<<x1<< ","<<z1<< " " <<x2<<","<<z2<<endl;
	}
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

					if(prevx!= nextx || prevz!= nextz && 0)
					{
						//std::cout<<"new x1 x2"<<endl;
						//std::cout<<x1<< ","<<x2<<endl;
					}
					
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
