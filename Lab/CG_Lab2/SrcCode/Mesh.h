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
public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
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
	void DrawColor();

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateHollowCylinder(int nSegment, float fHeight, float interRadius, float exterRadius);
	void CreateHinhHopCoRanh(float lenght, float width , float height , float depth, float thickness);
};

#endif