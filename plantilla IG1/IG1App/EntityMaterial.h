#pragma once
#include "Entity.h"
class EntityMaterial :
	public Entity
{
protected:
	Texture* texture;
public:
	EntityMaterial();
	~EntityMaterial();
	void setTexture(Texture* tex);
};

