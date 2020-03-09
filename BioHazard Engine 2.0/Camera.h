#pragma once
#include <glew.h>

#include "ShaderManager.h"
//#include "EventHandler.h"

#include <glm.hpp>
using glm::vec3;
using glm::mat4;
using glm::uint8;

class Camera{

private:

	const uint8* keystates;

	GLfloat movementSpeed;

	vec3 position;
	vec3 viewDirection;
	vec3 moveDirection;

	GLuint positionUniformID;
	//GLuint viewDirectionUniformID;

	GLuint viewUniformID;
	mat4 viewMatrix;
	mat4 xRotation;
	mat4 yRotation;
	mat4 totalRotation;


public:
	Camera();
	~Camera();

	void update();
	void render();

	//void onKeyboardEvent(const SDL_KeyboardEvent& e);
};

