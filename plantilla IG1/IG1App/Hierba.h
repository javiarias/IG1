#pragma once
#include "Entity.h"
class Hierba :
	public Entity
{
private:
	GLint repetitions = 1;

public:
	Hierba(GLdouble w, GLdouble h, GLint nr, string grassTex = "../Bmps/grass.bmp");
	~Hierba();

	void render(Camera const& cam);
};
