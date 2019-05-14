#include "SphereLight.h"



SphereLight::SphereLight(GLuint radius, GLuint radius2, dvec3 pos, dvec3 relativePos) : Sphere(radius), relativePos(relativePos)
{
	qObj2 = gluNewQuadric();

	r2 = radius2;

	originalPos = pos;

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
	updateMat2 = translate(dmat4(1), relativePos);


	GLdouble a = sqrt(4 * pi<double>() * r * r) / 2;
	GLdouble b = r;

	updateMat = translate(modelMat, dvec3(a * cos(angle), b * sin(angle) * sin(angle), -a * sin(angle) * cos(angle)));

	angle += timeElapsed * 0.001;
	if (angle >= 360)
		angle -= 360;
}

void SphereLight::setModelMat(glm::dmat4 const& aMat)
{
	Entity::setModelMat(aMat);

	update(0);
}


void SphereLight::render(Camera const& cam)
{
	if (qObj != nullptr) {
		dmat4 aux = modelMat;

		modelMat = updateMat;

		glEnable(GL_CULL_FACE);

		material->upload();
		gluQuadricDrawStyle(qObj, GLU_FILL);
		gluQuadricTexture(qObj, GL_TRUE);
		gluQuadricNormals(qObj, GLU_SMOOTH);
		gluQuadricOrientation(qObj, GLU_OUTSIDE);

		uploadMvM(cam.getViewMat());

		texture->bind(GL_MODULATE);
		gluSphere(qObj, r, 100, 100);
		texture->unbind();

		modelMat = updateMat * updateMat2;

		material2->upload();
		gluQuadricDrawStyle(qObj2, GLU_LINE);
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