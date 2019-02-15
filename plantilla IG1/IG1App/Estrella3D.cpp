#include "Estrella3D.h"

#include <gtc/matrix_transform.hpp>

using namespace glm;

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h, GLdouble giroY, GLdouble giroZ) : Entity(), giroY(giroY), giroZ(giroZ)
{

	mesh = Mesh::generaEstrella3D(re, np, h);
}


Estrella3D::~Estrella3D()
{
}


void Estrella3D::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(0.1, 1.0, 0.568);
		mesh->render();

		dmat4 originalMat = this->getModelMat();
		
		dmat4 auxMat;
		auxMat = rotate(originalMat, radians(180.0), dvec3(0.0, 1.0, 0.0));

		this->setModelMat(auxMat);

		uploadMvM(cam.getViewMat());
		mesh->render();

		this->setModelMat(originalMat);

		glLineWidth(1);
	}
}

void Estrella3D::update() {
	dmat4 originalMat = getModelMat();

	dmat4 auxMat;
	//auxMat = rotate(dmat4(1), radians(giroZ), dvec3(0.0, 0.0, 1.0));
	auxMat = rotate(dmat4(1), radians(90.0), dvec3(0.0, 1.0, 0.0));
	auxMat = auxMat * originalMat;

	setModelMat(auxMat);
}
