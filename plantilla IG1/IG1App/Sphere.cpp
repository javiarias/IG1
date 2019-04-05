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

		gluQuadricDrawStyle(qObj, GLU_FILL);
    gluQuadricTexture(qObj, GL_TRUE);
		gluQuadricNormals(qObj, GLU_SMOOTH);
		gluQuadricOrientation(qObj,GLU_OUTSIDE);

    uploadMvM(cam.getViewMat());

    texture->bind();
    gluSphere(qObj, r, 50, 100);
    texture->unbind();


    glDisable(GL_CULL_FACE);
	}
}