#pragma once
#include "EntityMaterial.h"
#include "IndexMesh.h"

class Surface :
	public EntityMaterial
{
protected:
	IndexMesh *m;

public:
	Surface(GLuint l, GLuint numDiv, GLdouble curve);
	~Surface();

	void render(Camera const& cam);
};

