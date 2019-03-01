#pragma once
#include "Entity.h"
class Rectangulo : public Entity
{

public:
	Rectangulo(GLdouble w, GLdouble h, string file = "../Bmps/baldosaC.bmp");
	~Rectangulo();
	virtual void render(Camera const& cam);
};

