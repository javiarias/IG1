#include "SphereLight.h"



SphereLight::SphereLight(GLuint radius, GLuint radius2, dvec3 pos, dvec3 relativePos) : Sphere(radius), relativePos(relativePos)
{
	qObj2 = gluNewQuadric();

	r2 = radius2;

	originalPos = pos;

	relativeMat = translate(dmat4(1), relativePos);

	light = new SpotLight();
	light->setDir(fvec3(0, -1, 0));
	light->setAng(90.0);
	light->enable();
}


SphereLight::~SphereLight()
{
	delete light;
}

void SphereLight::setTexture2(Texture* tex)
{
	texture2 = tex;
}

void SphereLight::setMaterial2(Material* mat)
{
	material2 = mat;
}

void SphereLight::update(GLuint timeElapsed)
{

	angle += timeElapsed * 0.001;
	if (angle >= 360)
		angle -= 360;
}


void SphereLight::render(Camera const& cam)
{
	if (qObj != nullptr) {
		dmat4 aux = modelMat;


		glEnable(GL_CULL_FACE);

		material->upload();
		gluQuadricDrawStyle(qObj, GLU_LINE);
		gluQuadricTexture(qObj, GL_TRUE);
		gluQuadricNormals(qObj, GLU_SMOOTH);
		gluQuadricOrientation(qObj, GLU_OUTSIDE);

		uploadMvM(cam.getViewMat());

		texture->bind(GL_MODULATE);
		gluSphere(qObj, r, 50, 50);
		texture->unbind();

		modelMat = aux * relativeMat;

		GLdouble a = sqrt(4 * pi<double>() * r2 * r2) / 2;
		GLdouble b = r2;
		modelMat = translate(modelMat, dvec3(a * cos(angle), b * sin(angle) * sin(angle), -a * sin(angle) * cos(angle)));

		material2->upload();
		gluQuadricDrawStyle(qObj2, GLU_FILL);
		gluQuadricTexture(qObj2, GL_TRUE);
		gluQuadricNormals(qObj2, GLU_SMOOTH);
		gluQuadricOrientation(qObj2, GLU_OUTSIDE);

		uploadMvM(cam.getViewMat());

		texture2->bind(GL_MODULATE);
		gluSphere(qObj2, r2, 100, 100);
		texture2->unbind();

		modelMat = aux;

		glDisable(GL_CULL_FACE);
	}
}