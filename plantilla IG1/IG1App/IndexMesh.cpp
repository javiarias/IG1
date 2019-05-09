#include "IndexMesh.h"

using namespace glm;


IndexMesh::IndexMesh()
{
	primitive = GL_TRIANGLES;
}


IndexMesh::~IndexMesh()
{
	delete[] indices;
}

void IndexMesh::render()
{
	if (indices != nullptr) {
		glEnableClientState(GL_INDEX_ARRAY);  
		glIndexPointer(GL_UNSIGNED_INT, 0, indices);
	}

	glDrawElements(primitive, 0, numVertices,indices);


	glDisableClientState(GL_INDEX_ARRAY);
}

IndexMesh * IndexMesh::generateGrid(GLdouble lado, GLuint numDiv)
{
	IndexMesh* m = new IndexMesh();
	GLdouble incr = lado / numDiv; // incremento para la coordenada x, y la c. z
	GLuint numFC = numDiv + 1; // número de vértices por filas y columnas

	m->numVertices = numFC * numFC; // número de vértices
	m->vertices = new dvec3[m->numVertices];

	for (int i = 0; i < numDiv; i++) {
		for (int j = 0; j < numDiv; j++) {
			m->vertices[i * numFC + j] = dvec3(-lado/2 + j * incr, 0, -lado / 2 + i * incr);
		}
	}


	m->numIndices = numDiv * numDiv * 6; // número de índices
	m->indices = new GLuint[m->numIndices];

	GLuint index = 0;
	for (int i = 0; i < numDiv; i++) {
		for (int j = 0; j < numDiv; j++) {
			GLuint iv = i * numFC + j;
			m->indices[index] = iv;
			index++;
			m->indices[index] = iv + numFC;
			index++;
			m->indices[index] = iv + 1;
			index++;
			m->indices[index] = iv + 1;
			index++;
			m->indices[index] = iv + numFC;
			index++;
			m->indices[index] = iv + numFC + 1;
			index++;
		}
	}

	return m;
}

IndexMesh * IndexMesh::generateGridTex(GLdouble lado, GLuint numDiv)
{
	IndexMesh* m = generateGrid(lado, numDiv);
	GLuint numFC = numDiv + 1;
	m->texCoords = new dvec2[m->numVertices];



	return m;
}

IndexMesh * IndexMesh::generatePlanoCurvado(GLdouble lado, GLuint numDiv, GLdouble curvatura)
{
}
