#include "Rectangulo.h"

#include <gtc/matrix_transform.hpp>

using namespace glm;



Rectangulo::Rectangulo(GLdouble w, GLdouble h, string file)
{
	GLdouble aspectRatio = h / w;
	int rw = 3;	//con esto las texturas se deberían ver medio cuadradas

	mesh = Mesh::generaRectanguloTexCor(w, h, rw, (int)(rw * aspectRatio));
	texture.load(file);

	foto = Mesh::generaRectanguloTexCor(w / 3, h / 3, 1, 1);
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

		dmat4 auxMat = getModelMat();
		auxMat = translate(auxMat, dvec3(0.0, 0.0, 0.01));
		setModelMat(auxMat);

		uploadMvM(cam.getViewMat());
		fotoTex.bind();
		foto->render();

		glLineWidth(1);

		fotoTex.unbind();

		setModelMat(originalMat);
	}
}

void Rectangulo::update(GLuint timeElapsed) {

	fotoTex.loadColorBuffer();

}