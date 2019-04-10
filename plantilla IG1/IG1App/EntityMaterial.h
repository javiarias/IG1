#pragma once
#include "Entity.h"
#include "Material.h"
class EntityMaterial :
	public Entity
{
protected:
	Texture* texture;
	Material* material;
public:
	EntityMaterial();
	~EntityMaterial();
	void setTexture(Texture* tex);

	void setMaterial(Material* mat);
};

