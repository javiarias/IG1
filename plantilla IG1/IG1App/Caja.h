#pragma once
#include "Entity.h"
class Caja :
	public Entity
{
private:

	GLdouble l = 0;
	Mesh* bottom = nullptr;
	Texture bottomTexture;

public:
	Caja(GLdouble l, string boxTex = "../Bmps/Zelda.bmp", string bottomTex = "../Bmps/baldosaF.bmp");
	~Caja();

	void render(Camera const& cam);

	GLdouble lado() { return l; }
};

