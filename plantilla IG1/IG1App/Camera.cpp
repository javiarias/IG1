#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/matrix_access.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Camera::set2D() 
{
	orbitAngle = 270;

	eye = dvec3(0, 0, orbitRadius);
	look= dvec3(0, 0, 0);
	up= dvec3(0, 1, 0);

	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
	orbitAngle = 315;

	look = dvec3(0, 10, 0);
	up = dvec3(0, 1, 0);


	eye = dvec3(orbitRadius, orbitRadius, orbitRadius);
	eye.x = look.x + cos(radians(orbitAngle)) * orbitRadius;
	eye.z = look.z - sin(radians(orbitAngle)) * orbitRadius;

	setVM();
}
//-------------------------------------------------------------------------

void Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

/*
void Camera::pitch(GLdouble a) 
{  
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
*/
//-------------------------------------------------------------------------

void Camera::uploadSize(GLdouble aw, GLdouble ah)
{
	xRight = aw / 2.0;
	xLeft = -xRight;
	yTop = ah / 2.0;
	yBot = -yTop;

	if (isOrthogonal)
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	else
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, yTop, farVal);

	uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadScale(GLdouble s)
{
	factScale -= s;
	if (factScale < 0) factScale = 0.01;

	if(isOrthogonal)
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	else
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, yTop, farVal);

	uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadPM() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------

void Camera::setAxes() {
	right = row(viewMat, 0);
	upward = row(viewMat, 1);
	front = -row(viewMat, 2);
}
//-------------------------------------------------------------------------

void Camera::setVM() {
	viewMat = lookAt(eye, look, up);
	setAxes();
}
//-------------------------------------------------------------------------

void Camera::moveUD(GLdouble cs) { // Up / Down
	eye += upward * cs;
	look += upward * cs;
	setVM();
}
//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs) { // Left / Right
	eye += right * cs;
	look += right * cs;
	setVM();
}
//-------------------------------------------------------------------------

void Camera::moveFB(GLdouble cs) { // Forward / Backward
	eye += front * cs;
	look += front * cs;
	setVM();
}
//-------------------------------------------------------------------------

void Camera::orbit(GLdouble incAng, GLdouble incY) {
	orbitAngle += incAng;
	eye.x = look.x + cos(radians(orbitAngle)) * orbitRadius;
	eye.z = look.z - sin(radians(orbitAngle)) * orbitRadius;
	eye.y += incY;
	setVM();
}

void Camera::changeProj()
{
	isOrthogonal = !isOrthogonal;

	if (isOrthogonal)
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	else
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, yTop, farVal);


	uploadPM();
}

void Camera::setTopDown()
{
	eye = dvec3(0, orbitRadius, 0);
	look = dvec3(0, 0, 0);
	up = dvec3(0, 0, -1);

	uploadScale(0.5);

	setVM();
}
