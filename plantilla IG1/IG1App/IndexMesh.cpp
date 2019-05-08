#include "IndexMesh.h"



IndexMesh::IndexMesh()
{
}


IndexMesh::~IndexMesh()
{
}

void IndexMesh::render()
{
	if (indices != nullptr) {
		glEnableClientState(GL_INDEX_ARRAY);  
		glIndexPointer(GL_UNSIGNED_INT, 0, indices);
		glDisableClientState(GL_INDEX_ARRAY);
	}

	glDrawElements(primitive, 0, numVertices,indices);
}

IndexMesh * IndexMesh::generateGridTex(GLdouble lado, GLuint numDiv)
{
	
}

IndexMesh * IndexMesh::generatePlanoCurvado(GLdouble lado, GLuint numDiv, GLdouble curvatura)
{
}
