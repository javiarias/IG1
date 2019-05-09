#pragma once
#include "Mesh.h"
class IndexMesh :
	public Mesh
{
public:
	IndexMesh();
	~IndexMesh();
	void render();
	static IndexMesh* generateGrid(GLdouble lado, GLuint numDiv);
	static IndexMesh* generateGridTex(GLdouble lado, GLuint numDiv);
	static IndexMesh*  generatePlanoCurvado(GLdouble  lado, GLuint numDiv, GLdouble curvatura);

protected:
	GLuint* indices = nullptr;
	GLuint numIndices = 0;
};

