#pragma once
#include "Entity.h"


class Dragon : public Entity
{
public:
	Dragon(GLuint numVert);
	~Dragon();
	virtual void render(Camera const& cam);
};

