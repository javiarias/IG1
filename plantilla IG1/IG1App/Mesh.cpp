#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh::~Mesh(void) 
{
  delete[] vertices;  vertices = nullptr;
  delete[] colors;    colors = nullptr;
}
//-------------------------------------------------------------------------

void Mesh::render()
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
	
    glDrawArrays(primitive, 0, numVertices);   // primitive graphic, first index and number of elements to be rendered

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
  }
}
//-------------------------------------------------------------------------

Mesh* Mesh::createRGBAxes(GLdouble l)
{
  Mesh* m = new Mesh();
  m->primitive = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  // X axis vertices
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  // Y axis vertices
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  // Z axis vertices
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  // X axis color: red  ( Alpha = 1 : fully opaque)
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}

Mesh* Mesh::generaPoliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
{
	Mesh* m = new Mesh();
	m->primitive = GL_LINE_STRIP;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];

	GLdouble x = verIni.x;
	GLdouble y = verIni.y;

	m->vertices[0] = dvec3(x, y, 0.0);

	for (int i = 1; i < numVert; i++) {
		GLdouble newLado = ladoIni + incrLado * (i - 1);
		GLdouble newAng = angIni + incrAng * (i - 1);
		x = x + newLado * (cos(radians(newAng)));
		y = y + newLado * (sin(radians(newAng)));
		m->vertices[i] = dvec3(x, y, 0.0);
	}



	return m;
}

Mesh* Mesh::generaDragon(GLuint numVert)
{
	Mesh* m = new Mesh();
	m->primitive = GL_POINTS;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];

	GLdouble x = 0, y = 0;

	m->vertices[0] = dvec3(x, y, 0.0);

	GLdouble PR1 = 0.787473;

	for(int i = 1; i < numVert; i++){
		GLdouble azar = rand() / double(RAND_MAX);

		GLdouble xAux = x, yAux = y;

		if (azar < PR1) {
			x = 0.824074 * xAux + 0.281482 * yAux - 0.882290;
			y = -0.212346 * xAux + 0.864198 * yAux - 0.110607;
		}

		else {
			x = 0.088272 * xAux + 0.520988 * yAux + 0.785360;
			y = -0.463889 * xAux - 0.377778 * yAux + 8.095795;
		}

		m->vertices[i] = dvec3(x, y, 0.0);
	}



	return m;
}
Mesh* Mesh::generaTriangulo(GLdouble r) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];

	GLdouble x = 0, y = 0;
	for (int i = 0; i < 3; i++) {
		
		x = r * (cos(radians((120.0 * i) + 90.0)));
		y = r * (sin(radians((120.0 * i) + 90.0)));

		m->vertices[i] = dvec3(x, y, 0.0);
	}
	return m;
}
Mesh* Mesh::generaTrianguloRGB(GLdouble r) {
	Mesh* m = generaTriangulo(r);
	m->colors = new dvec4[3];
	
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);

	

	return m;
}

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];

	GLdouble x = 0, y = 0;
	m->vertices[0] = dvec3(-w / 2, h / 2, 0.0);
	m->vertices[1] = dvec3(-w / 2, -h / 2, 0.0);
	m->vertices[2] = dvec3(w / 2, h / 2, 0.0);
	m->vertices[3] = dvec3(w / 2, -h / 2, 0.0);

	return m;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
	Mesh* m = generaRectangulo(w, h);
	m->colors = new dvec4[4];

	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[3] = dvec4(1.0, 0.0, 0.0, 1.0);



	return m;
}

Mesh* Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_FAN;
	m->numVertices = 2 * np + 2;

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0, 0, 0);

	GLdouble angleIncrement = 360 / (2 * np);

	for (int i = 0; i < 2 * np + 1; i++) {
		GLdouble x = 0, y = 0;

		if (i % 2 != 0) {
			x = cos(radians(angleIncrement * -i)) * re;
			y = sin(radians(angleIncrement * -i)) * re;
		}

		else {
			x = cos(radians(angleIncrement * -i)) * (re / 2);
			y = sin(radians(angleIncrement * -i)) * (re / 2);
		}


		m->vertices[i + 1] = dvec3(x, y, h);
	}

	return m;
}



Mesh* Mesh::generaContCubo(GLdouble l) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	m->vertices = new dvec3[m->numVertices];

	GLdouble x = l / 2, y = l / 2, z = l / 2;

	m->vertices[0] = dvec3(-x, y, z);
	m->vertices[1] = dvec3(-x, -y, z);

	m->vertices[2] = dvec3(x, y, z);
	m->vertices[3] = dvec3(x, -y, z);

	m->vertices[4] = dvec3(x, y, -z);
	m->vertices[5] = dvec3(x, -y, -z);

	m->vertices[6] = dvec3(-x, y, -z);
	m->vertices[7] = dvec3(-x, -y, -z);

	m->vertices[8] = dvec3(-x, y, z);
	m->vertices[9] = dvec3(-x, -y, z);

	return m;
}
Mesh * Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* m = generaRectangulo(w, h);
	m->texCoords = new dvec2[m->numVertices];

	m->texCoords[0] = dvec2(0, rh);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(rw, rh);
	m->texCoords[3] = dvec2(rw, 0);

	return m;
}
Mesh * Mesh::generaEstrellaTexCor(GLdouble re, GLdouble np, GLdouble h)
{
	Mesh* m = generaEstrella3D(re, np, h);
	m->texCoords = new dvec2[m->numVertices];

	m->texCoords[0] = dvec2(0, 0);

	GLdouble angleIncrement = 360 / (2 * np);

	for (int i = 0; i < 2 * np + 1; i++) {
		GLdouble x = 0, y = 0;

		if (i % 2 != 0) {
			x = cos(radians(angleIncrement * -i));
			y = sin(radians(angleIncrement * -i));
		}

		else {
			x = cos(radians(angleIncrement * -i));
			y = sin(radians(angleIncrement * -i));
		}


		m->texCoords[i + 1] = dvec2(x, y);
	}

	return m;
}

Mesh * Mesh::generaCajaTexCor(GLdouble l)
{
	Mesh* m = generaContCubo(l);
	m->texCoords = new dvec2[m->numVertices];

	GLdouble x = 1, y = 1;

	m->texCoords[0] = dvec2(0, y);
	m->texCoords[1] = dvec2(0, 0);

	m->texCoords[2] = dvec2(x, y);
	m->texCoords[3] = dvec2(x, 0);

	m->texCoords[4] = dvec2(0, y);
	m->texCoords[5] = dvec2(0, 0);

	m->texCoords[6] = dvec2(x, y);
	m->texCoords[7] = dvec2(x, 0);

	m->texCoords[8] = dvec2(0, y);
	m->texCoords[9] = dvec2(0, 0);

	return m;
}
//-------------------------------------------------------------------------
