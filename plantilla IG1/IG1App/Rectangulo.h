#pragma once
#include "Entity.h"
class Rectangulo : public Entity
{
public:
	Rectangulo(GLdouble w, GLdouble h);
	~Rectangulo();
	virtual void render(Camera const& cam);
};

