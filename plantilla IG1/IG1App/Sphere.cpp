#include "Sphere.h"



Sphere::Sphere(GLuint radius)
{
  qObj = gluNewQuadric();

  r = radius;
}


Sphere::~Sphere()
{
  gluDeleteQuadric(qObj);
}

void Sphere ::render(Camera const& cam)
{
	if (qObj != nullptr) {
		glEnable(GL_CULL_FACE);
		material->upload();
		gluQuadricDrawStyle(qObj, GLU_FILL);
		gluQuadricTexture(qObj, GL_TRUE);
		gluQuadricNormals(qObj, GLU_SMOOTH);
		gluQuadricOrientation(qObj,GLU_OUTSIDE);

		uploadMvM(cam.getViewMat());

		material->upload();
		texture->bind();
		gluSphere(qObj, r, 100, 100);
		texture->unbind();


		glDisable(GL_CULL_FACE);
	}
}