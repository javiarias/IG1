//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
//#include "Mesh.h"
#include "Poliespiral.h"
#include "Dragon.h"
#include "TrianguloRGB.h"
#include "Rectangulo.h"
#include "TrianguloAnimado.h"
#include "Estrella3D.h"
#include "Caja.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene() { };
	~Scene();
    void init(); 

    void render(Camera const& cam);

	void update(GLuint timeElapsed);

	void changeSceneMode();
	  
protected:

	  std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene

	  void init2D();
	  void init3D();
	  void clearScene();

	  bool isSceneIn3D = true;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

