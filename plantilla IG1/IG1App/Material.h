#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>


using namespace glm;

class Material
{
private:
	fvec4 ambient, diffuse, specular; // coeficientes de reflexión
	GLfloat expF; // exponente especular
	GLuint face = GL_FRONT_AND_BACK; // ambos lados
	GLuint sh = GL_SMOOTH; // smooth / flat shading

public:
	virtual void upload() {
		glShadeModel(sh);
		glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	};

	void setCopper() { ambient = { 0.19125, 0.0735, 0.0225, 1.0 }; diffuse = { 0.7038, 0.27048, 0.0828, 1.0 }; specular = { 0.256777, 0.137622, 0.086014, 1.0 }; expF = 12.8; };
	void setPewter() { ambient = { 0.10588, 0.58824, 0.113725, 1.0 }; diffuse = { 0.427451, 0.470588, 0.541176, 1.0 }; specular = { 0.3333, 0.3333, 0.521569, 1.0 }; expF = 9.84615; };
	void setGoggle() { ambient = { 0.25, 0.25, 0.25, 1.0 }; diffuse = { 0.4, 0.4, 0.4, 1.0 }; specular = { 0.774597, 0.774597, 0.774597, 1.0 }; expF = 76.8; };

	Material();
	~Material();
};

