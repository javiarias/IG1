#include "Rectangulo.h"

#include <gtc/matrix_transform.hpp>

using namespace glm;



Rectangulo::Rectangulo(GLdouble w, GLdouble h, string file)
{
	GLdouble aspectRatio = h / w;
	int rw = 3;	//con esto las texturas se deberían ver medio cuadradas

	mesh = Mesh::generaRectanguloTexCor(w, h, rw, (int)(rw * aspectRatio));
	texture.load(file);
}


Rectangulo::~Rectangulo()
{
}

void Rectangulo::render(Camera const& cam)
{
	if (mesh != nullptr) {

		dmat4 originalMat = getModelMat();

		uploadMvM(cam.getViewMat());
		texture.bind();

		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
		texture.unbind();

		glLineWidth(1);

		setModelMat(originalMat);
	}
}