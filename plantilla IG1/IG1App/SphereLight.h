#pragma once
#include "Sphere.h"
#include "SpotLight.h"
class SphereLight :
	public Sphere
{
public:
	SphereLight(GLuint radius, dvec3 pos);
	~SphereLight();

	SpotLight* light;
};

