#include<GL/glut.h>

float Vertexs[3][2] = {{-1.0,-0.58},{1.0,-0.58},{0.0,1.15}};
int n;

void triangle(GLfloat *dataVertexA , GLfloat *dataVertexB, GLfloat *dataVertexC)
{
    glVertex2fv(dataVertexA);
    glVertex2fv(dataVertexB);
    glVertex2fv(dataVertexC);
}

void divide_triangle(GLfloat *dataVertexA, GLfloat *dataVertexB, GLfloat *dataVertexC, int eledepthRecur)
{
    float Vertex1[2],Vertex2[2],Vertex3[2];
    if(eledepthRecur == 0 ) triangle(dataVertexA,dataVertexB,dataVertexC);
    else
    {
        for (int i = 0; i < 2; i++)
        {
            Vertex1[i] = (dataVertexA[i]+dataVertexB[i])/2;
            Vertex2[i] = (dataVertexB[i]+dataVertexC[i])/2;
            Vertex3[i] = (dataVertexA[i]+dataVertexC[i])/2;
        }
        divide_triangle(dataVertexA,Vertex1,Vertex3,eledepthRecur - 1);
        divide_triangle(dataVertexB,Vertex1,Vertex2,eledepthRecur - 1);
        divide_triangle(dataVertexC,Vertex2,Vertex3,eledepthRecur - 1);
        
    }
    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        divide_triangle(Vertexs[0],Vertexs[1],Vertexs[2],n);
    glEnd();
    glFlush();
}

void init()
{
    glClearColor(1.0,1.0,1.0,1.0); //white background
    glColor3f(1.0,0.0,0.0); // draw in red
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0,2.0,-2.0,2.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    n = 4;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Sierpinski 2D");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
