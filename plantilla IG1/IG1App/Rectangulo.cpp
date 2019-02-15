#include "Rectangulo.h"



Rectangulo::Rectangulo(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaRectangulo(w, h);
}


Rectangulo::~Rectangulo()
{
}
void Rectangulo::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(0.0, 0.0, 0.0);
		mesh->render();
		glLineWidth(1);
	}
}