#include <math.h>
#include<GL/gl.h>
#include<GL/glut.h>

#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};
//supportClass.h
class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	void set(Point3& p)
						{ x = p.x; y = p.y; z = p.z;}
	Point3() { x = y = z = 0;}
	Point3(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
						{ r = red; g = green; b = blue;}
	void set(Color3& c)
						{ r = c.r; g = c.g; b = c.b;}
	Color3() { r = g = b = 0;}
	Color3(float red, float green, float blue)
						{ r = red; g = green; b = blue;}

};
class Point2
{
	public:
		Point2() { x = y = 0.0f; } // constructor 1
		Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
		void set(float xx, float yy) { x = xx; y = yy; }
		float getX() { return x;}
		float getY() { return y;}
		void draw()		{	glBegin(GL_POINTS);
								glVertex2f((GLfloat)x, (GLfloat)y);
							glEnd();
						}
	private:
		float 	x, y;
};
class IntRect
{
	 public:
		IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
		IntRect( int left, int right, int bottom, int top)
			{ l = left; r = right; b = bottom; t = top; }
		void set( int left, int right, int bottom, int top)
			{ l = left; r = right; b = bottom; t = top; }
		void draw(){
						glRecti(l, b, r, t);
						glFlush();
					} // draw this rectangle using OpenGL
		int  getWidth(){return (r-l);}
		int  getHeight() { return (t-b);}
	 private:
		int	l, r, b, t;
};


class RealRect
{
	 public:
		RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
		RealRect( float left, float right, float bottom, float top)
			{ l = left; r = right; b = bottom; t = top; }
		void set( float left, float right, float bottom, float top)
			{ l = left; r = right; b = bottom; t = top; }
		float  getWidth(){return (r-l);}
		float  getHeight() { return (t-b);}
		void draw(){
							glRectf(l, b, r, t);
							glFlush();
						};// draw this rectangle using OpenGL
	 private:
		float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	void set(Vector3& v)
						{ x = v.x; y = v.y; z = v.z;}
	void flip()
						{ x = -x; y = -y; z = -z;}
	void normalize();
	Vector3() { x = y = z = 0;}
	Vector3(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	Vector3(Vector3& v)
						{ x = v.x; y = v.y; z = v.z;}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

//Mesh.h

class VertexID
{
public:
	int		vertIndex;	//chi so cua cac vertex nay trong list vertex
	int		colorIndex;	//chi so cua cac mau trong list mau
};

class Face
{
public:
	int		nVerts;		//number of vertex in this face
	VertexID*	vert;	//the list of vertex and color index
	Vector3		facenorm;
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;		//number of vertex in the mesh
	Point3*		pt;			//list of 3D vertex
	
	int		numFaces;		//number of face in the mesh
	Face*		face;		//list of face 

	//Lab3
	float		slideX , slideY , slideZ;
	float		rotateX, rotateY, rotateZ;
	float		scaleX, scaleY, scaleZ;
public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
		slideX = 0;
		slideY = 0;
		slideZ = 0;
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		scaleX = 1;
		scaleY = 1;
		scaleZ = 1;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor(int);
	void Draw();
	void CalculateFacesNorm();

	//Lab2
	void CreateTetrahedron();
	void CreateCuboid(float	fLenght, float fHeight, float fWidth);
	void CreateCylinder(int nSegment, float fTopHeight, float fRadius);
	//void CreateHollowCylinder(int nSegment, float fHeight, float interRadius, float exterRadius);
	void CreateHinhHopCoRanh(float lenght, float width , float height , float depth, float thickness);
	//void CreateHinhHopGiaoTru(int nSegment, float lenght, float height, float radius);
	void CreateHinhHopCoGo(float lenght, float width , float height , float depth, float thickness );
	void CreateThanhNoi(int nSegment, float lenght, float height, float interRadius, float exterRadius);
	//lab3
	void SetColor(int colorIdx);
	void setupMeterial(float t1[], float t2[], float t3[] , float t4);
};

//supportClass.cpp

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x*b.x + y*b.y + z*b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x*x + y*y + z*z);
	x = x/temp;
	y = y/temp;
	z = z/temp;
}

//Mesh.cpp

void Mesh::CreateCuboid(float fWidth, float fHeight , float fLength)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fWidth, fHeight, fLength);
	pt[1].set( fWidth, fHeight, fLength);
	pt[2].set( fWidth, fHeight, -fLength);
	pt[3].set(-fWidth, fHeight, -fLength);
	pt[4].set(-fWidth, 0 , fLength);
	pt[5].set( fWidth, 0, fLength);
	pt[6].set( fWidth, 0, -fLength);
	pt[7].set(-fWidth, 0, -fLength);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}


void Mesh::CreateCylinder(int nSegment, float fTopHeight, float fRadius){
	numVerts=nSegment*2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	int 	idxcolor;
	float	fAngle = 2*PI/nSegment;
	float	x, y, z;

	pt[0].set(0, fTopHeight, 0);
	for(i = 0; i<nSegment; i++){
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fTopHeight;
		pt[i+1].set(x, y, z);

		y = 0;
		pt[i +1 + nSegment].set(x, y, z);
	}
	pt[numVerts-1].set(0, 0, 0);

	numFaces= nSegment*3;
	face = new Face[numFaces];

	idx = 0;
	idxcolor = 0;
	for(i = 0; i<nSegment; i++){
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		for(int j = 0; j < face[idx].nVerts ; j++)
			face[idx].vert[j].colorIndex = idxcolor;
		
		idxcolor++;
		idx++;
	}

	for(i = 0; i<nSegment; i++){
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		
		face[idx].vert[0].vertIndex = i+1;
		if(i <nSegment - 1)
			face[idx].vert[1].vertIndex = i+2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		for(int j = 0; j < face[idx].nVerts ; j++)
			face[idx].vert[j].colorIndex = idxcolor;
		
		idxcolor++;
		idx++;
	}

	for(i = 0; i<nSegment; i++){
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegment -1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		
		for(int j = 0; j < face[idx].nVerts ; j++)
			face[idx].vert[j].colorIndex = idxcolor;
		
		idxcolor++;
		idx++;
	}

}



void Mesh::CreateHinhHopCoRanh(float lenght, float width , float height , float depth, float thickness)
{
	int idxColor = 0;
	numVerts = 16;
	pt = new Point3[numVerts];
	//bottom
	pt[0].set(lenght/2, 0, width/2);
	pt[1].set(-lenght/2, 0, width/2);
	pt[2].set(-lenght/2, 0, -width/2);
	pt[3].set(lenght/2, 0, -width/2);
	//midle
	pt[4].set(lenght/2,height - depth ,width/2);
	pt[5].set(-lenght/2,height - depth ,width/2);
	pt[6].set(-lenght/2,height - depth,-width/2);
	pt[7].set(lenght/2,height - depth,-width/2);
	//topnear
	pt[8].set(lenght/2,height ,width/2);
	pt[9].set(-lenght/2,height ,width/2);
	pt[10].set(-lenght/2,height ,width/2 - thickness);
	pt[11].set(lenght/2,height,width/2 - thickness );
	//topfar
	pt[12].set(lenght/2,height ,-width/2);
	pt[13].set(-lenght/2,height ,-width/2);
	pt[14].set(-lenght/2,height ,-width/2 + thickness);
	pt[15].set(lenght/2,height,-width/2 + thickness );

	numFaces = 14;
	face = new Face[numFaces];
	// bottom and middle face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	for(int i = 0 ; i < 4 ; i ++)
	{		
		face[0].vert[i].vertIndex = i;
		face[1].vert[i].vertIndex = i + 4;
	}
	for(int j = 0 ; j < face[0].nVerts; j++)
		face[0].vert[j].colorIndex = 0;
	for(int j = 0 ; j < face[1].nVerts; j++)
		face[1].vert[j].colorIndex = 1;

	//front and rear face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[3].vertIndex = 4;

	for(int j = 0 ; j < face[2].nVerts; j++)
		face[2].vert[j].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 2;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 5;

	for(int j = 0 ; j < face[3].nVerts; j++)
		face[3].vert[j].colorIndex = 3;

	//near and far face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 0;
	face[4].vert[1].vertIndex = 8;
	face[4].vert[2].vertIndex = 9;
	face[4].vert[3].vertIndex = 1;

	for(int j = 0 ; j < face[4].nVerts; j++)
		face[4].vert[j].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 12;
	face[5].vert[2].vertIndex = 13;
	face[5].vert[3].vertIndex = 2;

	for(int j = 0 ; j < face[5].nVerts; j++)
		face[5].vert[j].colorIndex = 5;

	//near and far top faces

	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 8;
	face[6].vert[1].vertIndex = 9;
	face[6].vert[2].vertIndex = 10;
	face[6].vert[3].vertIndex = 11;

	for(int j = 0 ; j < face[6].nVerts; j++)
		face[6].vert[j].colorIndex = 6;

	face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 12;
	face[7].vert[1].vertIndex = 13;
	face[7].vert[2].vertIndex = 14;
	face[7].vert[3].vertIndex = 15;

	for(int j = 0 ; j < face[7].nVerts; j++)
		face[7].vert[j].colorIndex = 7;

	//two behind faces

	face[8].nVerts = 4;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 4;
	face[8].vert[1].vertIndex = 5;
	face[8].vert[2].vertIndex = 10;
	face[8].vert[3].vertIndex = 11;

	for(int j = 0 ; j < face[8].nVerts; j++)
		face[8].vert[j].colorIndex = 8;

	face[9].nVerts = 4;
	face[9].vert = new VertexID[face[8].nVerts];
	face[9].vert[0].vertIndex = 6;
	face[9].vert[1].vertIndex = 7;
	face[9].vert[2].vertIndex = 12;
	face[9].vert[3].vertIndex = 13;

	for(int j = 0 ; j < face[9].nVerts; j++)
		face[9].vert[j].colorIndex = 9;

	//four front and rear faces

	face[10].nVerts = 3;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 4;
	face[10].vert[1].vertIndex = 8;
	face[10].vert[2].vertIndex = 11;

	for(int j = 0 ; j < face[10].nVerts; j++)
		face[10].vert[j].colorIndex = 10;

	face[11].nVerts = 3;
	face[11].vert = new VertexID[face[11].nVerts];
	face[11].vert[0].vertIndex = 7;
	face[11].vert[1].vertIndex = 12;
	face[11].vert[2].vertIndex = 15;

	for(int j = 0 ; j < face[11].nVerts; j++)
		face[11].vert[j].colorIndex = 11;
	
	face[12].nVerts = 3;
	face[12].vert = new VertexID[face[12].nVerts];
	face[12].vert[0].vertIndex = 5;
	face[12].vert[1].vertIndex = 9;
	face[12].vert[2].vertIndex = 10;
	
	for(int j = 0 ; j < face[12].nVerts; j++)
		face[12].vert[j].colorIndex = 12;

	face[13].nVerts = 3;
	face[13].vert = new VertexID[face[13].nVerts];
	face[13].vert[0].vertIndex = 6;
	face[13].vert[1].vertIndex = 13;
	face[13].vert[2].vertIndex = 14;

	for(int j = 0 ; j < face[13].nVerts; j++)
		face[13].vert[j].colorIndex = 13;
}
void Mesh::CreateHinhHopCoGo(float lenght, float width , float height , float depth, float thickness ){
	numVerts = 16;
	pt = new Point3[numVerts];

	pt[0].set(lenght/2,height,width/2);
	pt[1].set(-lenght/2,height,width/2);
	pt[2].set(-lenght/2,height,-width/2);
	pt[3].set(lenght/2,height,-width/2);

	pt[4].set(lenght/2,depth,width/2);
	pt[5].set(-lenght/2,depth,width/2);
	pt[6].set(-lenght/2,depth,-width/2);
	pt[7].set(lenght/2,depth,-width/2);

	pt[8].set(lenght/2,height - depth,width/2 - thickness);
	pt[9].set(-lenght/2,height - depth,width/2 - thickness);
	pt[10].set(-lenght/2,height - depth,-width/2 + thickness);
	pt[11].set(lenght/2,height - depth,-width/2 + thickness);

	pt[12].set(lenght/2,0,width/2);
	pt[13].set(-lenght/2,0,width/2);
	pt[14].set(-lenght/2,0,-width/2);
	pt[15].set(lenght/2,0,-width/2);

	//Draw cac mat

	numFaces = 12;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	for(int i = 0 ; i < 4 ; i ++)
	{		
		face[0].vert[i].vertIndex = i;
		face[1].vert[i].vertIndex = i + 4;
	}
	for(int j = 0 ; j < face[0].nVerts; j++)
		face[0].vert[j].colorIndex = 0;

	for(int j = 0 ; j < face[1].nVerts; j++)
		face[1].vert[j].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[3].vertIndex = 4;

	for(int j = 0 ; j < face[2].nVerts; j++)
		face[2].vert[j].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 2;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 5;

	for(int j = 0 ; j < face[3].nVerts; j++)
		face[3].vert[j].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 0;
	face[4].vert[1].vertIndex = 4;
	face[4].vert[2].vertIndex = 5;
	face[4].vert[3].vertIndex = 1;

	for(int j = 0 ; j < face[4].nVerts; j++)
		face[4].vert[j].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 7;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 2;

	for(int j = 0 ; j < face[5].nVerts; j++)
		face[5].vert[j].colorIndex = 5;

	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];

	face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];

	for(int i = 0 ; i < 4 ; i ++)
	{		
		face[6].vert[i].vertIndex = i + 8;
		face[7].vert[i].vertIndex = i + 12;
	}

	for(int j = 0 ; j < face[6].nVerts; j++)
		face[6].vert[j].colorIndex = 6;

	for(int j = 0 ; j < face[7].nVerts; j++)
		face[7].vert[j].colorIndex = 7;

	face[8].nVerts = 4;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 8;
	face[8].vert[1].vertIndex = 12;
	face[8].vert[2].vertIndex = 15;
	face[8].vert[3].vertIndex = 11;

	for(int j = 0 ; j < face[8].nVerts; j++)
		face[8].vert[j].colorIndex = 8;

	face[9].nVerts = 4;
	face[9].vert = new VertexID[face[8].nVerts];
	face[9].vert[0].vertIndex = 9;
	face[9].vert[1].vertIndex = 13;
	face[9].vert[2].vertIndex = 14;
	face[9].vert[3].vertIndex = 10;

	for(int j = 0 ; j < face[9].nVerts; j++)
		face[9].vert[j].colorIndex = 9;

	face[10].nVerts = 4;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 8;
	face[10].vert[1].vertIndex = 12;
	face[10].vert[2].vertIndex = 13;
	face[10].vert[3].vertIndex = 9;

	for(int j = 0 ; j < face[10].nVerts; j++)
		face[10].vert[j].colorIndex = 10;


	face[11].nVerts = 4;
	face[11].vert = new VertexID[face[11].nVerts];
	face[11].vert[0].vertIndex = 11;
	face[11].vert[1].vertIndex = 10;
	face[11].vert[2].vertIndex = 14;
	face[11].vert[3].vertIndex = 15;

	for(int j = 0 ; j < face[11].nVerts; j++)
		face[11].vert[j].colorIndex = 11;


}

void Mesh::CreateThanhNoi(int nSegment, float lenght, float height, float interRadius, float exterRadius){
	numVerts = nSegment*8 + 4*nSegment;
	pt = new Point3[numVerts];
	float fAngle = 2*PI/nSegment;
	float x,y,z;
	//Hinh tru ben chieu duong truc Ox (i = 0 ... 4*nSegment)
	for (int i = 0; i < nSegment; i++)
	{
		x = exterRadius*cos(fAngle*i) + lenght;
		z = exterRadius*sin(fAngle*i);
		y = height;
		pt[i].set(x,y,z);
		y = 0;
		pt[i+2*nSegment].set(x,y,z);

		x = interRadius*cos(fAngle*i) + lenght;
		z = interRadius*sin(fAngle*i);
		y = height;
		pt[i + nSegment].set(x,y,z);
		y = 0;
		pt[i+3*nSegment].set(x,y,z);
	}

	//Hinh tru ben chieu am truc Ox
	for (int i = 0; i < nSegment; i++)
	{
		x = exterRadius*cos(fAngle*i) ;
		z = exterRadius*sin(fAngle*i);
		y = height;
		pt[i + 4*nSegment].set(x,y,z);
		y = 0;
		pt[i+ 6*nSegment].set(x,y,z);

		x = interRadius*cos(fAngle*i); 
		z = interRadius*sin(fAngle*i);
		y = height;
		pt[i + 5*nSegment].set(x,y,z);
		y = 0;
		pt[i+7*nSegment].set(x,y,z);
	}

	
	float fAngle_quater = (PI/(2*nSegment));
	for(int i = 0; i < nSegment ; i++){
		//Diem thanh noi ben hinh tru tai truc duong
		x = exterRadius*cos(5*PI/4 - fAngle_quater*i) + lenght;
		z = exterRadius*sin(5*PI/4 - fAngle_quater*i);
		y = height - height/4;
		pt[i+8*nSegment].set(x,y,z);
		y = height/4;
		pt[i+9*nSegment].set(x,y,z);

		//Diem thanh noi ben hinh tru tai truc am

		x = exterRadius*cos(7*PI/4 + fAngle_quater*i);
		z = exterRadius*sin(7*PI/4 + fAngle_quater*i);
		y = height - height/4;
		pt[i+11*nSegment].set(x,y,z);
		y = height/4;
		pt[i+10*nSegment].set(x,y,z);


	}
	
	numFaces = nSegment*6 + 3*nSegment;
	face = new Face[numFaces];

	//Ve cac mat hinh tru ben chieu duong truc OX
	int idx = 0;
	//Ve hinh tron ben tren
	for (int i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		if(i < nSegment -1)
		{
			face[idx].vert[1].vertIndex = i+1;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		else
		{
			face[idx].vert[1].vertIndex = 0;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;
		
		idx++;
	}
	//Ve cac mat xung quay hinh tru
	for(int i = 0; i < nSegment ; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 1;
		else
			face[idx].vert[1].vertIndex = 0;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2*nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2*nSegment;
		
		idx++;
	}
	//Ve hinh tron ben duoi hinh tru
	for (int i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 2*nSegment;
		if(i < nSegment -1)
		{
			face[idx].vert[1].vertIndex = i+1 + 2*nSegment;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		else
		{
			face[idx].vert[1].vertIndex = 0+ 2*nSegment;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;
		
		idx++;
	}
 
	// Ve cac mat cua hinh tru ben chieu am truc OX
	// Ve hinh tron ben tren cua hinh tru
	for (int i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 4*nSegment;
		if(i < nSegment -1)
		{
			face[idx].vert[1].vertIndex = i+1 + 4*nSegment;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		else
		{
			face[idx].vert[1].vertIndex = 0 + 4*nSegment;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;
		
		idx++;
	}
	//Ve cac mat xung quanh cua hinh tru
	for(int i = 0; i < nSegment ; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 4*nSegment;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 1 + 4*nSegment;
		else
			face[idx].vert[1].vertIndex = 0 + 4*nSegment;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2*nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2*nSegment;
		
		idx++;
	}
	for (int i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 6*nSegment;
		if(i < nSegment -1)
		{
			face[idx].vert[1].vertIndex = i+1 + 6*nSegment;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		else
		{
			face[idx].vert[1].vertIndex = 0+ 6*nSegment;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;
		
		idx++;
	}
	//Ve cac mat thanh noi
	for (int i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 8*nSegment;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[2].vertIndex + nSegment;
		
		idx++;
	}
	for (int i = 0; i < nSegment-1; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 8*nSegment;
		face[idx].vert[1].vertIndex = i + 8*nSegment + 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 3*nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 3*nSegment;
		
		idx++;
	}

	for (int i = 0; i < nSegment-1; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 9*nSegment;
		face[idx].vert[1].vertIndex = i + 9*nSegment + 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;
		
		idx++;
	}
	int idxColor = 0;
	for(int j= 0; j < numFaces; j++)
		for(int k = 0; k < face[j].nVerts ; k++)
		{
			face[j].vert[k].colorIndex = idxColor++;
		}
}
void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor(int colorInx)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			ic = colorInx % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

//Lab3
void Mesh::SetColor(int colorIdx){
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}
void Mesh::setupMeterial(float *t1, float *t2, float *t3, float t4){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, t1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, t2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, t3);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, t4);

}
void Mesh::CalculateFacesNorm()
{
	for (int f = 0; f < numFaces; f++)
	{
		float mx = 0, my = 0, mz = 0;
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			mx += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
			my += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
			mz += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
		}
		face[f].facenorm.set(mx, my, mz);
		face[f].facenorm.normalize();
	}
}

void Mesh::Draw()
{
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

//main.cpp

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
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

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
		glEnable(GL_LIGHT1);
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
