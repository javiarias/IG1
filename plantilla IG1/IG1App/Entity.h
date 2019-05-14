//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
	Entity() : modelMat(1.0) { };
	Entity(string file) : modelMat(1.0) { texture.load(file); };
	virtual ~Entity() { };

	virtual void render(Camera const& cam) = 0;
	virtual void update(GLuint timeElapsed) {}

	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	virtual void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }
  
protected:

	Mesh* mesh = nullptr;   // surface mesh
	glm::dmat4 modelMat;    // modeling matrix

	Texture texture;

	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
	EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(Camera const& cam);
};

//-------------------------------------------------------------------------

#endif //_H_Entities_H_