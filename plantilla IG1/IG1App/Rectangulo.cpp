#include "Rectangulo.h"



Rectangulo::Rectangulo(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaRectanguloRGB(w, h);
}


Rectangulo::~Rectangulo()
{
}
void Rectangulo::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glPointSize(2);
		glPolygonMode(GL_BACK, GL_LINE);
		glColor3d(1, 0.876456354, 0.324845312);
		mesh->render();
		glPointSize(1);
	}
}