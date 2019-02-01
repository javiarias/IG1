#include "Poliespiral.h"

using namespace glm;


Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity()
{
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
}
//-------------------------------------------------------------------------

Poliespiral::~Poliespiral()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void Poliespiral::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glColor3d(0.1, 1.0, 0.568);
		mesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------