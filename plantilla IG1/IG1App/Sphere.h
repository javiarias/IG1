#pragma once
#include "EntityMaterial.h"
class Sphere :
	public EntityMaterial
{
protected:
	GLUquadricObj *qObj;
	GLuint r;

public:
	Sphere(GLuint radius);
	~Sphere();
	virtual void render(Camera const& cam);
};

