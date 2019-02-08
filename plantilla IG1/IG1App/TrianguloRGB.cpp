#include "TrianguloRGB.h"



TrianguloRGB::TrianguloRGB(GLdouble r)
{
	mesh = Mesh::generaTrianguloRGB(r);
}


TrianguloRGB::~TrianguloRGB()
{
}
void TrianguloRGB ::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glPointSize(2);
		glPolygonMode(GL_BACK, GL_POINT);
		glColor3d(1, 0.876456354, 0.324845312);
		mesh->render();
		glPointSize(1);
	}
}