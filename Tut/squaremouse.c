#include<GL/glut.h>
#include<stdlib.h>
GLsizei wh = 500, ww = 500;
GLfloat size = 3.0;

void drawSquare(int x, int y)
{
    y = wh - y;
    glBegin(GL_POLYGON);
        glVertex2f(x+size,y+size);
        glVertex2f(x-size,y+size);
        glVertex2f(x-size,y-size);
        glVertex2f(x+size,y-size);
    glEnd();
    glFlush();
}

void init()
{
    glViewport(0,0,ww,wh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble) ww, 0.0, (GLdouble) wh);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0,0.0,0.0,1.0);
    glColor3f(1.0,0.0,0.0);
}
void myMouse(int btn, int state, int x, int y)
{
    if(btn == GLUT_LEFT_BUTTON && btn == GLUT_DOWN)
        drawSquare(x,y);
    if(btn == GLUT_RIGHT_BUTTON && btn == GLUT_DOWN)
        exit(1);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    glutInitWindowSize(ww,wh);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("square");
    init();
    glutMouseFunc(myMouse);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
