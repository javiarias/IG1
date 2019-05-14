#pragma once
#include "PosLight.h"
class SpotLight :
	public PosLight
{
protected:
	fvec4 spotDir = { 0.0, -1.0, 0.0, 0 };

	double exponent = 0.1;
	double angle = 45;

public:
	SpotLight() : PosLight() {  };

	virtual void upload(dmat4 const& modelViewMat) {
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(modelViewMat));
		glLightf(id, GL_SPOT_CUTOFF, angle);
		glLightf(id, GL_SPOT_EXPONENT, exponent);
		glLightfv(id, GL_SPOT_DIRECTION, value_ptr(spotDir));
		glLightfv(id, GL_POSITION, value_ptr(position));
		uploadLI();
	}

	virtual void setDir(fvec3 dir) { spotDir = fvec4(dir, 0.0); }
	virtual void setExp(double exp) { exponent = exp; }
	virtual void setAng(double ang) { angle = ang; }
	~SpotLight() {}
};

