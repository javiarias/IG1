#pragma once
#include "Light.h"

class PosLight : public Light {
protected:
	fvec4 position = { 0, 0, 0, 1 }; // w=1 -> punto
public:
	PosLight() : Light() { }; // Constructora con parámetros !!!
	virtual void upload(dmat4 const& modelViewMat) {
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(modelViewMat));
		glLightfv(id, GL_POSITION, value_ptr(position));
		//uploadLI();
	};
	void setPos(fvec3 pos) { position = fvec4(pos, 1.0); };
};