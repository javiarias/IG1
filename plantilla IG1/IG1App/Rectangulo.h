#pragma once
#include "Entity.h"
class Rectangulo : public Entity
{
private:
	Mesh* foto;
	Texture fotoTex;

public:
	Rectangulo(GLdouble w, GLdouble h, string file = "../Bmps/baldosaC.bmp");
	~Rectangulo();
	virtual void render(Camera const& cam);
	virtual void update(GLuint timeElapsed);
};

