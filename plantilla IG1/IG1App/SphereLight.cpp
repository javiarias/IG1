#include "SphereLight.h"



SphereLight::SphereLight(GLuint radius, GLuint radius2, dvec3 pos, dvec3 relativePos) : Sphere(radius), relativePos(relativePos)
{
	qObj2 = gluNewQuadric();

	r2 = radius2;

	originalPos = pos;

	relativeMat = translate(dmat4(1), relativePos);

	light = new SpotLight();
	light->setDir(fvec3(0, -1, 0));
	light->setAng(40.0);
	light->setExp(5.0);
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

	updateAngle += timeElapsed * 0.001;
	if (updateAngle >= 360)
		updateAngle -= 360;

	rotationAngle += timeElapsed * 0.1 * rotationDir;
	if (rotationAngle >= 45) {
		rotationAngle = 45;
		rotationDir = -1;
	}
	else if (rotationAngle <= -45) {
		rotationAngle = -45;
		rotationDir = 1;
	}
}

void SphereLight::uploadLight(dmat4 camMat) {

	//update matrices
	GLdouble a = r2 * r2;// sqrt(4 * pi<double>() * r2 * r2) / 2;
	GLdouble b = r2;
	dmat4 updateMat = translate(dmat4(1), dvec3(a * cos(updateAngle), b * sin(updateAngle) * sin(updateAngle), -a * sin(updateAngle) * cos(updateAngle)));

	mat1 = rotate(updateMat * relativeMat, radians(rotationAngle), dvec3(1.0, 1.0, 1.0)) / (updateMat * relativeMat) * updateMat;

	mat2 = updateMat * relativeMat;


	light->upload(camMat * mat1);

}


void SphereLight::render(Camera const& cam)
{
	if (qObj != nullptr) {
		dmat4 originalMat = modelMat;

		modelMat = mat1;

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


		modelMat = mat2;
		
		material2->upload();
		gluQuadricDrawStyle(qObj2, GLU_FILL);
		gluQuadricTexture(qObj2, GL_TRUE);
		gluQuadricNormals(qObj2, GLU_SMOOTH);
		gluQuadricOrientation(qObj2, GLU_OUTSIDE);

		uploadMvM(cam.getViewMat());

		texture2->bind(GL_MODULATE);
		gluSphere(qObj2, r2, 100, 100);
		texture2->unbind();


		modelMat = originalMat;

		glDisable(GL_CULL_FACE);
	}
}