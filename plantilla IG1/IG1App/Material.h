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
  virtual void upload() {
    glShadeModel(sh);
    glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
  };
public:
  Material();
  ~Material();
};

