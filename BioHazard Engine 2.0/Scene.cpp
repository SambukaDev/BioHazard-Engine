#include "Scene.h"
#include <glm.hpp>
using glm::vec3;

Scene::Scene(){

	//Set room position and size and shininess
	position = vec3(0, 0, 0);
	dimension = vec3(10, 5, 10);

	ambient = vec3(1, 1, 1);
	diffuse = vec3(0.5, 0.5, 0.5);
	specular = vec3(1, 1, 1);
	m_shininess = 20;

	GLfloat thinkness = 0.1;

	//Set floor values and store for later use
	floor = new Cube("Textures/Floor.jpg", "FLOOR");
	floor->setPosition(position);
	floor->setDimensions(vec3(dimension.x, thinkness, dimension.z));
	floor->setAmbient(vec3(1, 1, 1));
	floor->setDiffuse(vec3(0.5, 0.5, 0.5));
	floor->setSpecular(specular, m_shininess);

	gameObjects.push_back(floor);

	GLfloat width = 20;
	GLfloat height = 0.5;
	GLfloat depth = -20;

	//Set right wall values and store for later use
	rightWall = new Cube("Textures/Wall.jpg", "WALL");

	rightWall->setPosition(vec3(50, 0, 0));
	rightWall->setDimensions(vec3(thinkness, dimension.y, dimension.z));
	rightWall->setAmbient(ambient);
	rightWall->setDiffuse(diffuse);
	rightWall->setSpecular(specular, m_shininess);

	gameObjects.push_back(rightWall);

	//Set left wall values and store for later use
	leftWall = new Cube("Textures/Wall.jpg", "WALL");

	leftWall->setPosition(vec3(-50, 0, 0));
	leftWall->setDimensions(vec3(thinkness, dimension.y, dimension.z));
	leftWall->setAmbient(ambient);
	leftWall->setDiffuse(diffuse);
	leftWall->setSpecular(specular, m_shininess);

	gameObjects.push_back(leftWall);

	//Set back wall values and store for later use
	backWall = new Cube("Textures/Wall.jpg", "WALL");

	backWall->setPosition(vec3(0, 0, -50));
	backWall->setDimensions(vec3(dimension.x, dimension.y, thinkness));
	backWall->setAmbient(ambient);
	backWall->setDiffuse(diffuse);
	backWall->setSpecular(specular, m_shininess);

	gameObjects.push_back(backWall);


	//Props
	metalProp = new Cube("Textures/Metal2.jpg", "METAL");

	metalProp->setPosition(vec3(-2, 0.5, -2));
	metalProp->setAmbient(vec3(1, 1, 1));
	metalProp->setDiffuse(vec3(1, 1, 1));
	metalProp->setSpecular(vec3(1, 1, 1), 80);

	gameObjects.push_back(metalProp);


	blackMetalProp = new Cube("Textures/BlackMetal.jpg", "BLACKMETAL");

	blackMetalProp->setPosition(vec3(2, 0.5, -2));
	blackMetalProp->setAmbient(vec3(1, 1, 1));
	blackMetalProp->setDiffuse(vec3(1, 1, 1));
	blackMetalProp->setSpecular(vec3(1, 1, 1), 80);

	gameObjects.push_back(blackMetalProp);


	woodProp = new Cube("Textures/Crate.jpg", "CRATE");

	woodProp->setPosition(vec3(-2, 0.5, 2));
	woodProp->setAmbient(vec3(1, 1, 1));
	woodProp->setDiffuse(vec3(0.7, 0.7, 0.7));
	woodProp->setSpecular(vec3(0.3, 0.3, 0.3), m_shininess);

	gameObjects.push_back(woodProp);


	fabricProp = new Cube("Textures/Fabric3.jpg", "FABRIC");

	fabricProp->setPosition(vec3(2, 0.5, 2));
	fabricProp->setAmbient(vec3(1, 1, 1));
	fabricProp->setDiffuse(vec3(0.5, 0.5, 0.5));
	fabricProp->setSpecular(vec3(0, 0, 0), 1);

	gameObjects.push_back(fabricProp);
}


Scene::~Scene(){

	delete floor;
	delete rightWall;
	delete leftWall;
	delete backWall;
}


void Scene::update(){

	for (int i = 0; i < gameObjects.size(); i++){

		gameObjects[i]->update();
	}
}


void Scene::render(){

	for (int i = 0; i < gameObjects.size(); i++) {

		gameObjects[i]->render();
	}
}

