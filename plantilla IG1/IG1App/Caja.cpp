#include "Caja.h"
#include <gtc/matrix_transform.hpp>

using namespace glm;

Caja::Caja(GLdouble l) : Entity(), l(l)
{
	mesh = Mesh::generaContCubo(l);

	bottom = Mesh::generaRectangulo(l, l);
}


Caja::~Caja()
{
}

void Caja::render(Camera const& cam)
{
	if (mesh != nullptr) {

		dmat4 originalMat = getModelMat();

		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(0.1, 1.0, 0.568);
		mesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		dmat4 auxMat = getModelMat();
		
		auxMat = translate(auxMat, dvec3(0.0, -l / 2, 0.0));

		auxMat = rotate(auxMat, radians(90.0), dvec3(1.0, 0.0, 0.0));

		setModelMat(auxMat);

		uploadMvM(cam.getViewMat());
		bottom->render();

		setModelMat(originalMat);

		glLineWidth(1);
	}
}
