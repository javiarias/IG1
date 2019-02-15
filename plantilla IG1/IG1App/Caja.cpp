#include "Caja.h"



Caja::Caja(GLdouble l) : Entity(), l(l)
{
	mesh = Mesh::generaContCubo(l);
}


Caja::~Caja()
{
}

void Caja::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(0.1, 1.0, 0.568);
		mesh->render();
		glLineWidth(1);
	}
}
