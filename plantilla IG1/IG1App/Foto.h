#pragma once
#include "Entity.h"
class Foto :
	public Entity
{
public:
	Foto(GLdouble w, GLdouble h);
	~Foto();

	virtual void update(GLuint timeElapsed);
	virtual void render(Camera const& cam);
};

