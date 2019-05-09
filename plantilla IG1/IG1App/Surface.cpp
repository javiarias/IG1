#include "Surface.h"


Surface::Surface(GLuint l, GLuint numDiv)
{
	m = IndexMesh::generateGridTex(l, numDiv);
}

Surface::~Surface()
{
	delete m;
}

void Surface::render(Camera const & cam)
{
	if (m != nullptr) {
		//glEnable(GL_CULL_FACE);

		uploadMvM(cam.getViewMat());
		texture->bind();//GL_MODULATE);

		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m->render();
		texture->unbind();

		glLineWidth(1);

		glDisable(GL_CULL_FACE);
	}


}
