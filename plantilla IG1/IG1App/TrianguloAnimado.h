#pragma once
#include "Entity.h"
class TrianguloAnimado : public Entity
{
private:
	GLdouble anguloGiro = 0;

public:
	TrianguloAnimado(GLdouble r, GLdouble ang);
	~TrianguloAnimado();
	virtual void render(Camera const& cam);

	void update(GLuint timeElapsed);
};

