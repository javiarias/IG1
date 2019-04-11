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
#include "Foto.h"
#include "Cristalera.h"
#include "Hierba.h"
#include "Sphere.h"
#include "DirLight.h"
#include "SpotLight.h"

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

	enum TextureEnum {
		Sun,
		Moon,
		Mars,
		Earth,
		Desert,
		Red,
		Terrain,
		TerrainG
	};

	std::vector<pair<int, string>> TexturePaths{
	{Sun, "sun.bmp"},
	{Moon, "moon.bmp"},
	{Mars, "mars.bmp"},
	{Earth, "earth.bmp"},
	{Desert, "desierto.bmp"},
	{Red, "BarrenReds.bmp"},
	{Terrain, "terreno.bmp"},
	{TerrainG, "terrenoG.bmp"}
	};
	
	enum MaterialEnum {
		Copper,
		Chrome,
		Pewter,


		END
	};
	  
protected:

	std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
	std::vector<Texture*> textures;
	std::vector<Material*> mats;

	void init2D();
	void init3D();
	void initQuad();
	void clearScene();

	bool isSceneIn3D = false;

	//luces 
	DirLight* dirLight;
	
	SpotLight* camLight;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

