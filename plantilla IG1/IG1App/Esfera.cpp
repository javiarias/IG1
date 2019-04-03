#include "Esfera.h"



Esfera::Esfera(GLuint radio)
{
	gluSphere(qObj, radio, 50, 50);
}


Esfera::~Esfera()
{
}

void Esfera ::render(Camera const& cam)
{
	if (qObj != nullptr) {

		gluQuadricDrawStyle(qObj, GLU_FILL);
		gluQuadricNormals(qObj, GLU_SMOOTH);
		gluQuadricOrientation(qObj,GLU_OUTSIDE);
		gluQuadricTexture(qObj, GL_FALSE);
		

		uploadMvM(cam.getViewMat());
		

		

		
	}
}