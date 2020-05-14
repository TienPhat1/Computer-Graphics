// Lab3.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <math.h>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

#define PI		3.1415926

int		screenWidth = 600;
int		screenHeight= 600;

bool	bWireFrame = true;

float	baseRadius = 0.6;
float	baseHeight = 0.2;
float	baseRotateStep = 5;

float	cylRadius = 0.3;
float	cylHeight = 1.0;
float   cylMaxScaleY = 2.0;
float	cylScaleStep = 0.05;

float	body1SizeX = 3;       
float	body1SizeY = 0.1;     
float	body1SizeZ = 1.2;     

float	body2Radius = 0.3;
float	body2Height = 1.0;

Mesh	base;
Mesh	cyl;
Mesh	body1;
Mesh	body2;

void drawAxis()
{
	glPushMatrix();

	glColor3f(0, 0, 1);
	glLineWidth(2);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(-4, 0, 0);//x
		glVertex3f(4, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);//y
		glVertex3f(0, 4, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, -4);//z
		glVertex3f(0, 0, 4);
	glEnd();

	glPopMatrix();
}
void myKeyboard(unsigned char key, int x, int y)
{
	
    switch(key)
    {
		case '1':
			base.rotateY += baseRotateStep;
			if(base.rotateY > 360)
				base.rotateY -=360;
			break;
		case '2':	
			base.rotateY -= baseRotateStep;
			if(base.rotateY < 0)
				base.rotateY +=360;
			break;
		case '3':
			cyl.scaleY += cylHeight;
			break;
		case '4':	
			cyl.scaleY -= cylHeight;
			break;

	}
    glutPostRedisplay();
}

void drawBase()
{
	glPushMatrix();

		glTranslated(0, base.slideY, 0);
		glRotatef(base.rotateY, 0, 1, 0);

		if(bWireFrame)
			base.DrawWireframe();
		else
			base.DrawColor();

	glPopMatrix();
}
void drawCyl()
{
	glPushMatrix();
	
		glTranslated(0, cyl.slideY + baseHeight, 0);
		glScalef(cyl.scaleX, cyl.scaleY, cyl.scaleZ);
		glRotatef(base.rotateY, 0, 1, 0);

		if(bWireFrame)
			cyl.DrawWireframe();
		else
			cyl.DrawColor();

	glPopMatrix();
}
void drawBody1()
{
	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);
		glTranslated(0, body1SizeY + cylHeight*cyl.scaleY + baseHeight, 0);
		
		if(bWireFrame)
			body1.DrawWireframe();
		else
			body1.DrawColor();

	glPopMatrix();
}
void drawBody2()
{
	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);
		glTranslated(body1SizeX - body2Radius/2, cylHeight*cyl.scaleY + baseHeight, 0);
		
		if(bWireFrame)
			body2.DrawWireframe();
		else
			body2.DrawColor();

	glPopMatrix();
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-8, 6, 8, 0, 1, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glViewport(0, 0, screenWidth, screenHeight);
	
	drawAxis();
	drawBase();
	drawCyl();
	drawBody1();
	drawBody2();
	glFlush();
    glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
		
	glutInit(&argc,argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab3-2019-2020"); // open the screen window

	base.CreateCylinder(20,baseHeight, baseRadius);
	//base.SetColor(2);
	// base.slideY = baseHeight/2.0;

	cyl.CreateCylinder(20,cylHeight, cylRadius);
	//cyl.SetColor(0);
	// cyl.slideY = cylHeight/2.0;

	body1.CreateCuboid(body1SizeX, body1SizeY, body1SizeZ);
	// body1.SetColor(4);
	body2.CreateCylinder(20,body2Height,body2Radius);
	myInit();

	glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(myDisplay);
	
	glutMainLoop();
	return 0;
}






