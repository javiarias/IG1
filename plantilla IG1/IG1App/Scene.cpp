#include "Scene.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
	  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	  glEnable(GL_DEPTH_TEST);  // enable Depth test
	  glEnable(GL_TEXTURE_2D);

	  init3D();

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

void Scene::update(GLuint timeElapsed) {
	for (Entity* el : grObjects)
	{
		el->update(timeElapsed);
	}
}

void Scene::init2D()
{
	Entity* auxEntity;
	dmat4 auxMat;

// Graphics objects (entities) of the scene
	grObjects.push_back(new EjesRGB(5));

	//rectangulo
	auxEntity = new Rectangulo(5.5, 5);
	auxMat = auxEntity->getModelMat();
	auxMat = rotate(auxMat, radians(-25.0), dvec3(0.0, 0.0, 1.0));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);

	//triangulo
	auxEntity = new TrianguloRGB(4);
	auxMat = auxEntity->getModelMat();
	auxMat = rotate(auxMat, radians(17.64), dvec3(0.0, 0.0, 1.0));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);

	//dragon
	auxEntity = new Dragon(4638);
	auxMat = auxEntity->getModelMat();
	auxMat = rotate(auxMat, radians(-75.0), dvec3(0.0, 0.0, 1.0));
	auxMat = translate(auxMat, dvec3(-40, -26, 0.0));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);

	//poliespiral
	grObjects.push_back(new Poliespiral(dvec2(0.0, 0.0), 12.5, 165, 1, 1.3, 56));
	auxMat = auxEntity->getModelMat();
	auxMat = translate(auxMat, dvec3(0.0, 0.0, -1.5));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);

	//triangulo animado
	auxEntity = new TrianguloAnimado(5, 1.0);
	auxMat = auxEntity->getModelMat();
	auxMat = translate(auxMat, dvec3(5.0, 15.0, 1.0));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);

	auxEntity = new TrianguloAnimado(1, 5.0);
	auxMat = auxEntity->getModelMat();
	auxMat = translate(auxMat, dvec3(-3.0, 7.0, 2.0));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);

	auxEntity = new TrianguloAnimado(7, 0.4);
	auxMat = auxEntity->getModelMat();
	auxMat = translate(auxMat, dvec3(20.0, -25.0, 3.0));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);

	auxEntity = new TrianguloAnimado(2, 1.0);
	auxMat = auxEntity->getModelMat();
	auxMat = translate(auxMat, dvec3(-29.0, -29.0, 4.0));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);
}

void Scene::init3D()
{
	Entity* auxEntity;
	dmat4 auxMat;

//escena 3D

	grObjects.push_back(new EjesRGB(5));

	//rectangulo
	auxEntity = new Rectangulo(20, 15);
	auxMat = auxEntity->getModelMat();
	auxMat = rotate(auxMat, radians(-90.0), dvec3(1.0, 0.0, 0.0));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);

	//Cubo
	auxEntity = new Caja(5);
	GLdouble auxLado = static_cast<Caja*>(auxEntity)->lado() / 2;
	auxMat = auxEntity->getModelMat();
	auxMat = translate(auxMat, dvec3(-auxLado, auxLado, -auxLado));
	auxMat = translate(auxMat, dvec3(0.0, 0.001, 0.0));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);

	//Estrella 3D
	auxEntity = new Estrella3D(2.5, 4, 2.5, 4, 9);
	auxMat = auxEntity->getModelMat();
	auxMat = translate(auxMat, dvec3(-auxLado, 4 * auxLado, -auxLado));
	auxEntity->setModelMat(auxMat);
	grObjects.push_back(auxEntity);
}

void Scene::clearScene()
{
	grObjects.clear();
}

void Scene::changeSceneMode()
{
	isSceneIn3D = !isSceneIn3D;

	clearScene();

	if (isSceneIn3D)
		init3D();
	else
		init2D();
}

