#include "Foto.h"


Foto::Foto(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
}


Foto::~Foto()
{
}

void Foto::update(GLuint timeElapsed) {

	texture.loadColorBuffer();

}

void Foto::render(Camera const& cam)
{
	if (mesh != nullptr) {

		uploadMvM(cam.getViewMat());
		texture.bind();

		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
		texture.unbind();

		glLineWidth(1);
	}
}