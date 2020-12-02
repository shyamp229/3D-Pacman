/*
 Author: Shyam Patel
 Class: ECE4122
 Last Date Modified: 12/01/20
 Description:
 Draws a pacman maze with pacman, ghosts, coins, powerups, and maze
 Also game functionalitys like: ghosts move about the maze without going through walls,
 The ghost should travel towards pac-man and always be in motion, and pac-man moves about 
 the maze without going through walls and consumes object. Also, Up, down, left, right 
 arrow key change pac-man’s direction.
 */

#include "openGLheader.h"

#include <math.h>
#include <stdio.h>
#include "ECE_Ghost.h"
#include "ECE_Pacman.h"

// dimensions for maze
#define GDIMY 19
#define GDIMX 23


// Global Variables
// maze is blue print for drawing everything in the window
/*
 Walls ==> h, l, X, U
 Coins/PowerUps ==> c / P
 */
char maze[GDIMX][GDIMY] = {
	{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'X', 'l', 'l', 'l', 'l', 'l', 'l', 'l', 'l', 'l'},
	{'U', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'X', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'U'},
	{'U', 'P', 'X', 'l', 'c', 'X', 'l', 'l', 'c', 'X', 'c', 'X', 'l', 'l', 'c', 'h', 'X', 'P', 'U'},
	{'U', 'c', 'h', 'U', 'c', 'h', 'h', 'U', 'c', 'U', 'c', 'h', 'h', 'U', 'c', 'U', 'l', 'c', 'U'},
	{'U', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'U'},
	{'U', 'c', 'h', 'l', 'c', 'X', 'c', 'h', 'h', 'X', 'l', 'l', 'c', 'X', 'c', 'h', 'l', 'c', 'U'},
	{'U', 'c', 'c', 'c', 'c', 'X', 'c', 'c', 'c', 'X', 'c', 'c', 'c', 'X', 'c', 'c', 'c', 'c', 'U'},
	{'U', 'l', 'l', 'l', 'c', 'X', 'l', 'l', ' ', 'U', ' ', 'h', 'h', 'X', 'c', 'h', 'h', 'h', 'U'},
	{' ', ' ', ' ', 'U', 'c', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'c', 'U', ' ', ' ', ' '},
	{'h', 'h', 'h', 'U', 'c', 'U', ' ', 'X', 'l', ' ', 'l', 'l', ' ', 'U', 'c', 'U', 'l', 'l', 'l'},
	{' ', ' ', ' ', ' ', 'c', ' ', ' ', 'X', ' ', 'Q', ' ', 'U', ' ', ' ', 'c', ' ', ' ', ' ', ' '},
	{'h', 'h', 'h', 'X', 'c', 'X', ' ', 'X', 'L', 'I', 'E', 'U', ' ', 'X', 'c', 'X', 'l', 'l', 'l'},
	{' ', ' ', ' ', 'X', 'c', 'X', ' ', 'h', 'h', 'h', 'h', 'U', ' ', 'X', 'c', 'X', ' ', ' ', ' '},
	{' ', ' ', ' ', 'X', 'c', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', 'c', 'X', ' ', ' ', ' '},
	{'X', 'l', 'l', 'l', 'c', 'U', ' ', 'h', 'h', 'X', 'l', 'l', ' ', 'U', 'c', 'h', 'h', 'h', 'X'},
	{'X', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'X', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'X'},
	{'X', 'c', 'h', 'X', 'c', 'h', 'h', 'l', 'c', 'U', 'c', 'h', 'h', 'l', 'c', 'X', 'l', 'c', 'X'},
	{'X', 'P', 'c', 'X', 'c', 'c', 'c', 'c', 'c', 'M', 'c', 'c', 'c', 'c', 'c', 'X', 'c', 'P', 'X'},
	{'X', 'l', 'c', 'U', 'c', 'X', 'c', 'h', 'h', 'X', 'l', 'l', 'c', 'X', 'c', 'U', 'c', 'h', 'X'},
	{'X', 'c', 'c', 'c', 'c', 'X', 'c', 'c', 'c', 'X', 'c', 'c', 'c', 'X', 'c', 'c', 'c', 'c', 'X'},
	{'X', 'c', 'h', 'h', 'h', 'h', 'h', 'l', 'c', 'U', 'c', 'h', 'h', 'h', 'h', 'h', 'l', 'c', 'X'},
	{'X', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'X'},
	{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'U'},
};

ECEGhost redGhost;		// ECE Ghost object to draw ghosts
ECEGhost greenGhost;		// ECE Ghost object to draw ghosts
ECEGhost orangeGhost;		// ECE Ghost object to draw ghosts
ECEGhost pinkGhost;		// ECE Ghost object to draw ghosts

ECEPacman pacman;	// ECE Pacman to draw pacman
//float angle = 0.0f;	// rotating map
int x = 0, y = 0;	// idx for maze
float xPos = 0.0f, yPos = 0.0f; 	// pacman position
bool left = false, right = false, up = false, down = false;
int tmpX, tmpY;
// positions
int pacX = 17, pacY = 9;
int rX = 11, rY = 8;
int gX = 11, gY = 9;
int orX = 11, orY = 10;
int pinkX = 10, pinkY = 9;

bool startGame = false;
int coins = 154, pu = 4, pacLives = 3;
bool powerUpActive {false};
// init function to setup Camera, lighting, shading, background color


void init(void)
{
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	gluLookAt(15.0, -20.0, 15.0, 
			  0.0, 0.0, 0.0, 
			  0.0, 0.0, 1.0);
	glRotatef(-90.0f, 0, 0, 1);
}

// right wall: wall points toward right
void drawHWalls()
{
		// blue
	glColor4f(0.0f, 0.0f, 1.0f, 1);
	glPushMatrix();
		// right
	glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
	gluCylinder(gluNewQuadric(), 0.1, 0.1, 1.0, 32, 32);
	glPopMatrix();
}

// left wall: wall points toward left
void drawLWalls()
{
		// blue
	glColor4f(0.0f, 0.0f, 1.0f, 1);
	glPushMatrix();
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		gluCylinder(gluNewQuadric(), 0.1, 0.1, 1.0, 32, 32);
	glPopMatrix();
}

// down wall: wall points downward
void drawWalls()
{
	// blue
	glColor4f(0.0f, 0.0f, 1.0f, 1);
	glPushMatrix();
		glRotatef(90.0, 0.0f, 1.0f, 0.0f);
		gluCylinder(gluNewQuadric(), 0.1, 0.1, 1.0, 32, 32);
	glPopMatrix();
}
// up wall: wall points upward
void drawUWalls()
{
		// blue
	glColor4f(0.0f, 0.0f, 1.0f, 1);
	glPushMatrix();
		glRotatef(-90.0, 0.0f, 1.0f, 0.0f);
		gluCylinder(gluNewQuadric(), 0.1, 0.1, 1.0, 32, 32);
	glPopMatrix();
}

// Silver Coins drawing function
void drawCoin() 
{
	glPushMatrix();
		// silver color
		glColor4f(0.75, 0.75, 0.75, 1);
		glutSolidSphere(0.05, 20, 20);  
	glPopMatrix();
}

// Power ups drawing function
void drawPowerUps()
{
	glPushMatrix();
	// golden color
		glColor4f(0.90, 0.70, 0.01, 1);
		glRotatef(90, 0, 0, 1);
		gluDisk(gluNewQuadric(), 0, 0.1, 20, 20);
	glPopMatrix();
}

void drawGame()
{
	// draw maze,pacman,ghost,coin,powerups
	for (int i = -12; i <= 12; i++)
	{
		for (int j = -9; j <= 9; j++)
		{
			if (maze[x][y] == 'X')
			{
				glPushMatrix();
				glTranslatef(i, j, 0);
				drawWalls();
				glPopMatrix();
			}
			if (maze[x][y] == 'U')
			{
				glPushMatrix();
				glTranslatef(i, j, 0);
				drawUWalls();
				glPopMatrix();
			}
			if (maze[x][y] == 'h')
			{
				glPushMatrix();
				glTranslatef(i, j, 0);
				drawHWalls();
				glPopMatrix();
			}
			if (maze[x][y] == 'l')
			{
				glPushMatrix();
				glTranslatef(i, j, 0);
				drawLWalls();
				glPopMatrix();
			}
			if (maze[x][y] == 'c')
			{
				glPushMatrix();
				glTranslatef(i, j, 0);
				drawCoin();
				glPopMatrix();
			}
			if (maze[x][y] == 'P')
			{
				glPushMatrix();
				glTranslatef(i, j, 0);
				drawPowerUps();
				glPopMatrix();

			}
			if (maze[x][y] == 'M')
			{
//				printf("x = %d, y = %d\n", x, y);
				glPushMatrix();
				glTranslatef(i, j, 0);
				pacman.drawPacman();
				glPopMatrix();
			}
			// red ghost
			if (maze[x][y] == 'L')
			{
				glPushMatrix();
				glTranslatef(i, j, 0);
				if (powerUpActive) glColor4f(1, 1, 1, 1);
				else glColor4f(1, 0, 0, 1);
				redGhost.drawGhost();
				glPopMatrix();
			}
			// green ghost
			if (maze[x][y] == 'I')
			{

				glPushMatrix();
				glTranslatef(i, j, 0);
				if (powerUpActive) glColor4f(1, 1, 1, 1);
				else glColor4f(0, 1, 0, 1);
				greenGhost.drawGhost();
				glPopMatrix();
			}
			// orange ghost
			if (maze[x][y] == 'E')
			{

				glPushMatrix();
				glTranslatef(i, j, 0);
				if (powerUpActive) glColor4f(1, 1, 1, 1);
				else glColor4f(0.96, 0.56, 0.22, 1);
				orangeGhost.drawGhost();
				glPopMatrix();
			}
			// pink
			if (maze[x][y] == 'Q')
			{
				glPushMatrix();
				glTranslatef(i, j, 0);
				if (powerUpActive) glColor4f(1, 1, 1, 1);
				else glColor4f(0.96, 0.26, 0.91, 1);
				pinkGhost.drawGhost();
				glPopMatrix();
			}
			++y;
		}
		++x;
		y = 0;
	}
	x = 0;
	y = 0;
}

// display: draws the maze, pacman, ghosts, silver coins, powerups 
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
//	glRotatef(angle, 0.0f, 0.0f, 1.0f);			// rotates the map
	// starts pacman game when key pressed
	if (startGame)
	{
		glPushMatrix();
		drawGame();
		glPopMatrix();
	}
	
	
	// check if games over
	if ((pu == 0 && coins == 0) || pacLives < 0)
	{
		startGame = false;
	}

	
	glutSwapBuffers();
}

// reshape: resphaes the map according to the window size
void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

// keyboard: reads input from keyboard mainly reads if user pressed 'r' or 'R' and rotates it by 5 degress clockwise
void keyboard(unsigned char key, int x, int y)
{
	// reads any keyboard input to start the game
	if (key && !startGame)
	{
		startGame = true;
		//================Demo 1==========================//
		// after starting the game ghosts are set in motion
		if (pinkGhost.ghostAlive)
			pinkGhost.setGhostToPath();
		//================Demo 2==========================//
		if (redGhost.ghostAlive)
			redGhost.setGhostToPath();
		if (greenGhost.ghostAlive)
			greenGhost.setGhostToPath();
		if (orangeGhost.ghostAlive)
			orangeGhost.setGhostToPath();
	}
	glutPostRedisplay();
}

// Directions functions reads up, down, left, right arrow keys
void direction(int key, int, int)
{
	// check for collision
	//		don't move if wall else move
	// check for coins and power ups
	//		if coins or power ups replace with clear space
	// move 
	switch (key) {
		case GLUT_KEY_UP:
//			printf("up\n");
			up = true;
			left = right = down = false;
			xPos = -1.0f;
			yPos = 0.0f;
			break;
		case GLUT_KEY_RIGHT:
//			printf("right\n");
			right = true;
			left = up = down = false;
			yPos = 1.0f;
			xPos = 0.0f;
			break;
		case GLUT_KEY_LEFT:
//			printf("left\n");
			left = true;
			up = right = down = false;
			yPos = -1.0f;
			xPos = 0.0f;
			break;
		case GLUT_KEY_DOWN:
//			printf("down\n");
			down = true;
			left = right = up = false;
			xPos = 1.0f;
			yPos = 0.0f;
			break;
		default:
			startGame = true;
//			coins = 154;
//			pu = 4;
			break;
	}

	// new pacman position in maze
	tmpX = pacX + xPos;
	tmpY = pacY + yPos;
	if (tmpX == 10 && tmpY == 18 && right)
	{
		tmpY = 0;
	}
	if (tmpX == 10 && tmpY == 0 && left)
	{
		tmpY = 18;
	}
	
	// check where new position is and avoid walls
	switch(maze[tmpX][tmpY])
	{
		case 'P':
			maze[tmpX][tmpY] = 'M';
			maze[pacX][pacY] = ' ';
			pacX = tmpX;
			pacY = tmpY;
			--pu;
			powerUpActive = true;
			glutPostRedisplay();
			break;
		case 'c':
			maze[tmpX][tmpY] = 'M';
			maze[pacX][pacY] = ' ';
			pacX = tmpX;
			pacY = tmpY;
			--coins;
			glutPostRedisplay();
			break;
		case ' ':
			maze[tmpX][tmpY] = 'M';
			maze[pacX][pacY] = ' ';
			pacX = tmpX;
			pacY = tmpY;
			glutPostRedisplay();
			break;
		case 'L':
			if (powerUpActive)
			{
				maze[tmpX][tmpY] = 'M';
				maze[rX][rY] = 'L';
				redGhost.ghostPos.first = rX;
				redGhost.ghostPos.second = rY;
				redGhost.ghostAlive = false;
				maze[pacX][pacY] = ' ';
				pacX = tmpX;
				pacY = tmpY;
			} 
			else 
			{
				pacLives--;
				maze[pacX][pacY] = ' ';
				pacX = 17;
				pacY = 9;
				maze[pacX][pacY] = 'M';
				tmpX = pacX;
				tmpY = pacY;
			}
			glutPostRedisplay();
			break;
		case 'I':
			if (powerUpActive)
			{
				maze[tmpX][tmpY] = 'M';
				maze[gX][gY] = 'I';
				greenGhost.ghostPos.first = gX;
				greenGhost.ghostPos.second = gY;
				greenGhost.ghostAlive = false;
				maze[pacX][pacY] = ' ';
				pacX = tmpX;
				pacY = tmpY;
			}
			else
			{
				pacLives--;
				maze[pacX][pacY] = ' ';
				pacX = 17;
				pacY = 9;
				maze[pacX][pacY] = 'M';
				tmpX = pacX;
				tmpY = pacY;
			}
			glutPostRedisplay();
			break;
		case 'E':
			if (powerUpActive)
			{
				maze[tmpX][tmpY] = 'M';
				maze[orX][orY] = 'E';
				orangeGhost.ghostPos.first = orX;
				orangeGhost.ghostPos.second = orY;
				orangeGhost.ghostAlive = false;
				maze[pacX][pacY] = ' ';
				pacX = tmpX;
				pacY = tmpY;
			} 
			else
			{
				pacLives--;
				maze[pacX][pacY] = ' ';
				pacX = 17;
				pacY = 9;
				maze[pacX][pacY] = 'M';
				tmpX = pacX;
				tmpY = pacY;
			}
			glutPostRedisplay();
			break;
		case 'Q':
			if (powerUpActive)
			{
				maze[tmpX][tmpY] = 'M';
				maze[pinkX][pinkY] = 'Q';
				pinkGhost.ghostPos.first = pinkX;
				pinkGhost.ghostPos.second = pinkY;
				pinkGhost.ghostAlive = false;
				maze[pacX][pacY] = ' ';
				pacX = tmpX;
				pacY = tmpY;
			} else
			{
				pacLives--;
				maze[pacX][pacY] = ' ';
				pacX = 17;
				pacY = 9;
				maze[pacX][pacY] = 'M';
				tmpX = pacX;
				tmpY = pacY;
			}
			glutPostRedisplay();
			break;
		default:
			glutPostRedisplay();
			break;	
	}
	

}

// timer function updates pacman position in ghost class
void timer(int)
{
	if (startGame)
	{
		redGhost.pacPos = make_pair(pacX+1, pacY+3);
		greenGhost.pacPos = make_pair(pacX+2, pacY+2);
		orangeGhost.pacPos = make_pair(pacX, pacY+1);
		pinkGhost.pacPos = make_pair(pacX, pacY);
//		if (pinkGhost.ghostAlive == false)
//		{
//			this_thread::sleep_for(5s);
//			pinkGhost.ghostAlive = true;
//		}
	}
	glutPostRedisplay();
	glutTimerFunc(200, timer, 0); 		// recalls timer functions every 200ms;
	
}

// main: setsup the window for 3D Pacman
int main(int argc, char** argv)
{
	// init for ghosts
	redGhost.ghostPos = make_pair(rX, rY);
	greenGhost.ghostPos = make_pair(gX, gY);
	orangeGhost.ghostPos = make_pair(orX, orY);
	pinkGhost.ghostPos = make_pair(pinkX, pinkY);
	redGhost.colorofGhost = 'L';
	greenGhost.colorofGhost = 'I';
	orangeGhost.colorofGhost = 'E';
	pinkGhost.colorofGhost = 'Q';

		
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("3D Pacman");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(direction);
	
	glutMainLoop();
	return 0;
}
