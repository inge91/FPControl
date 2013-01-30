#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>
#include "imageloader.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include  "alien.h"
#include "player.h"
#include "lodepng.h" 
#include <SOIL.h>
#include "room.h"
GLuint LoadTextureRAW( const char * filename, int wrap, int w, int h );
GLuint raw_texture_load(const char *filename, int width, int height);
GLuint GetTexture(std::string Filename);