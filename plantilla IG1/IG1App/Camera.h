//#pragma once
#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Viewport.h"

using namespace glm;
//-------------------------------------------------------------------------

class Camera {
public:
	Camera(Viewport* avp) : vp(avp), viewMat(1.0), projMat(1.0),
							xRight(avp->getW() / 2.0), xLeft(-xRight), 
							yTop(avp->getH() / 2.0), yBot(-yTop) { };
	~Camera() {};
	Viewport* getVP() { return vp; }

	// view matrix (the inverse of modeling matrix)
	dmat4 const& getViewMat() const { return viewMat; };
	void uploadVM() const; // transfers viewMat to the GPU

	void set2D();  // eye(0,0,500), look(0,0,0), up(0, 1, 0)
	void set3D();  // eye(500,500,500), look(0,10,0), up(0, 1, 0)

	void setAxes();
	void setVM();

	void moveLR(GLdouble cs); // Left / Right
	void moveFB(GLdouble cs); // Forward / Backward
	void moveUD(GLdouble cs); // Up / Down 
    
	/*
	void pitch(GLdouble a); // rotates a degrees on the X axis
	void yaw(GLdouble a);   // rotates a degrees on the Y axis
	void roll(GLdouble a);  // rotates a degrees on the Z axis
	*/

	// projection matrix
	dmat4 const& getProjMat() const { return projMat; };
	void uploadPM() const;  // transfers projMat to the GPU

	// set scene visible area size and transfers projMat to the GPU
	void uploadSize(GLdouble aw, GLdouble ah); 

	// update scale factor and transfers projMat to GPU
	void uploadScale(GLdouble s); 

	void orbit(GLdouble incAng, GLdouble incY);

	void changeProj();

protected:
	
	dmat4 viewMat;    // view matrix = inverse of modeling matrix
	
	dmat4 projMat;     // projection matrix
	
	GLdouble xRight, xLeft, yTop, yBot;    // size of scene visible area
	GLdouble nearVal = 1, farVal = 10000;  // view volume
	GLdouble factScale = 1;
	
	Viewport* vp;

	dvec3 eye, look, up;		//to generate view matrix (viewMat). Eye is the position, look the look vector and up the inclination
	dvec3 right, upward, front;	//for the u (right), v (upward) and -n (front) axes, used to calculate the camera's movement

	GLdouble orbitAngle = 0;
	GLdouble orbitRadius = 500;

	bool isOrthogonal = true;
};

//-------------------------------------------------------------------------

#endif //_H_Camera_H_