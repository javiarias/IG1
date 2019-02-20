#include "TrianguloAnimado.h"


#include <gtc/matrix_transform.hpp>

using namespace glm;


TrianguloAnimado::TrianguloAnimado(GLdouble r, GLdouble ang)
{
	mesh = Mesh::generaTrianguloRGB(r);
	anguloGiro = ang;
}


TrianguloAnimado::~TrianguloAnimado()
{
}

void TrianguloAnimado::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glPointSize(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3d(1, 0.876456354, 0.324845312);
		mesh->render();
		glPointSize(1);
	}
}

void TrianguloAnimado::update(GLuint timeElapsed) {
	dmat4 originalMat = getModelMat();

	dmat4 auxMat;
	auxMat = rotate(dmat4(1), radians(anguloGiro), dvec3(0.0, 0.0, 1.0));
	auxMat = auxMat * originalMat;
	auxMat = rotate(auxMat, radians(anguloGiro), dvec3(0.0, 0.0, 1.0));

	setModelMat(auxMat);
}