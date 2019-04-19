#include "SphereLight.h"



SphereLight::SphereLight(GLuint radius, dvec3 pos) : Sphere(radius)
{
	light = new SpotLight();
	light->setDir(fvec3(0, -1, 0));
	light->setPos(pos);
	light->setAng(180.0);
	light->uploadLI();
	light->enable();
}


SphereLight::~SphereLight()
{
	delete light;
}
