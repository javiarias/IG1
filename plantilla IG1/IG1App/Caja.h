#pragma once
#include "Entity.h"
class Caja :
	public Entity
{
private:

	GLdouble l = 0;

public:
	Caja(GLdouble l);
	~Caja();

	void render(Camera const& cam);

	GLdouble lado() { return l; }
};

