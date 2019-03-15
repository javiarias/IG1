#include "Bipiramide.h"

#include <gtc/matrix_transform.hpp>

using namespace glm;

Bipiramide::Bipiramide(GLdouble l, GLdouble h, string file)
{
	mesh = Mesh::generaPiramideTexCor(l, h);
	texture.load(file, 0.5 * 255);

	alturaOriginal = h;
	alturaActual = 0;
}

Bipiramide::~Bipiramide()
{
}




void Bipiramide::render(Camera const& cam)
{
	if (mesh != nullptr) {

		glDepthMask(GL_FALSE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		dmat4 originalMat = getModelMat();

	//animación
		dmat4 auxMat = translate(getModelMat(), dvec3(0.0, alturaActual, 0.0));
		auxMat = rotate(auxMat, radians(anguloY), dvec3(0.0, 1.0, 0.0));

		setModelMat(auxMat);

		uploadMvM(cam.getViewMat());
		glPointSize(2);
		glPolygonMode(GL_FRONT, GL_FILL);
		glColor3d(1, 0.876456354, 0.324845312);
		mesh->render();

		texture.bind();

	//rotación
		auxMat = rotate(auxMat, radians(180.0), dvec3(1.0, 0.0, 0.0));
		setModelMat(auxMat);



		uploadMvM(cam.getViewMat());
		mesh->render();

		texture.unbind();

	//reinicio de matriz
		setModelMat(originalMat);

		glLineWidth(1);

		glDepthMask(GL_TRUE);
	}
}

void Bipiramide::update(GLuint timeElapsed)
{
	anguloY += giroY + 0.05 * timeElapsed;

	GLdouble testAltura = alturaActual + modificadorAltura + 0.05 * timeElapsed;

	if (testAltura >= alturaOriginal * 2 || testAltura <= 0)
		modificadorAltura = -modificadorAltura;

	alturaActual += modificadorAltura + 0.05 * timeElapsed;
}
