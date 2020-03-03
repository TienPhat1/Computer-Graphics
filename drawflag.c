#include<GL/glut.h>
#include<math.h>
#define PI acos(-1)

void drawStar(int len)
{
    
    float arrVertexTriangles[5][2];
    float arrVertexPentagon[5][2];
    arrVertexTriangles[0][0] = 0;
    arrVertexTriangles[0][1] = len;
    float x1,xh;
    float y1,yh;
    float angle = 90;
    //try by array
    for( int i = 1; i < 6; i++)
    {
        angle +=72;
        x1 = cos((angle/180)*PI)*len;
        y1 = sin((angle/180)*PI)*len;
        arrVertexPentagon[i-1][1] = (arrVertexTriangles[i-1][0]*x1+arrVertexTriangles[i-1][1]*y1)/(arrVertexTriangles[i-1][0]*(y1-arrVertexTriangles[i-1][1])/(arrVertexTriangles[i-1][0]-x1)+arrVertexTriangles[i-1][1]);
        arrVertexPentagon[i-1][0] = arrVertexPentagon[i-1][1]*(y1-arrVertexTriangles[i-1][1])/(arrVertexTriangles[i-1][0]-x1);
        arrVertexTriangles[i][0] = x1;
        arrVertexTriangles[i][1] = y1;
    }
    glBegin(GL_POLYGON);
        for (int i = 0; i < 5; i++)
        {
            glVertex2f(arrVertexPentagon[i][0],arrVertexPentagon[i][1]);
        }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < 5; i++)
        {
            if (i==0)
            {
                glVertex2f(arrVertexTriangles[i][0],arrVertexTriangles[i][1]);
                glVertex2f(arrVertexPentagon[i][0],arrVertexPentagon[i][1]);
                glVertex2f(arrVertexPentagon[4][0],arrVertexPentagon[4][1]);
            }
            else 
            {
                glVertex2f(arrVertexTriangles[i][0],arrVertexTriangles[i][1]);
                glVertex2f(arrVertexPentagon[i-1][0],arrVertexPentagon[i-1][1]);
                glVertex2f(arrVertexPentagon[i][0],arrVertexPentagon[i][1]);
            }
            
            
            
        }
        
    glEnd();
    glFlush();
        
}

void init(void)
{
    
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2,2,-1,1);
}

    void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawStar(2);   
}
int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
     glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("drawFlag");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    
    return 0;
}
