#pragma once
#include "GameObject.h"
#include <glm.hpp>
using glm::vec3;

#include <string>
using std::string;


class Cube : public GameObject{

private:

	string texPath;
	string texID;

	void fillVerts();
	void fillNormals();
	void fillIndices();

public:
	Cube(string path, string ID);
	~Cube();

	void update();
	void render();

	void setDimensions(vec3 dim);
	void setPosition(vec3 pos);
	void setRotation(GLfloat angle, vec3 axis);

	void setAmbient(vec3 amb);
	void setDiffuse(vec3 diff);
	void setSpecular(vec3 spec, GLfloat shine);
};

