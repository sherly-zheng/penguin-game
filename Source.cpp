#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <iostream>
GLfloat pos[] = { -2,4,5,1 }, amb[] = { 0.3, 0.3, 0.3, 1.0 }, spe[] = { 0.25, 0.25, 0.25, 1.0 };
GLfloat theta = 0, dt = 0.3, rotorTheta = 225, rotorDT = 3.0, heliTheta = 225, heliDT = 0.4;
GLfloat tubeColor[8][3] = { { 1,0,0 },{ 0,1,0 },{ 0,0,1 },{ 1,1,0 },{ 0,1,1 },{ 1,0,1 },{ 0.5,0.5,0.5 } };
GLfloat snowmanX[3] = { -0.75, 0.0, 0.75 };
GLfloat penPos = 0.0;
int axis = 0, sampleColor = 0, randSnowmanA = 0, randSnowmanB = 2, rotations = 0, score = 0, highScore = 0;
bool start = false, pause = false, end = false;
char tubeInstr[] = "Use the 'A' and 'D' keys to select a snow tube color. ";
char startInstr[] = "Press 'S' to start.";
char commands[] = "'A' - Left     'D' - Right     'P' - Pause/Unpause     'Q' - Quit";
char playInsrt[] = "Instructions: Use the 'A' and 'D' keys to avoid the snowmen.";
char gameOver[] = "Game Over! Press 'S' to restart.";

void houseDetails() {
	glColor3f(0.4, 0, 0);
	glutSolidCube(0.6);
	//Roof
	glPushMatrix();
	glTranslated(0.0, 0.281, 0.0);
	glRotated(270, 1, 0, 0);
	glColor3f(0.1, 0.1, 0.1);
	glutSolidCone(0.5, 0.13, 20, 20);
	glPopMatrix();

	//Chimney
	glPushMatrix();
	glTranslated(0.2, 0.27, 0.0);
	glScaled(1.0, 4.0, 1.0);
	glColor3f(0.4, 0.171, 0.0);
	glutSolidCube(0.1);
	glPopMatrix();

	//Chimney Puffs
	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glScaled(1.5, 1.0, 1.0);
	glTranslated(0.15, 0.5, 0.0);
	glutSolidSphere(0.025, 10, 10);
	glTranslated(0.0, 0.15, 0.0);
	glutSolidSphere(0.05, 10, 10);
	glTranslated(0.0, 0.2, 0.0);
	glutSolidSphere(0.075, 10, 10);
	glPopMatrix();

	//Door
	glPushMatrix();
	glColor3f(0.1, 0.0, 0.0);
	glTranslated(0.0, 0.0, 0.21);
	glScaled(1.0, 2.0, 1.0);
	glutSolidCube(0.2);
	glPopMatrix();

	//Doorknob
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.1);
	glTranslated(0.06, 0.0, 0.3);
	glutSolidSphere(0.02, 5, 5);
	glPopMatrix();
}

void penguin() {									//Penguin in a tube.
	glPushMatrix();
	if (!start) {												//Rotate the penguin around the y-axis as the player picks a tube color.
		glTranslated(0.0, 0.25, 2.0);
		glRotated(theta, 0, 1, 0);
	}
	else {														//If the player is done choosing a color, rotate the penguin so the player is facing the penguin's backside.
		glRotated(50, 1, 0, 0);
		glTranslated(penPos, 0.48, 1.25);
		glRotated(180, 0, 1, 0);
	}

	//Head
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslated(0.0, 0.35, 0.0);
	glutSolidSphere(0.15, 50, 50);
	glPopMatrix();

	//Left Eye
	glPushMatrix();
	glTranslated(-0.04, 0.35, 0.135);
	glutSolidSphere(0.02, 10, 10);
	glColor3f(1.0, 1.0, 1.0);
	glScaled(2.0, 3.0, 1.0);
	glutSolidSphere(0.015, 10, 10);
	glPopMatrix();

	//Right Eye
	glPushMatrix();
	glTranslated(0.04, 0.35, 0.135);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidSphere(0.02, 10, 10);
	glColor3f(1.0, 1.0, 1.0);
	glScaled(2.0, 3.0, 1.0);
	glutSolidSphere(0.015, 10, 10);
	glPopMatrix();

	//Beak
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslated(0.0, 0.3, 0.15);
	glutSolidCone(0.02, 0.05, 20, 10);
	glPopMatrix();

	//Wings
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslated(-0.17, 0.16, 0.0);
	glRotated(135, 0.0, 0.0, 1.0);
	glScaled(1.0, 4.0, 2.5);
	glutSolidSphere(0.02, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslated(0.17, 0.16, 0.0);
	glRotated(45, 0.0, 0.0, 1.0);
	glScaled(1.0, 4.0, 2.5);
	glutSolidSphere(0.02, 10, 10);
	glPopMatrix();

	//Body 
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslated(0.0, 0.13, .15);
	glScaled(4.0, 8.0, 1.0);
	glutSolidSphere(0.015, 20, 20);
	glPopMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glRotated(270.0, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 0.15, 0.15, 0.35, 40, 100);

	//Tube
	glColor3f(tubeColor[sampleColor][0], tubeColor[sampleColor][1], tubeColor[sampleColor][2]);
	glutSolidTorus(0.1, 0.23, 60, 90);
	glPopMatrix();
}

void helicopter() {
	//Helicopter Rotation
	glPushMatrix();
	glTranslated(0, -2.5, 2.0);
	if (start) glRotated(heliTheta, 0, 0, 1);
	else glRotated(225, 0, 0, 1);
	glTranslated(0, 5.0, -5.0);

	//Heli body
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glScaled(1.5, 1.0, 1.0);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	//Tail
	glPushMatrix();
	glTranslated(0.2, -0.0275, 0.0);
	glRotated(10, 0, 0, 1);
	glRotated(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.09, 0.015, 0.65, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.785, 0.16, 0.0);
	glutSolidTorus(0.0125, 0.075, 10, 10);
	glColor3f(0.0, 0.0, 0.0);
	glRotated(rotorTheta, 0, 0, 1);
	//Tail rotor 1
	glPushMatrix();
	glScaled(1.0, 9.0, 1.0);
	glutSolidCube(0.0125);
	glPopMatrix();

	//Tail rotor 2
	glPushMatrix();
	glScaled(9.0, 1.0, 1.0);
	glutSolidCube(0.0125);
	glPopMatrix();
	glPopMatrix();

	//Heli head
	glPushMatrix();
	glTranslated(-0.2, 0.0, 0.0);
	glScaled(1.5, 1.0, 1.0);
	glutSolidSphere(0.1, 30, 30);
	glPopMatrix();

	//Rotor
	glPushMatrix();
	glTranslated(0.0, 0.225, 0.0);
	//Rotor blade 1	
	glPushMatrix();
	glRotated(rotorTheta, 0, 1, 0);
	glRotated(45, 0, 1, 0);
	glScaled(50.0, 1.0, 2.4);
	glutSolidCube(0.0125);
	glPopMatrix();

	//Rotor blade 2
	glPushMatrix();
	glRotated(rotorTheta, 0, 1, 0);
	glRotated(135, 0, 1, 0);
	glScaled(50.0, 1.0, 2.4);
	glutSolidCube(0.0125);
	glPopMatrix();

	//Rotor base
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.015, 0.015, 0.05, 10, 10);
	glPopMatrix();

	//Legs
	glPushMatrix();
	glTranslated(-0.35, -0.225, 0.125);
	glRotated(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.01, 0.01, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.35, -0.225, -0.125);
	glRotated(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.01, 0.01, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.15, -0.225, 0.125);
	glRotated(340, 0, 0, 1);
	glRotated(225, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.01, 0.01, 0.15, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.15, -0.225, 0.125);
	glRotated(20, 0, 0, 1);
	glRotated(225, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.01, 0.01, 0.15, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.15, -0.225, -0.125);
	glRotated(340, 0, 0, 1);
	glRotated(315, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.01, 0.01, 0.15, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.15, -0.225, -0.125);
	glRotated(20, 0, 0, 1);
	glRotated(315, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.01, 0.01, 0.15, 10, 10);
	glPopMatrix();
	glPopMatrix();
}

void snowman() {
	glPushMatrix();
	//Head and body
	glColor3f(0.8, 0.8, 0.8);
	glutSolidSphere(0.2, 20, 20);
	glTranslated(0.0, 0.25, 0.0);
	glutSolidSphere(0.1, 20, 20);
	//Eyes
	glColor3f(0.0, 0.0, 0.0);
	glTranslated(-0.03, 0, 0.09);
	glutSolidSphere(0.015, 10, 10);
	glTranslated(0.06, 0, 0);
	glutSolidSphere(0.015, 10, 10);
	glPopMatrix();
	//Buttons
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.2);
	glutSolidSphere(0.0125, 10, 10);
	glTranslated(0.0, 0.05, 0.0);
	glutSolidSphere(0.0125, 10, 10);
	glTranslated(0.0, 0.05, 0.0);
	glutSolidSphere(0.0125, 10, 10);
	glPopMatrix();
	//Arms
	glPushMatrix();
	glTranslated(0.08, 0.075, 0);
	glRotated(45, 0, 0, 1);
	glScaled(20, 1, 1);
	glutSolidCube(0.02);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.08, 0.075, 0);
	glRotated(315, 0, 0, 1);
	glScaled(20, 1, 1);
	glutSolidCube(0.02);
	glPopMatrix();
}

void treeDetails() {
	gluCylinder(gluNewQuadric(), 0.1, 0.1, 0.5, 10, 10);
	glColor3f(0.137, 0.357, 0.137);
	glTranslated(0.0, 0.0, 0.2);
	glutSolidCone(0.3, 0.3, 20, 20);
	glTranslated(0.0, 0.0, 0.2);
	glutSolidCone(0.25, 0.3, 20, 20);
	glTranslated(0.0, 0.0, 0.2);
	glutSolidCone(0.2, 0.3, 20, 20);
}

void ground() {
	//Snowman #1
	glPushMatrix();
	glTranslated(snowmanX[randSnowmanA], -1.95, 0.0);
	if (start) {
		if (theta > 270.0 && theta <300.0) randSnowmanA = rand() % 3;
		glRotated(theta, 1, 0, 0);
	}
	glTranslated(0.0, 2.0, 0.0);
	snowman();
	glPopMatrix();

	//Snowman #2 (assuming there's no overlap)
	if (randSnowmanB != randSnowmanA) {
		glPushMatrix();
		glTranslated(snowmanX[randSnowmanB], -1.95, 0.0);
		if (start) {
			if (theta > 270.0 && theta < 300.0) randSnowmanB = rand() % 3;
			glRotated(theta, 1, 0, 0);
		}
		glTranslated(0.0, 2.0, 0.0);
		snowman();
		glPopMatrix();
	}

	//Houses
	glPushMatrix();
	glTranslated(0.0, -1.5, 0.0);
	if (start) glRotated(theta, 1, 0, 0);
	for (double i = 0; i < 360; i += 90) {
		glRotated(i, 1, 0, 0);
		//Left houses
		glPushMatrix();
		glRotated(25, 0, 0, 1);
		glTranslated(-1.0, 2.0, 0.0);
		houseDetails();
		glPopMatrix();

		//Right houses		
		glPushMatrix();
		glRotated(335, 0, 0, 1);
		glTranslated(1.0, 2.0, 0.0);
		houseDetails();
		glPopMatrix();

		//Left Trees
		glPushMatrix();
		glColor3f(0.35, 0.16, 0.14);
		glTranslated(-1.5, 0.75, 1.0);
		glRotated(25, 0, 0, 1);
		glRotated(320, 1, 0, 0);
		treeDetails();
		glPopMatrix();

		//Right Trees
		glPushMatrix();
		glColor3f(0.35, 0.16, 0.14);
		glTranslated(1.5, 0.75, 1.0);
		glRotated(335, 0, 0, 1);
		glRotated(320, 1, 0, 0);
		treeDetails();
		glPopMatrix();
	}

	//Ground
	glPushMatrix();
	glScaled(1.5, 0.75, 0.75);
	glColor3f(1.0, 0.98, 0.98);
	glutSolidSphere(2.0, 100, 120);
	glPopMatrix();
	glPopMatrix();

}

void play() {
	if (rotations > 3) {					//Speed up after every third rotation
		dt += 0.05;
		rotations = 0;
	}

	if ((theta > 35.0 && theta < 50.0) && (snowmanX[randSnowmanA] == penPos || snowmanX[randSnowmanB] == penPos)) {			//If the penguin collides with a snowman, game over.
		start = false;
		end = true;
		printf("Score: %i \n", score);
		if (score > highScore) highScore = score;
		printf("High Score: %i \n\n", highScore);
		randSnowmanA = 0;
		randSnowmanB = 2;
	}
}

void rotate(void) {
	if (!pause) {										//If game is paused, do not rotate anything.
		if (theta > 360.0) {
			theta -= 360.0;
			rotations++;
			score++;
		}

		if (theta <= 360.0) theta += dt;

		if (heliTheta > 360.0) heliTheta -= 360.0;
		if (heliTheta <= 360) heliTheta += heliDT;

		if (rotorTheta > 360.0) rotorTheta -= 360.0;
		if (rotorTheta <= 360) rotorTheta += rotorDT;
	}
	glutPostRedisplay();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);

	srand(time(NULL));
	if (start) {
		play();
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-1.7, 1.9, 0.0);
		for (int i = 0; i < 65; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, commands[i]);
		glRasterPos3f(-1.7, 1.7, 0.0);
		for (int i = 0; i < 60; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, playInsrt[i]);

	}
	if (!start && !end) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-1.4, 1.8, 0.0);
		for (int i = 0; i<53; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tubeInstr[i]);
		glRasterPos3f(-0.5, 1.5, 0.0);
		for (int i = 0; i<19; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, startInstr[i]);
	}
	if (end) {
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(-1.0, 1.8, 0.0);
		for (int i = 0; i<32; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gameOver[i]);
	}
	ground();
	helicopter();
	penguin();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		if (!start) {														// If it's the start of the game, choose a color. Otherwise, move penguin left.
			if (sampleColor != 0) sampleColor -= 1;
		}
		else if (start && !pause) {
			if (penPos > -0.75)  penPos -= 0.75;
		}
		break;

	case 'd':
		if (!start) {														// If it's the start of the game, choose a color. Otherwise, move penguin right.					
			if (sampleColor != 6) sampleColor += 1;
		}
		else if (start && !pause) {
			if (penPos < 0.75) penPos += 0.75;
		}
		break;

	case 's':																//Start game and reset values
		if (!start) {
			start = true;
			end = false;
			theta = 0;
			rotations = 0;
			score = 0;
			randSnowmanA = 0;
			randSnowmanB = 2;
			penPos = 0;
		}
		break;

	case 'p':
		if (start) {													//Pause or unpause game.
			if (pause) pause = false;
			else pause = true;
		}
		break;

	case 'q':															//Quit game.
		start = false;
		pause = false;
		break;

	}
	glutPostRedisplay();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("Penguin Game");
	glClearColor(0.2, 0.6, 0.8, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1.0, 2, 8);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -5);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(rotate);
	glutMainLoop();
}