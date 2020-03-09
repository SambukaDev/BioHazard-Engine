#pragma once
#include "GameObject.h"

#include <string>
#include <glew.h>
#include <glm.hpp>
using glm::mat4;
using glm::vec2;
using glm::vec3;
using glm::uint8;

class POVCamera : public GameObject{

private:

	const uint8* keystates;

	GLfloat m_velocity;
	GLfloat m_sensitivity;

	GLuint m_viewUniformID;
	GLuint m_positionUniformID;

	mat4 m_viewMatrix;
	mat4 m_rotationMatrixX;
	mat4 m_rotationMatrixY;

	vec2 m_threshold;
	vec3 m_position;
	vec3 m_upVector;
	vec3 m_moveDirection;
	vec3 m_lookAtDirection;

public:
	POVCamera();
	~POVCamera();

	void setVelocity(GLfloat velocity);
	void setViewUniformID(std::string uniform);
	void setLookAtDirection(GLfloat x, GLfloat y, GLfloat z);
	vec3 getLookAt();
	vec3 getPos();

	void stop();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();
	void rotateX(GLfloat motionY);
	void rotateY(GLfloat motionX);

	void update();
	void render();
};

