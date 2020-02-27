#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#define PI acos(-1.0)
float x,y;
float len = 3;
void drawLine(float x1,float y1, float len, float angle, float &x2, float &y2)
{
    float radiant;
    radiant = (angle/180)*PI;
    x2 = cos(radiant)*len + x1;
    y2 = sin(radiant)*len + y1;
    glBegin(GL_LINES);
        glVertex2f(x2,y2);
        glVertex2f(x1,y1);
    glEnd();
    glFlush();
}
void drawTriangle(float x,float y, float len, float angle)
{
    float x1,y1;
    x1 = x;
    y1 = y;
    for (int i = 0; i < 3; i++)
    {
        drawLine(x1,y1,len,angle,x1,y1);
        angle = angle + 120;
    }
    
}
void drawMultiTriangle(void)
{
    float angle = 30;
    for (int i = 0; i < 12; i++)
    {
        drawTriangle(0,0,3,angle);
        angle = angle +30;
    }
    
}
void drawWindow(float a, float b, float len, float angle) //tao lao
{
    float x1,y1;
    float x,y;
    x = a + cos(((angle*4/180)+5)*PI/4)*sqrt(2)*len/2;
    y = b + sin(((angle*4/180)+5)*PI/4)*sqrt(2)*len/2;
    for( int i = 0 ; i < 4 ; i++)
    {
        drawLine(x,y,len,angle,x,y);
        drawLine(a,b,len/2,angle,x1,y1);
        angle += 90;

    }
        
}
void drawMultiWindow(float len)
{
    float angle = 0;
    for (int i = 0; i < 3; i++)
    {
        drawWindow(0,0,len,angle);
        angle += 30;
    }    
}
void drawPetal(float len,float angle)
{
    float x = 0,y = 0;
    for(int i = 0 ; i < 10 ; i++)
    {
        drawLine(x,y,len,angle,x,y);
        angle += (180-144);
    }
}
void drawFlower()
{
    float angle = 0;
    for (int i = 0; i < 12; i++)
    {
        drawPetal(len,angle);
        angle += 30;
    }
    
}
void demo_menu(int id)
{
    switch (id)
    {
    case 1: exit(1);
        break;
    case 2: len *= 2;
        break;
    case 3: len /= 2;
    }
    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2);
    drawFlower();   
}

void init(void)
{
    
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,10,-10,10,-1,1);
}
int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
     glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("drawLine");
    int sub_menu = glutCreateMenu(demo_menu);
    glutAddMenuEntry("increase size",2);
    glutAddMenuEntry("decrease size",3);
    glutCreateMenu(demo_menu);
    glutAddSubMenu("Resize",sub_menu);
    glutAddMenuEntry("exit",1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    printf("%f,%f",x,y);
    
    return 0;
}
