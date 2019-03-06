#include "Hierba.h"
#include <gtc/matrix_transform.hpp>

using namespace glm;


Hierba::Hierba(GLdouble w, GLdouble h, GLint nr, string grassTex)
{
	mesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
	texture.load(grassTex, 0, 0, 0, 0);

	repetitions = (nr > 0) ? nr : 1;
}

Hierba::~Hierba()
{
}

void Hierba::render(Camera const & cam)
{

	if (mesh != nullptr) {

		dmat4 originalMat = getModelMat();

		glDepthMask(GL_FALSE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		for (GLdouble i = 0; i < repetitions; i++) {
			dmat4 auxMat = originalMat;

			GLdouble aux = radians(i * (180.0 / repetitions));
			auxMat = rotate(auxMat, radians(i * (180.0 / repetitions)), dvec3(0.0, 1.0, 0.0));
			setModelMat(auxMat);

			uploadMvM(cam.getViewMat());
			texture.bind();

			mesh->render();

			texture.unbind();
		}

		setModelMat(originalMat);

		glLineWidth(1);

		glDepthMask(GL_TRUE);
	}
}
