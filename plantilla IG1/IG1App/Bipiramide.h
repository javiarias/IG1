#pragma once
#include "Entity.h"
class Bipiramide :
	public Entity
{
private:
	GLdouble alturaOriginal = 0;
	GLdouble alturaActual = 0;
	GLdouble modificadorAltura = 3;
	GLdouble anguloY = 0;
	GLdouble giroY = 3;

public:
	Bipiramide(GLdouble l, GLdouble h, string file = "../Bmps/sierpinski.bmp");
	~Bipiramide();


	virtual void render(Camera const& cam);
	void update(GLuint timeElapsed);
};

