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
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 

		if (colors != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
		}

		if (texCoords != nullptr) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
		}

		if (normals != nullptr) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, normals);
		}

		if (indices != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, indices);
		}

		glDrawElements(primitive, numIndices, GL_UNSIGNED_INT, indices);


		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY);
	}
}

IndexMesh * IndexMesh::generateGrid(GLdouble lado, GLuint numDiv)
{
	IndexMesh* m = new IndexMesh();
	double incr = lado / numDiv; // incremento para la coordenada x, y la c. z
	GLuint numFC = numDiv + 1; // número de vértices por filas y columnas

	m->numVertices = numFC * numFC; // número de vértices
	m->vertices = new dvec3[m->numVertices];

	for (int i = 0; i < numDiv; i++) {
		for (int j = 0; j < numDiv; j++) {
			m->vertices[i * numFC + j] = dvec3(-lado / 2 + j * incr, 0, -lado / 2 + i * incr);
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

	GLuint s = 0;
	GLuint t = 1;

	for (int i = 0; i < numDiv; i++) {
		for (int j = 0; j < numDiv; j++) {
			m->texCoords[i * numFC + j] = dvec2(s + j / (GLdouble)numDiv , t - i / (GLdouble)numDiv);
		}
	}

	return m;
}

IndexMesh * IndexMesh::generatePlanoCurvado(GLdouble lado, GLuint numDiv, GLdouble curvatura)
{
	IndexMesh* m = generateGridTex(lado, numDiv);

	m->normals = new dvec3[m->numVertices];

	for (int i = 0; i < m->numVertices; i++) {
		GLdouble x = m->vertices[i].x;
		GLdouble z = m->vertices[i].z;

		m->vertices[i] = dvec3(x, lado * curvatura / 2 - curvatura / lado * x * x - curvatura / lado * z * z, z);
		m->normals[i] = dvec3(2 * curvatura / lado * x, 1.0, 2 * curvatura / lado * z);
	}

	return m;
}
