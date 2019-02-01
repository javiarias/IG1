#include "Dragon.h"

using namespace glm;


Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generaDragon(numVert);
}
//-------------------------------------------------------------------------

Dragon::~Dragon()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void Dragon::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glPointSize(2);
		glColor3d(1, 0.876456354, 0.324845312);
		mesh->render();
		glPointSize(1);
	}
}
//-------------------------------------------------------------------------