#include "Rectangulo.h"



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

		uploadMvM(cam.getViewMat());
		texture.bind();

		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
		glLineWidth(1);

		texture.unbind();
	}
}