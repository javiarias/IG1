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
