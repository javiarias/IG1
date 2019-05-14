#pragma once
#include "Sphere.h"
#include "SpotLight.h"
class SphereLight :
	public Sphere
{
protected:
	Texture* texture2;
	Material* material2;

	GLUquadricObj* qObj2;
	GLuint r2;

	dvec3 relativePos;
	dvec3 originalPos;

	dmat4 relativeMat;
	dmat4 updateMat;
	
	GLdouble angle = 0;
public:
	SphereLight(GLuint radius, GLuint radius2, dvec3 pos, dvec3 relativePos);
	~SphereLight();
	virtual void render(Camera const& cam);

	SpotLight* light;

	void setTexture2(Texture* tex);

	void setMaterial2(Material* mat);

	virtual void update(GLuint timeElapsed);
};

