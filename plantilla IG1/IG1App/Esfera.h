#pragma once
#include "EntityMaterial.h"
class Esfera :
	public EntityMaterial
{
protected:
	GLUquadricObj *qObj;
public:
	Esfera(GLuint radio);
	~Esfera();
	void render(Camera const& cam);
};

