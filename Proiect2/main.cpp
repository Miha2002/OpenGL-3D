/*	Proiect 3D - Grafică pe calculator
	Iancu Florentina-Mihaela & Bora Dragoș-Ionuț , grupa 361*/

#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <gl/freeglut.h>
#include <math.h>

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;
// position of the camera
float vertPos = 1.0;
float horizPos = 0.0;

# define M_PI 3.14159265358979323846  
float strafing = M_PI / 2;

// Bird movement
int rotateBird = 0;

// Light position
GLfloat pozitial0[] = { 10.0, 50.0, 10.0, 0.0 };
// Colors
GLfloat alb[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat gri[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat negru[] = { 0.0, 0.0, 0.0, 1.0 };
//-----------
GLfloat ambient[] = { 0.55, 0.15, 0.6, 0.2 };
GLfloat specular[] = { 0.15, 0.05, 0.05, 0.2 };
GLfloat diffuse[] = { 0.35, 0.15, 0.6, 0.2 };

// FOG SETUP
GLfloat angleFog = 0.0;
GLfloat density = 0.049;
GLfloat fogColor[4] = { 0.5, 0.5, 0.7, 0.05 };

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void init(void) 
{
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glEnable(GL_FOG); //enable the fog
	glFogi(GL_FOG_MODE, GL_EXP2); //set the fog mode to GL_EXP2

	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, density); 
	glHint(GL_FOG_HINT, GL_NICEST); // set the fog to look the nicest, may slow down on older cards
}

void drawTree()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// LIGHTING
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);

	// Tree trunk
	GLfloat trunk[] = { 0.36, 0.25, 0.2 , 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, trunk);
	
	glPushMatrix();
	glTranslated(0.0f, 0.0f, 0.0f);
	glRotatef(-90, 1, 0, 0);
	glutSolidCylinder(0.1, 1.5, 20, 20);
	glPopMatrix();

	// Tree top
	GLfloat crown[] = { 0.0, 0.5, 0.05 , 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, crown);
	glPushMatrix();
	glTranslatef(0.0f, 1.4f, 0.0f);
	glScalef(1.0, 0.8, 1.0);
	glutSolidSphere(0.6f, 20, 20);
	glPopMatrix();
}

void drawBuildings()
{
	// FIRST HALF
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -15.0f);
	glScalef(2.0, 10.0, 1.0);
	glutSolidCube(1.0);

	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(1.0, 0.8, 1.0);
	glutSolidCube(1.0);

	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.2, 1.0);
	glutSolidCube(1.0);

	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.2, 1.0);
	glutSolidCube(1.0);

	glTranslatef(1.2f, 0.0f, 0.0f);
	glScalef(1.0, 0.6, 1.0);
	glutSolidCube(1.0);

	glTranslatef(1.0f, 0.0f, 0.0f);
	glutSolidCube(1.0);

	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(1.2, 1.5, 1.0);
	glutSolidCube(1.0);

	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(0.8, 0.8, 1.0);
	glutSolidCube(1.0);

	glTranslatef(1.2f, 0.0f, 0.0f);
	glScalef(1.0, 1.2, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	
	//NEXT HALF
	glPushMatrix();
	glTranslatef(-2.5f, 0.0f, -15.0f);
	glScalef(2.0, 10.0, 1.0);
	glutSolidCube(1.0);

	glTranslatef(-1.0f, 0.0f, 0.0f);
	glScalef(1.0, 0.8, 1.0);
	glutSolidCube(1.0);

	glTranslatef(-1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.5, 1.0);
	glutSolidCube(1.0);

	glTranslatef(-1.0f, 0.0f, 0.0f);
	glutSolidCube(1.0);

	glTranslatef(-1.2f, 0.0f, 0.0f);
	glScalef(1.0, 0.8, 1.0);
	glutSolidCube(1.0);

	glTranslatef(-1.0f, 0.0f, 0.0f);
	glScalef(1.0, 0.8, 1.0);
	glutSolidCube(1.0);

	glTranslatef(-1.0f, 0.0f, 0.0f);
	glutSolidCube(1.0);

	glTranslatef(-1.0f, 0.0f, 0.0f);
	glScalef(1.2, 1.5, 1.0);
	glutSolidCube(1.0);

	glTranslatef(-1.0f, 0.0f, 0.0f);
	glScalef(0.8, 0.8, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawBird()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// LIGHTING
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);

	// Draw Body
	GLfloat birdBody[] = { 0.95, 0.9, 0.2 , 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, birdBody);

	glPushMatrix();
	glTranslatef(0.0f, 1.2f, 0.0f);
	glScalef(1.5f, 1.0f, 1.0f);
	glutSolidSphere(0.2f, 20, 20);
	glPopMatrix();

	// Draw Tail
	glPushMatrix();
	glTranslatef(0.0f, 1.25f, 0.0f);
	glRotatef(-90, 0, 1, 0);

	glutSolidCone(0.15f, 0.5f, 20, 20);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);

	// Draw Wings
	GLfloat birdWing[] = { 0.90, 0.85, 0.1 , 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, birdWing);

	glPushMatrix();
	glTranslatef(0.0f, 1.22f, 0.0f);
	glScalef(0.27, 0.18, 0.5);
	glRotatef(35, 0, 0, 1);
	
	glutSolidTetrahedron();
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);

	// Draw Eyes
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, alb);
	glPushMatrix();
	glTranslatef(0.22f, 1.2f, -0.1f);
	glutSolidSphere(0.05f, 20, 20);

	glTranslatef(0.0f, 0.0f, 0.2f);
	glutSolidSphere(0.05f, 20, 20);
	glPopMatrix();

	// Draw Pupils
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);
	glPushMatrix();
	glTranslatef(0.24f, 1.2f, -0.12f);
	glutSolidSphere(0.035f, 20, 20);

	glTranslatef(0.0f, 0.0f, 0.24f);
	glutSolidSphere(0.035f, 20, 20);
	glPopMatrix();

	// Draw Beak
	GLfloat birdBeak[] = { 0.9, 0.7, 0.1 , 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, birdBeak);

	glPushMatrix();
	glTranslatef(0.2f, 1.16f, 0.0f);
	glScalef(2.5f, 1.0f, 1.0f);
	glRotatef(45, 0, 0, 1);
	glRotatef(45, 0, 1, 0);
	
	glutSolidCube(0.1f);
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);
}

void drawPipe(float height)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// LIGHTING
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);

	// Draw Body
	GLfloat pipeLight[] = { 0.10, 0.35, 0.05 , 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, pipeLight);

	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glRotated(-90, 1, 0, 0);
	glutSolidCylinder(0.35, 0.1, 20, 20);
	glutSolidCylinder(0.3, height, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, height, 0.0);
	glRotated(-90, 1, 0, 0);
	glutSolidCylinder(0.35, 0.1, 20, 20);
	glPopMatrix();
}

void renderScene(void)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// LIGHTING
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.6f, 1.0f, 1.0);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x + horizPos, vertPos, z,
		x + lx + horizPos, vertPos, z + lz,
		0.0f, 2.0f, 0.0f);

	// Draw ground
	GLfloat ground[] = { 0.2, 0.7, 0.2, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ground);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);

	//Draw buildings
	GLfloat building1[] = { 0.05, 0.05, 0.10, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, building1);

	glPushMatrix();
	glTranslatef(1.0, 1.0, -10.0);
	glScaled(1.2, 0.4, 1.0);
	drawBuildings();
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);

	GLfloat building2[] = { 0.10, 0.10, 0.20, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, building2);

	glPushMatrix();
	glTranslatef(1.8, 1.0, -15.0);
	glScaled(0.8, 1.05, 1.0);
	drawBuildings();
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);

	GLfloat building3[] = { 0.15, 0.15, 0.25, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, building3);

	glPushMatrix();
	glTranslatef(0.5, 1.0, -20.0);
	glScaled(1.5, 1.5, 1.0);
	drawBuildings();
	glPopMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);

	// Draw trees
	for (int i = 18; i >= 6; i = i - 2)
	{
		glPushMatrix();
		glTranslated(i, 0.0, -6.0);
		drawTree();
		glTranslated(0.0, 0.0, 2.0);
		drawTree();
		glTranslated(0.0, 0.0, 2.0);
		drawTree();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-i, 0.0, -6.0);
		drawTree();
		glTranslated(0.0, 0.0, 2.0);
		drawTree();
		glTranslated(0.0, 0.0, 2.0);
		drawTree();
		glPopMatrix();
	}

	// Draw bird	
	glPushMatrix();
	glTranslated(horizPos, vertPos, 0.0);
	glRotated(rotateBird, 0, 1, 0);
	drawBird();
	glPopMatrix();

	// Draw Pipes
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	drawPipe(0.8);
	glTranslated(2.0, 0.0, 0.0);
	drawPipe(3.3);
	glTranslated(2.0, 0.0, 0.0);
	drawPipe(2.3);
	glTranslated(2.0, 0.0, 0.0);
	drawPipe(1.8);
	glTranslated(2.0, 0.0, 0.0);
	drawPipe(2.3);
	glTranslated(2.0, 0.0, 0.0);
	drawPipe(2.8);
	glTranslated(2.0, 0.0, 0.0);
	drawPipe(3.8);
	glTranslated(2.0, 0.0, 0.0);
	drawPipe(1.8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.0, 0.0, 0.0);
	drawPipe(2.8);
	glTranslated(-2.0, 0.0, 0.0);
	drawPipe(1.8);
	glTranslated(-2.0, 0.0, 0.0);
	drawPipe(3.3);
	glTranslated(-2.0, 0.0, 0.0);
	drawPipe(1.3);
	glTranslated(-2.0, 0.0, 0.0);
	drawPipe(0.8);
	glTranslated(-2.0, 0.0, 0.0);
	drawPipe(2.3);
	glTranslated(-2.0, 0.0, 0.0);
	drawPipe(1.8);
	glPopMatrix();

	angleFog++;
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	float fraction = 0.1f;

	switch (key)
	{
	// camera angle and movement direction
	case 'q':
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;

	case 'e':
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;

	// basic movement of the camera
	case 'w':
		x += lx * fraction;
		z += lz * fraction;
		break;
	
	case 's':
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	
	case 'd':
		x += sin(strafing + angle) * fraction;
		z += -cos(strafing + angle) * fraction;
		break;

	case 'a':
		x -= sin(strafing + angle) * fraction;
		z -= -cos(strafing + angle) * fraction;
		break;
	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;
	
	// bird movement
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (horizPos >= -12) 
		{ 
			horizPos = horizPos - 0.1;
			rotateBird = 180;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (horizPos <= 12) 
		{ 
			horizPos = horizPos + 0.1;
			rotateBird = 0;
		}
		break;
	case GLUT_KEY_UP:
		if (vertPos < 5) { vertPos = vertPos + 0.1; }
		break;
	case GLUT_KEY_DOWN:
		if (vertPos > 1) { vertPos = vertPos - 0.1; }
		break;
	}
}

int main(int argc, char** argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Flappy Bird - NOW IN 3D - WIP");

	// register callbacks
	init();
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();
	return 1;
}