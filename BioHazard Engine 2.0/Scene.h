#pragma once
#include "Cube.h"
#include "GameObject.h"

#include <vector>
using std::vector;

class Scene : public GameObject{

private:

	vec3 dimension;

	Cube* floor;
	Cube* rightWall;
	Cube* leftWall;
	Cube* backWall;

	Cube* metalProp;
	Cube* woodProp;
	Cube* blackMetalProp;
	Cube* fabricProp;

	vector<GameObject*> gameObjects;

public:
	Scene();
	~Scene();

	void update();
	void render();
};

