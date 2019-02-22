#pragma once
#include "Entity.h"
class Estrella3D :
	public Entity
{
private:
	GLdouble giroY, giroZ;
	GLdouble anguloY = 0, anguloZ = 0;
public:
	Estrella3D(GLdouble re, GLdouble np, GLdouble h, GLdouble giroY, GLdouble giroZ, string file = "../Bmps/baldosaP.bmp");
	~Estrella3D();
	virtual void render(Camera const& cam);
	void update(GLuint timeElapsed);
};

