#pragma once
#include "PosLight.h"
class SpotLight :
	public PosLight
{
public:
	SpotLight() : PosLight() {  };
	~SpotLight();
};

