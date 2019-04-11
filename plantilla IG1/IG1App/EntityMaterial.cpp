#include "EntityMaterial.h"



EntityMaterial::EntityMaterial() : Entity()
{

}


EntityMaterial::~EntityMaterial()
{
}

void EntityMaterial::setTexture(Texture * tex)
{
	texture = tex;
}

void EntityMaterial::setMaterial(Material * mat)
{
	material = mat;
}


