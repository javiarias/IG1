#include "Caja.h"
#include <gtc/matrix_transform.hpp>

using namespace glm;

Caja::Caja(GLdouble l, string boxTex, string bottomTex) : Entity(), l(l)
{
	mesh = Mesh::generaCajaTexCor(l);
	texture.load(boxTex);

	bottom = Mesh::generaRectanguloTexCor(l, l, 1, 1);
	bottomTexture.load(bottomTex);
}


Caja::~Caja()
{
}

void Caja::render(Camera const& cam)
{
	if (mesh != nullptr) {

		dmat4 originalMat = getModelMat();

		uploadMvM(cam.getViewMat());
		texture.bind();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		mesh->render();

		texture.unbind();
		glDisable(GL_CULL_FACE);

		uploadMvM(cam.getViewMat());
		bottomTexture.bind();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		mesh->render();

		bottomTexture.unbind();
		glDisable(GL_CULL_FACE);

		dmat4 auxMat = getModelMat();
		auxMat = translate(auxMat, dvec3(0.0, -l / 2, 0.0));
		auxMat = rotate(auxMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
		setModelMat(auxMat);

		uploadMvM(cam.getViewMat());
		bottomTexture.bind();

		bottom->render();

		bottomTexture.unbind();

		setModelMat(originalMat);

		glLineWidth(1);
	}
}
