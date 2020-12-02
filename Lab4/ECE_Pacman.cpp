/*
 Author: Shyam Patel
 Class: ECE4122
 Last Date Modified: 12/01/20
 Description:
 Implements functionality of ECEPacman class.
 */


#include "ECE_Pacman.h"
#include "openGLheader.h"

// draws pacman using solid sphere
void ECEPacman::drawPacman() 
{
	glColor4f(1, 1, 0, 1);
	glPushMatrix();
		//glTranslatef(0.0, 0.0, 1.75); // position head
		glutSolidSphere(0.25, 20, 20); // head sphere
								   // Draw Eyes (two small black spheres)
		glColor4f(0.0, 0.0, 0.0, 1); // eyes are white
		glPushMatrix();
			glTranslatef(0.0, -0.18, 0.10); // lift eyes to final position
			glPushMatrix();
				glTranslatef(-0.05, 0.0, 0.0);
				glutSolidSphere(0.05, 10, 10); // right eye
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.05, 0.0, 0.0);
				glutSolidSphere(0.05, 10, 10); // left eye
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

}
