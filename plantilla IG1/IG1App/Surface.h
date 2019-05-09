#pragma once
#include "EntityMaterial.h"
#include "IndexMesh.h"

class Surface :
	public EntityMaterial
{
protected:
	IndexMesh *m;

public:
	Surface(GLuint l, GLuint numDiv);
	~Surface();

	void render(Camera const& cam);
};

