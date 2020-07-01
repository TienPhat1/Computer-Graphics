#ifndef MESH_H
#define MESH_H

#include "supportClass.h"


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

#endif