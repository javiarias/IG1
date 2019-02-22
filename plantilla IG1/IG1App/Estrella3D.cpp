#include "Estrella3D.h"

#include <gtc/matrix_transform.hpp>

using namespace glm;

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h, GLdouble giroY, GLdouble giroZ, string file) : Entity(), giroY(giroY), giroZ(giroZ)
{

	mesh = Mesh::generaEstrella3D(re, np, h);
	texture.load(file);

}


Estrella3D::~Estrella3D()
{
}


void Estrella3D::render(Camera const& cam)
{
	if (mesh != nullptr) {

	//rotaci�n
		dmat4 originalMat = getModelMat();

		dmat4 auxMat = rotate(getModelMat(), radians(anguloY), dvec3(0.0, 1.0, 0.0));
		auxMat = rotate(auxMat, radians(anguloZ), dvec3(0.0, 0.0, 1.0));

		setModelMat(auxMat);


		texture.bind();

		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();


		auxMat = rotate(auxMat, radians(180.0), dvec3(0.0, 1.0, 0.0));

		setModelMat(auxMat);

		uploadMvM(cam.getViewMat());
		mesh->render();

	//reinicio de matriz
		setModelMat(originalMat);

		glLineWidth(1);

		texture.unbind();
	}
}

void Estrella3D::update(GLuint timeElapsed) {

	anguloY += giroY;
	anguloZ += giroZ;

}
