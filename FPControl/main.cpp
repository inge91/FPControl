
#include "StdAfx.h"
#include "main.h"


using namespace std;
GLuint LoadTextureRAW( const char * filename, int wrap, int w, int h );
GLuint raw_texture_load(const char *filename, int width, int height);
GLfloat boxsize = 2;
bool a = false;
bool d = false;
bool w = false;
bool s = false;
bool q = false;
bool e = false;
GLfloat weight = 1.5;

Player p = Player();
Room r = Room(&p);
Signs signs= Signs();
FMOD::System     *sys; //handle to FMOD engine
FMOD::Sound      *sound1; //sound that will be loaded and played
FMOD::Sound      *sound2; //sound that will be loaded and played
FMOD::Channel *c1;			// channel of choice for sound
FMOD::Channel *c2;			// channel of choice for sound


void key_down_func(unsigned char key, int x, int y) {
	GLfloat tempx;
	GLfloat tempz;
	pair <GLfloat, GLfloat> pprev;
	pair <GLfloat, GLfloat> pnext;
	pair <GLfloat, GLfloat> temp;
	switch (key) {
	// a-key
	case 97:
		a = true;
		p.mdegrees -= 2;
		break;
	// d-key
	case 100:
		d  = true;
		p.mdegrees += 2;
		break;
	// w-key
	case 119:
		w = true;
		p.calculate_direction();
		tempx = p.mpositionx - (p.mdirx) * weight;
		tempz = p.mpositionz + (p.mdirz) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;

		break;
	// s-key
	case 115:
		s = true;
		p.calculate_direction();
		tempx = p.mpositionx + (p.mdirx) * weight;
		tempz = p.mpositionz - (p.mdirz) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;
	
		
		break;
	// q-key
	case 113:
		//p.mpositionz = p.mpositionx - (p.mdirx);
		q = true;
		p.calculate_direction_horizontal();
		
		tempx = p.mpositionx + (p.mdirz) * weight;
		tempz = p.mpositionz - (p.mdirx) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;
	

		break;
	case 'e':
		e = true;
		//p.mpositionz = p.mpositionx - (p.mdirx);
		p.calculate_direction_horizontal();
		tempx = p.mpositionx - (p.mdirz) * weight;
		tempz = p.mpositionz + (p.mdirx) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;
		break;
	
	case 32:
		signs.add_sign(p.mpositionx, p.mpositionz);
		break;
	case 27: //Escape key
			exit(0);
	}
}

void key_up_func(unsigned char key, int x, int y) {
	GLfloat tempx;
	GLfloat tempz;
	pair <GLfloat, GLfloat> pprev;
	pair <GLfloat, GLfloat> pnext;
	pair <GLfloat, GLfloat> temp;

	switch (key) {
	// a-key
	case 97:
		a = false;
		p.mdegrees -= 2;
		break;
	// d-key
	case 100:
		d  = false;
		p.mdegrees += 2;
		break;
	// w-key
	case 119:
		w = false;
	p.calculate_direction();
		tempx = p.mpositionx - (p.mdirx) * weight;
		tempz = p.mpositionz + (p.mdirz) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;
		break;
	// s-key
	case 115:
		s = false;
	p.calculate_direction();
		tempx = p.mpositionx + (p.mdirx) * weight;
		tempz = p.mpositionz - (p.mdirz) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;
		break;
	// q-key
	case 113:
		q = false;
		p.calculate_direction_horizontal();
		tempx = p.mpositionx + (p.mdirz) * weight;
		tempz = p.mpositionz - (p.mdirx) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;
		break;
	case 'e':
		e = false;
		//p.mpositionz = p.mpositionx - (p.mdirx);
		p.calculate_direction_horizontal();
		tempx = p.mpositionx - (p.mdirz) * weight;
		tempz = p.mpositionz + (p.mdirx) * weight;

		p.mpositionx = tempx;
		p.mpositionz = tempz;
		break;
	case 27: //Escape key
			exit(0);
	}
}



//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture

}
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}
int prevd = 0;
GLuint t;
//GLuint alien;
GLfloat prevdegr = 0;
Alien l= Alien(p.mpositionx, p.mpositionz);


void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 60, 1, 0.1, 1000.0 );


	pair <GLfloat, GLfloat> pprev;
	pair <GLfloat, GLfloat> pnext;
	pprev.first = p.mprevx;
	pprev.second = p.mprevz;
	pnext.first = p.mpositionx; 
	pnext.second = p.mpositionz;
	pair <GLfloat, GLfloat> temp = r.detect_collision(pprev, pnext);
	p.mpositionx = temp.first;
	p.mpositionz = temp.second;
	pair <GLfloat, GLfloat> current (p.mpositionx, p.mpositionz);
	if(r.at_goal(current))
	{
		exit(0);
	}

	p.draw_player();


	r.draw_level();
	signs.draw_signs(p.mpositionx, p.mpositionz);

	sys->update();
	

	glutSwapBuffers();
}
// load a 256x256 RGB .RAW file as a texture
// Taken from http://www.nullterminator.net/gltexture.html
GLuint LoadTextureRAW( const char * filename, int wrap, int w, int h )
{
    GLuint texture;
    int width, height;
    BYTE * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer
    width = w;
    height = h;
    data = (BYTE*) malloc( width * height * 3 );

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

	
    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    free( data );

    return texture;
}

//Called every 25 milliseconds
void update(int value) {
	glutPostRedisplay();
	if(a)
	{
	p.mdegrees -= 2;
	}
	if(d)
	{
		p.mdegrees += 2;
	}
	if(w)
	{
	
		p.calculate_direction();
		if(q||e){
		

		GLfloat tempx = p.mpositionx - (p.mdirx/2) * weight;
		GLfloat tempz = p.mpositionz + (p.mdirz/2) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;


		}
		else{


		GLfloat tempx = p.mpositionx - (p.mdirx) * weight;
		GLfloat tempz = p.mpositionz + (p.mdirz) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;


		}
	}
	if(s){
	p.calculate_direction();
		if(q||e){
		
		GLfloat tempx = p.mpositionx + (p.mdirx/2) * weight;
		GLfloat tempz = p.mpositionz - (p.mdirz/2) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;


		}
		else{


		GLfloat tempx = p.mpositionx + (p.mdirx) * weight;
		GLfloat tempz = p.mpositionz - (p.mdirz) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;


		}
	}
	if(q)
	{
		p.calculate_direction_horizontal();
		if(w||s)
		{


		GLfloat tempx = p.mpositionx + (p.mdirz/2) * weight;
		GLfloat tempz = p.mpositionz - (p.mdirx/2) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;


		}
		else{


		GLfloat tempx = p.mpositionx + (p.mdirz) * weight;
		GLfloat tempz = p.mpositionz - (p.mdirx) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;




		}

	}
	if(e)
	{
		p.calculate_direction_horizontal();
		if(w||s)
		{
		GLfloat tempx = p.mpositionx - (p.mdirz/2) * weight;
		GLfloat tempz = p.mpositionz + (p.mdirx/2) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;
		}
		else{

		GLfloat tempx = p.mpositionx - (p.mdirz) * weight;
		GLfloat tempz = p.mpositionz + (p.mdirx) * weight;
		p.mpositionx = tempx;
		p.mpositionz = tempz;
		}
	}

	glutTimerFunc(25, update, 0);
}


 GLuint raw_texture_load(const char *filename, int width, int height)
 {
     GLuint texture;
     unsigned char *data;
     FILE *file;
 
     // open texture data
     file = fopen(filename, "rb");
     if (file == NULL) return 0;
 
     // allocate buffer
     data = (unsigned char*) malloc(width * height * 4);
 
     // read texture data
     fread(data, width * height * 4, 1, file);
     fclose(file);
 
     // allocate a texture name
     glGenTextures(1, &texture);
 
     // select our current texture
     glBindTexture(GL_TEXTURE_2D, texture);
 
     // select modulate to mix texture with color for shading
     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
 
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
 
     // when texture area is small, bilinear filter the closest mipmap
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
     // when texture area is large, bilinear filter the first mipmap
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
     // texture should tile
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 
     // build our texture mipmaps
     gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
 
     // free buffer
     free(data);
 
     return texture;
 }


GLuint GetTexture(std::string Filename)
{
	GLuint tex_ID;

	tex_ID = SOIL_load_OGL_texture(
				Filename.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_POWER_OF_TWO
				| SOIL_FLAG_MIPMAPS
				| SOIL_FLAG_MULTIPLY_ALPHA
				| SOIL_FLAG_COMPRESS_TO_DXT
				| SOIL_FLAG_DDS_LOAD_DIRECT
				| SOIL_FLAG_INVERT_Y
				);

		if( tex_ID > 0 )
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, tex_ID );
			
			return tex_ID;
		}
		else
			return 0;
}

void init_sound_engine()
{
	//init FMOD
	FMOD::System_Create(&sys);// create an instance of the game engine
	sys->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels


	//load sounds
	sys->createSound("night.mp3", FMOD_HARDWARE|FMOD_LOOP_NORMAL, 0, &sound1);

	sys->playSound(FMOD_CHANNEL_FREE, sound1, true, &c1);
	c1->setVolume(1);
	c1->setPaused(false);

	
	

	
    glEnable(GL_DEPTH_TEST); // check for depth
    
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);



glutGameModeGet(GLUT_GAME_MODE_POSSIBLE);
	if(GLUT_GAME_MODE_POSSIBLE && 0)
	{
		glutEnterGameMode(); 
	}
	else
	{
			RECT desktop;
		   // Get a handle to the desktop window
		   const HWND hDesktop = GetDesktopWindow();
		   // Get the size of screen to the variable desktop
		   GetWindowRect(hDesktop, &desktop);
		   float width = desktop.right;
		   float height = desktop.bottom-65;
			glutInitWindowSize(desktop.right, desktop.bottom-55);
		glutInitWindowPosition (0,0);
		glutCreateWindow("FPS");
	}

	init_sound_engine();

	//sys->playSound(FMOD_CHANNEL_FREE, sound1, false, 0);
	//glutFullScreen();
	initRendering();

	r.set_textures();
	l.set_texture();
	signs.set_textures();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(key_down_func);
	glutKeyboardUpFunc(key_up_func);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutIgnoreKeyRepeat(true);
	glutMainLoop();
	return 0;
}

