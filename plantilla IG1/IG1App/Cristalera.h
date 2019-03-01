#pragma once
#include "Entity.h"
class Cristalera :
	public Entity
{
private:

public:
	Cristalera(GLdouble l, string boxTex = "../Bmps/window.bmp");
	~Cristalera();

	void render(Camera const& cam);
};

