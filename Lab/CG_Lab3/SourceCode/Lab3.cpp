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

bool	bWireFrame = false;
bool 	viewMode = true;
bool	slight = true;
bool	animation = false;
float	baseRadius = 0.6;
float	baseHeight = 0.2;
float	baseRotateStep = 5;

float	cylRadius = 0.3;
float	cylHeight = 2.0;
float   cylMaxScaleY = 2.0;
float	cylScaleStep = 0.05;

float	matbanSizeX = 3;       
float	matbanSizeY = 0.1;     
float	matbanSizeZ = 1.2;
float 	beta;   
float 	constant;  

float camera_angle = 5;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;


Mesh	base;
Mesh	cyl;
//Body
Mesh	matban;
Mesh	giacodinh;
Mesh	decontruot_1;
Mesh	decontruot_2;
Mesh	thanhnoi1;
Mesh	thanhnoi2;
Mesh	thanhnoi3;
Mesh	thanhnoi4;
Mesh	contruot1;
Mesh 	contruot2;
Mesh	chot0;
Mesh 	chot1;
Mesh	chot2;
Mesh	chot3;
Mesh	chot4;

float CenterX(float x1,float y1, float x2, float y2,float radius)
    {
        float radsq = radius * radius;
        float q = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
        float x3 = (x1 + x2) / 2;


     return x3 + sqrt(radsq - ((q / 2) * (q / 2))) * ((y1 - y2) / q);


    }

float CenterY(float x1, float y1, float x2, float y2, float radius)
    {
    double radsq = radius * radius;
    double q = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

     double y3 = (y1 + y2) / 2;

      return y3 + sqrt(radsq - ((q / 2) * (q / 2))) * ((x2-x1) / q);


    }

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

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.5;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.5;
		if (camera_height < 0)
			camera_height = 0;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 5;
		break;
	case GLUT_KEY_LEFT:
		camera_angle -= 5;
		break;
	default:
		break;
	
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	
    switch(key)
    {
		case '1':
			base.rotateY += baseRotateStep;
			if(base.rotateY > 360)
				base.rotateY -=360;
			//thanhnoi1.rotateY = base.rotateY;
			break;
		case '2':	
			base.rotateY -= baseRotateStep;
			if(base.rotateY < 0)
				base.rotateY +=360;
			//thanhnoi1.rotateY = base.rotateY;
			break;
		case '3':
			thanhnoi1.rotateY += baseRotateStep;
			if(thanhnoi1.rotateY > 360)
				thanhnoi1.rotateY -=360;
			break;
		case '4':
			thanhnoi1.rotateY -= baseRotateStep;
			if(thanhnoi1.rotateY < 0)
				thanhnoi1.rotateY +=360;
			break;
		case '5':
			if(contruot2.slideX <-1.7)
				contruot2.slideX += 0.1;
			break;
		case '6':
			if(contruot2.slideX >-2.5)
				contruot2.slideX -= 0.1;
			break;
		case 'W':
		case 'w':	
			bWireFrame = !bWireFrame;
			break;
		case 'V':
		case 'v':
			viewMode = !viewMode;
			break;
		case 'D':
		case 'd':
			slight = !slight;
			break;
		case '+':
		camera_dis += 0.2;
		break;
		case '-':
		camera_dis -= 0.2;
		break;
		case 'A':
		case 'a':
			animation = !animation;
			break;


	}
    glutPostRedisplay();
}

void drawLucGiac(float x, float y, float z, float radius){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
	glBegin(GL_QUADS);
	glColor3f(143.0/255.0,0,109.0/255.0);
	glNormal3f(0,1,0);
	glVertex3f(x + radius*cos(0),y, z + radius*sin(0));
	glVertex3f(x + radius*cos(PI/3),y,z + radius*sin(PI/3));
	glVertex3f(x + radius*cos(2*PI/3),y,z + radius*sin(2*PI/3));
	glVertex3f(x,y,z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(197.0/255.0,124.0/255.0,172.0/255.0);
	glNormal3f(0,1,0);
	glVertex3f(x + radius*cos(2*PI/3),y, z + radius*sin(2*PI/3));
	glVertex3f(x + radius*cos(PI),y,z + radius*sin(PI));
	glVertex3f(x + radius*cos(4*PI/3),y,z + radius*sin(4*PI/3));
	glVertex3f(x,y,z);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(232.0/255.0,211.0/255.0,237.0/255.0);
	glNormal3f(0,1,0);
	glVertex3f(x + radius*cos(4*PI/3),y, z + radius*sin(4*PI/3));
	glVertex3f(x + radius*cos(5*PI/3),y,z + radius*sin(5*PI/3));
	glVertex3f(x + radius*cos(6*PI/3),y,z + radius*sin(6*PI/3));
	glVertex3f(x,y,z);
	glEnd();

}

void drawNen()
{
	float y = 0;
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	float d = 0.7, R = d / cos(M_PI / 6);
	int i = 0;
	for (float x = -30; x < 30; x += R + R * cos(M_PI / 3))
	{
		float z = (i % 2 == 0) ? -20 : (-20 - d);
		for (; z < 20; z += 2 * d)
			drawLucGiac(x, y, z, R);
		i++;
	}
	glEnable(GL_LIGHTING);
}
void drawBase()
{
	glPushMatrix();

		glTranslated(0, 0, 0);
		glRotatef(base.rotateY, 0, 1, 0);

		float diffuse[] = {223.0/255.0, 0.0, 41.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		base.setupMeterial(ambient, diffuse, specular, shininess);

		if(bWireFrame)
			base.DrawWireframe();
		else
			base.Draw();

	glPopMatrix();
}
void drawCyl()
{
	glPushMatrix();
	
		glTranslated(0, base.slideY, 0);
		glScalef(cyl.scaleX, cyl.scaleY, cyl.scaleZ);
		glRotatef(base.rotateY, 0, 1, 0);

		float diffuse[] = {32.0/225.0, 90.0/225.0, 167.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		cyl.setupMeterial(ambient, diffuse, specular, shininess);

		if(bWireFrame)
			cyl.DrawWireframe();
		else
			cyl.Draw();

	glPopMatrix();
}
void drawMatban()
{
	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);
		glTranslated(0,cyl.slideY, 0);

		float diffuse[] = {91.0/225.0, 189.0/225.0, 43.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		matban.setupMeterial(ambient, diffuse, specular, shininess);
		
		if(bWireFrame)
			matban.DrawWireframe();
		else
			matban.Draw();

	glPopMatrix();
}
void drawGiacodinh(){
	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);
		glTranslated(0, matban.slideY, matban.slideZ-0.2);

		float diffuse[] = {151.0/225.0, 109.0/225.0, 0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		giacodinh.setupMeterial(ambient, diffuse, specular, shininess);
	
		if(bWireFrame)
			giacodinh.DrawWireframe();
		else
			giacodinh.Draw();
	glPopMatrix();
}
void drawDeConTruot1(){
	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);
		glTranslated(decontruot_1.slideX,matban.slideY,decontruot_1.slideZ);

		float diffuse[] = {151.0/225.0, 109.0/225.0, 0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		decontruot_1.setupMeterial(ambient, diffuse, specular, shininess);

		if(bWireFrame)
			decontruot_1.DrawWireframe();
		else
			decontruot_1.Draw();
	glPopMatrix();
}
void drawDeConTruot2(){
	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);
		glTranslated(decontruot_2.slideX,matban.slideY,decontruot_2.slideZ);

		float diffuse[] = {151.0/225.0, 109.0/225.0, 0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		decontruot_2.setupMeterial(ambient, diffuse, specular, shininess);

		if(bWireFrame)
			decontruot_2.DrawWireframe();
		else
			decontruot_2.Draw();
	glPopMatrix();
}
void drawThanhnoi1(){

	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);

		glTranslated(giacodinh.slideX, giacodinh.slideY, thanhnoi1.slideZ);
			
		glRotatef(thanhnoi1.rotateY, 0, 1, 0);

		float diffuse[] = {245.0/225.0, 177.0/225.0, 109.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		thanhnoi1.setupMeterial(ambient, diffuse, specular, shininess);
		
		
		if(bWireFrame)
			thanhnoi1.DrawWireframe();
		else
			thanhnoi1.Draw();

	glPopMatrix();
}

void drawThanhnoi2(){

	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);

		float x_thanhnoi1 = 0.5*cos((thanhnoi1.rotateY*PI)/180);
		float z_thanhnoi1 = thanhnoi1.slideZ - thanhnoi1.slideZ*sin((thanhnoi1.rotateY*PI)/180)/2;
		
		float x_thanhnoi3 = contruot2.slideX;
		float z_thanhnoi3 = decontruot_2.slideZ;

		float x_tam = CenterX(x_thanhnoi1,z_thanhnoi1,x_thanhnoi3,z_thanhnoi3,thanhnoi2.slideX);
		float z_tam = CenterY(x_thanhnoi1,z_thanhnoi1,x_thanhnoi3,z_thanhnoi3,thanhnoi2.slideX);
		float temp = ((x_tam-x_thanhnoi1)*thanhnoi2.slideX)/(sqrt((x_tam-x_thanhnoi1)*(x_tam - x_thanhnoi1)+(z_tam- z_thanhnoi1)*(z_tam - z_thanhnoi1))*thanhnoi2.slideX);
		float degree_rotate = (180/PI)*acos(temp);

		//glTranslated(0.5*cos((thanhnoi1.rotateY*PI)/180), thanhnoi1.slideY,thanhnoi1.slideZ - thanhnoi1.slideZ*sin((thanhnoi1.rotateY*PI)/180)/2);
		glTranslatef(x_thanhnoi1,thanhnoi1.slideY,z_thanhnoi1);
		glRotatef(degree_rotate,0,1,0);

		float diffuse[] = {229.0/225.0, 70.0/225.0, 70.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		thanhnoi2.setupMeterial(ambient, diffuse, specular, shininess);
		
		
		if(bWireFrame)
			thanhnoi2.DrawWireframe();
		else
			thanhnoi2.Draw();

	glPopMatrix();
}
void drawThanhnoi3(){
	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);

		float x_thanhnoi1 = 0.5*cos((thanhnoi1.rotateY*PI)/180);
		float z_thanhnoi1 = thanhnoi1.slideZ - thanhnoi1.slideZ*sin((thanhnoi1.rotateY*PI)/180)/2;
		
		float x_thanhnoi3 = contruot2.slideX;
		float z_thanhnoi3 = decontruot_2.slideZ;

		float x_tam = CenterX(x_thanhnoi1,z_thanhnoi1,x_thanhnoi3,z_thanhnoi3,thanhnoi2.slideX);
		float z_tam = CenterY(x_thanhnoi1,z_thanhnoi1,x_thanhnoi3,z_thanhnoi3,thanhnoi2.slideX);

		float temp = ((x_tam-x_thanhnoi3)*thanhnoi2.slideX)/(sqrt((x_tam-x_thanhnoi3)*(x_tam - x_thanhnoi3)+(z_tam- z_thanhnoi3)*(z_tam - z_thanhnoi3))*thanhnoi2.slideX);
		float degree_rotate = (180/PI)*acos(temp);
		if(z_tam <= z_thanhnoi3)	degree_rotate*=-1;
		glTranslatef(contruot2.slideX,thanhnoi3.slideY,decontruot_2.slideZ);
		glRotatef(-degree_rotate,0,1,0);

		float diffuse[] = {32.0/225.0, 90.0/225.0, 167.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		thanhnoi3.setupMeterial(ambient, diffuse, specular, shininess);

		if(bWireFrame)
			thanhnoi3.DrawWireframe();
		else
			thanhnoi3.Draw();
	glPopMatrix();

}

void drawThanhnoi4(){
	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);
		float x_thanhnoi1 = 0.5*cos((thanhnoi1.rotateY*PI)/180);
		float z_thanhnoi1 = thanhnoi1.slideZ - thanhnoi1.slideZ*sin((thanhnoi1.rotateY*PI)/180)/2;
		
		float x_thanhnoi3 = contruot2.slideX;
		float z_thanhnoi3 = decontruot_2.slideZ;

		float x_tam = CenterX(x_thanhnoi1,z_thanhnoi1,x_thanhnoi3,z_thanhnoi3,thanhnoi2.slideX);
		float z_tam = CenterY(x_thanhnoi1,z_thanhnoi1,x_thanhnoi3,z_thanhnoi3,thanhnoi2.slideX);
		
		float temp = (z_tam -decontruot_2.slideZ)/thanhnoi2.slideX;
		float degree_rotate = (180/PI)*asin(temp);
		if(x_tam<0)
			thanhnoi4.slideX = thanhnoi2.slideX*cos((PI/180)*degree_rotate) - abs(x_tam);
		else
			thanhnoi4.slideX = thanhnoi2.slideX*cos((PI/180)*degree_rotate) + abs(x_tam);
		
		glTranslatef(x_tam,contruot1.slideY,z_tam);
		glRotatef(degree_rotate,0,1,0);

		float diffuse[] = {32.0/225.0, 90.0/225.0, 167.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		thanhnoi4.setupMeterial(ambient, diffuse, specular, shininess);


		if(bWireFrame)
			thanhnoi4.DrawWireframe();
		else
			thanhnoi4.Draw();
	glPopMatrix();

}
void drawContruot1(){
	
	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);
		glTranslated(thanhnoi4.slideX, decontruot_1.slideY,decontruot_1.slideZ);

		float diffuse[] = {245.0/225.0, 177.0/225.0, 109.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 80.0;
		contruot1.setupMeterial(ambient, diffuse, specular, shininess);


		if(bWireFrame)
			contruot1.DrawWireframe();
		else
			contruot1.Draw();
	glPopMatrix();
}

void drawContruot2(){
	
	glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);	
		glTranslated(contruot2.slideX, decontruot_2.slideY,decontruot_2.slideZ);

		float diffuse[] = {245.0/225.0, 177.0/225.0, 109.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 80.0;
		contruot2.setupMeterial(ambient, diffuse, specular, shininess);

		if(bWireFrame)
			contruot2.DrawWireframe();
		else
			contruot2.Draw();
	glPopMatrix();
}
 void drawChot1(){
	 glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);
		float x_thanhnoi1 = 0.5*cos((thanhnoi1.rotateY*PI)/180);
		float z_thanhnoi1 = thanhnoi1.slideZ - thanhnoi1.slideZ*sin((thanhnoi1.rotateY*PI)/180)/2;

		glTranslated(x_thanhnoi1, giacodinh.slideY, z_thanhnoi1);
			
		glRotatef(thanhnoi1.rotateY, 0, 1, 0);

		float diffuse[] = {112.0/225.0, 112.0/225.0, 112.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		chot1.setupMeterial(ambient, diffuse, specular, shininess);
		
		
		if(bWireFrame)
			chot1.DrawWireframe();
		else
			chot1.Draw();

	glPopMatrix();

 }

 void drawChot2(){
	 glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);
		float x_thanhnoi1 = 0.5*cos((thanhnoi1.rotateY*PI)/180);
		float z_thanhnoi1 = thanhnoi1.slideZ - thanhnoi1.slideZ*sin((thanhnoi1.rotateY*PI)/180)/2;
		
		float x_thanhnoi3 = contruot2.slideX;
		float z_thanhnoi3 = decontruot_2.slideZ;

		float x_tam = CenterX(x_thanhnoi1,z_thanhnoi1,x_thanhnoi3,z_thanhnoi3,thanhnoi2.slideX);
		float z_tam = CenterY(x_thanhnoi1,z_thanhnoi1,x_thanhnoi3,z_thanhnoi3,thanhnoi2.slideX);

		glTranslated(x_tam, contruot2.slideY, z_tam);
			
		//glRotatef(thanhnoi1.rotateY, 0, 1, 0);

		float diffuse[] = {112.0/225.0, 112.0/225.0, 112.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		chot2.setupMeterial(ambient, diffuse, specular, shininess);
		
		
		if(bWireFrame)
			chot2.DrawWireframe();
		else
			chot2.Draw();

	glPopMatrix();

 }

void drawChot3(){
	 glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);

		glTranslated(contruot2.slideX, contruot2.slideY, decontruot_2.slideZ);
			
		//glRotatef(thanhnoi1.rotateY, 0, 1, 0);

		float diffuse[] = {112.0/225.0, 112.0/225.0, 112.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		chot3.setupMeterial(ambient, diffuse, specular, shininess);
		
		
		if(bWireFrame)
			chot3.DrawWireframe();
		else
			chot3.Draw();

	glPopMatrix();

 }

void drawChot4(){
	 glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);

		glTranslated(thanhnoi4.slideX, contruot1.slideY,decontruot_1.slideZ);
			
		//glRotatef(thanhnoi1.rotateY, 0, 1, 0);

		float diffuse[] = {112.0/225.0, 112.0/225.0, 112.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		chot4.setupMeterial(ambient, diffuse, specular, shininess);
		
		
		if(bWireFrame)
			chot4.DrawWireframe();
		else
			chot4.Draw();

	glPopMatrix();

 }
 void drawChot0(){
	 glPushMatrix();
		glRotatef(base.rotateY, 0, 1, 0);

		glTranslated(giacodinh.slideX, giacodinh.slideY, thanhnoi1.slideZ);
			
		//glRotatef(thanhnoi1.rotateY, 0, 1, 0);

		float diffuse[] = {112.0/225.0, 112.0/225.0, 112.0/225.0, 1.0};
		float ambient[] = {0.0, 0.0, 0.0, 1.0};
		float specular[] = {1.0, 1.0, 1.0, 1.0};
		float shininess = 20.0;
		chot0.setupMeterial(ambient, diffuse, specular, shininess);
		
		
		if(bWireFrame)
			chot0.DrawWireframe();
		else
			chot0.Draw();

	glPopMatrix();

 }

void buildModel(){
	base.CreateCylinder(20,baseHeight, baseRadius);
	base.SetColor(1);
	base.CalculateFacesNorm();
	base.slideY = baseHeight;

	cyl.CreateCylinder(20,cylHeight, cylRadius);
	cyl.SetColor(2);
	cyl.CalculateFacesNorm();
	cyl.slideY = base.slideY + cylHeight;

	matban.CreateCuboid(matbanSizeX, matbanSizeY, matbanSizeZ);
	matban.SetColor(3);
	matban.CalculateFacesNorm();
	matban.slideY = cyl.slideY + matbanSizeY;
	matban.slideX = matbanSizeX;
	matban.slideZ = matbanSizeZ;

	giacodinh.CreateCuboid(0.2,0.4,0.2);
	giacodinh.SetColor(4);
	giacodinh.CalculateFacesNorm();
	giacodinh.slideZ = 0.2;
	giacodinh.slideY = matban.slideY + 0.4;

	decontruot_1.CreateHinhHopCoRanh(2.5,0.5,0.55,0.275,0.1); //ben phai
	decontruot_1.SetColor(5);
	decontruot_1.CalculateFacesNorm();
	decontruot_1.slideY = matban.slideY + 0.55-0.275;
	decontruot_1.slideX = matban.slideX - 2.5/2;
	decontruot_1.slideZ = -matban.slideZ + 0.5/2;

	decontruot_2.CreateHinhHopCoRanh(2.5,0.5,0.25,0.125,0.1); //ben trai
	decontruot_2.SetColor(6);
	decontruot_2.CalculateFacesNorm();
	decontruot_2.slideY = matban.slideY + 0.25 - 0.125;
	decontruot_2.slideX = -matban.slideX + 2.5/2;
	decontruot_2.slideZ = -matban.slideZ + 0.5/2;

	thanhnoi1.CreateThanhNoi(15,0.5,0.2,0.1,0.13);
	thanhnoi1.SetColor(7);
	thanhnoi1.CalculateFacesNorm();
	thanhnoi1.slideX = 0.5;
	thanhnoi1.slideY = giacodinh.slideY + 0.2;
	thanhnoi1.slideZ =  matban.slideZ - giacodinh.slideZ;

	thanhnoi2.CreateThanhNoi(15,2,0.2,0.1,0.13);
	thanhnoi2.SetColor(3);
	thanhnoi2.CalculateFacesNorm();
	thanhnoi2.slideZ = thanhnoi1.slideZ + 0.5;
	thanhnoi2.slideX = 2;
	
	contruot1.CreateHinhHopCoGo(1,0.5,0.55,0.275,0.1);//ben phai
	contruot1.SetColor(4);
	contruot1.CalculateFacesNorm();
	contruot1.slideX = 3;
	contruot1.slideY = decontruot_1.slideY + 0.55;

	contruot2.CreateHinhHopCoGo(1,0.5,0.25,0.125,0.1);//ben trai
	contruot2.SetColor(3);
	contruot2.CalculateFacesNorm();
	contruot2.slideX = -3 + 0.5;
	contruot2.slideY = decontruot_2.slideY + 0.25;

	thanhnoi3.CreateThanhNoi(15,2,0.2,0.1,0.13);
	thanhnoi3.SetColor(3);
	thanhnoi3.CalculateFacesNorm();
	thanhnoi3.slideX = contruot2.slideX;
	thanhnoi3.slideY = contruot2.slideY;

	thanhnoi4.CreateThanhNoi(15,2,0.2,0.1,0.13);
	thanhnoi4.SetColor(3);
	thanhnoi4.CalculateFacesNorm();
	thanhnoi4.slideX = 2;

	chot0.CreateCylinder(15,0.2,0.1);
	chot0.SetColor(3);
	chot0.CalculateFacesNorm();
	
	chot1.CreateCylinder(15,0.4,0.1);
	chot1.SetColor(3);
	chot1.CalculateFacesNorm();

	chot2.CreateCylinder(15,0.65,0.1);
	chot2.SetColor(3);
	chot2.CalculateFacesNorm();

	chot3.CreateCylinder(15,0.2,0.1);
	chot3.SetColor(3);
	chot3.CalculateFacesNorm();

	chot4.CreateCylinder(15,0.2,0.1);
	chot4.SetColor(3);
	chot4.CalculateFacesNorm();
}
void drawAll(){
	drawBase();
	drawCyl();
	drawMatban(); 	
	drawGiacodinh();
	drawDeConTruot1();	//ben phai
	drawDeConTruot2();	//ben trai
	drawThanhnoi1();
	drawThanhnoi2();
	drawThanhnoi3();
	drawThanhnoi4();
	drawContruot1();
	drawContruot2();
	drawChot1();
	drawChot2();
	drawChot3();
	drawChot4();
	drawChot0();
}
void myDisplay()
{
	float	fHalfSize = 4;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat light_position0[] = { -5.0, 10.0, 5.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	if (slight == true)
	{
		glEnable(GL_LIGHT1);
		GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat position1[] = { -5.0, 10.0, 5.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	}
	else
		glDisable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	camera_X = camera_dis * cos(camera_angle * PI / 180);
	camera_Y = camera_height;
	camera_Z = camera_dis * sin(camera_angle * PI / 180);
	// if(viewMode)
	// 	gluLookAt(-4, 4, 4, 0, 1, 0, 0, 1, 0); // nhin ngang
	// else
	

	if (camera_dis == 0)
	{
		const float ar = (float)screenWidth / (float)screenHeight;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glEnable(GL_NORMALIZE);
		glShadeModel(GL_SMOOTH);
		glDepthFunc(GL_LEQUAL);
		//glEnable(GL_COLOR_MATERIAL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		gluLookAt(camera_X, camera_Y, camera_Z, 0, 1, 0, sin(camera_angle * PI / 180), 0, cos(camera_angle * PI / 180));
	}
	else if(!viewMode)
	{
		glMatrixMode(GL_PROJECTION);
	 	glLoadIdentity();
		glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_NORMALIZE);
		glShadeModel(GL_SMOOTH);
		glDepthFunc(GL_LEQUAL);
		//glEnable(GL_COLOR_MATERIAL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		gluLookAt(0, camera_Y, 0, 0, 1, 0, 0, 0, -1); // OY nhin xuong
		
	}
	else
	{
		const float ar = (float)screenWidth / (float)screenHeight;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glEnable(GL_NORMALIZE);
		glShadeModel(GL_SMOOTH);
		glDepthFunc(GL_LEQUAL);
		//glEnable(GL_COLOR_MATERIAL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		gluLookAt(camera_X, camera_Y, camera_Z, 0, 1, 0, 0, 1, 0);
	}

	glClearStencil(0);
	// Clear depth
	glClearDepth(1.0f);
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glViewport(0, 0, screenWidth, screenHeight);
	//glClearStencil(0);
	// Clear depth
	//glClearDepth(1.0f);
	
	//drawAxis();
	drawAll();
	drawNen();
	glFlush();
    glutSwapBuffers();
}

void processTimer(int value)
{
	if (animation)
	{
		//if(contruot2.slideX <-1.7 && contruot2.scaleX )
			contruot2.slideX += (cos(thanhnoi1.rotateY*PI/180) - cos((thanhnoi1.rotateY + baseRotateStep)*PI/180))/2 ;
		thanhnoi1.rotateY += baseRotateStep;
		if (thanhnoi1.rotateY > 360)
			thanhnoi1.rotateY -= 360;
		
		
	}
	glutTimerFunc(10, processTimer, 0);
	glutPostRedisplay();
}

void myInit()
{
	float	fHalfSize = 4;
	camera_angle = 135;  // Góc quay camera xung quanh trục Oy
	camera_height = 5; // Chiều cao camera so với mặt phẳng xOz
	camera_dis = 6;	// Khoảng cách đến trục Oy

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(10, processTimer, 0);
	//glEnable(GL_CULL_FACE);

	
	


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);

	
}
int main(int argc, char *argv[])
{
		
	glutInit(&argc,argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab3-2019-2020"); // open the screen window
	
	buildModel();
	myInit();

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
    glutDisplayFunc(myDisplay);
	
	glutMainLoop();
	return 0;
}






