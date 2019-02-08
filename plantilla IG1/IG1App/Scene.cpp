#include "Scene.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
	  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	  glEnable(GL_DEPTH_TEST);  // enable Depth test 

	  Entity* auxEntity;
	  dmat4 auxMat;
     
	  // lights
	  // textures  
	  // meshes

	  // Graphics objects (entities) of the scene
	  /*grObjects.push_back(new EjesRGB(5));

	  //rectangulo
	  auxEntity = new Rectangulo(5.5, 5);
	  auxMat = auxEntity->getModelMat();
	  auxMat = rotate(auxMat, radians(-25.0), dvec3(0.0, 0.0, 1.0));
	  auxMat = translate(auxMat, dvec3(7.0, 4.0, 0.0));
	  auxEntity->setModelMat(auxMat);
	  grObjects.push_back(auxEntity);

	  //triangulo
	  auxEntity = new TrianguloRGB(4);
	  auxMat = auxEntity->getModelMat();
	  auxMat = rotate(auxMat, radians(17.64), dvec3(0.0, 0.0, 1.0));
	  auxMat = translate(auxMat, dvec3(-1.2, 1.7, 0.0));
	  auxEntity->setModelMat(auxMat);
	  grObjects.push_back(auxEntity);

	  //dragon
	  auxEntity = new Dragon(4638);
	  auxMat = auxEntity->getModelMat();
	  auxMat = rotate(auxMat, radians(-75.0), dvec3(0.0, 0.0, 1.0));
	  auxMat = translate(auxMat, dvec3(-16.2, -6.7, 0.0));
	  auxEntity->setModelMat(auxMat);
	  grObjects.push_back(auxEntity);

	  //dragon
	  grObjects.push_back(new Poliespiral(dvec2(0.0, 0.0), 12.5, 165, 1, 1.3, 56));*/

	  //triangulo animado
	  auxEntity = new TrianguloAnimado(5, 1.50);
	  auxMat = auxEntity->getModelMat();
	  auxMat = translate(auxMat, dvec3(5.0, 15.0, 0.0));
	  auxEntity->setModelMat(auxMat);
	  grObjects.push_back(auxEntity);

	  auxEntity = new TrianguloAnimado(5, 2.017);
	  auxMat = auxEntity->getModelMat();
	  auxMat = translate(auxMat, dvec3(10.0, 30.0, 0.0));
	  auxEntity->setModelMat(auxMat);
	  grObjects.push_back(auxEntity);

	  auxEntity = new TrianguloAnimado(5, 4.319);
	  auxMat = auxEntity->getModelMat();
	  auxMat = translate(auxMat, dvec3(15.0, 45.0, 0.0));
	  auxEntity->setModelMat(auxMat);
	  grObjects.push_back(auxEntity);
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam)
{
	for (Entity* el: grObjects)
	{
		el->render(cam);
	}
}
//-------------------------------------------------------------------------

void Scene::update() {
	for (Entity* el : grObjects)
	{
		el->update();
	}
}

