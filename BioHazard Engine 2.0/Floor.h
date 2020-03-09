#pragma once
#include "ShaderManager.h"
#include "GameObject.h"
#include <vector>
using std::vector;

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Floor : public GameObject{

private:

	uniformShaderType shaderType;


	GLuint isWaterID;

	GLuint textureUniformID1;
	GLuint textureUniformID2;

public:
	Floor();
	~Floor();

	void update();
	void render();
};

