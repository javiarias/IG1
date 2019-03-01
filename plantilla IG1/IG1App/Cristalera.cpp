#include "Cristalera.h"
#include <gtc/matrix_transform.hpp>

using namespace glm;

Cristalera::Cristalera(GLdouble l, string boxTex) : Entity()
{
	mesh = Mesh::generaCajaTexCor(l, l / 2);
	texture.load(boxTex, 185);
}


Cristalera::~Cristalera()
{
}

void Cristalera::render(Camera const& cam)
{
	if (mesh != nullptr) {

		glDepthMask(GL_FALSE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		uploadMvM(cam.getViewMat());
		texture.bind();

		mesh->render();

		texture.unbind();

		glLineWidth(1);

		glDepthMask(GL_TRUE);
	}
}
