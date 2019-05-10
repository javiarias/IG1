#pragma once
#include "Light.h"

class DirLight : public Light {
protected:
	fvec4 direction = { 0, 0, 1, 0 }; // w=0 -> vector
public:
	DirLight() : Light() { }; // Constructora con parámetros !!!
	virtual void upload(dmat4 const& modelViewMat) {
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(modelViewMat));
		glLightfv(id, GL_POSITION, value_ptr(direction));
		uploadLI();
	};

	void setDir(fvec3 dir) { direction = fvec4(dir, 0); };

};