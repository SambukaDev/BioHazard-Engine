#include "POVCamera.h"

#include <glew.h>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "POVCamera.h"
#include "ScreenManager.h"
#include "ShaderManager.h"


POVCamera::POVCamera(){

	position = vec3(0, 3, 6);
	m_velocity = 0.0f;
	m_sensitivity = 0.5f;
	m_upVector.y = 1.0f;
	m_viewMatrix = glm::mat4(1.0f);
	m_threshold = glm::vec2(-0.90f, 0.90f);
	m_lookAtDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	//get shader program ID so that we can use it multiple times below
	GLuint shaderProgram = TheShader::Instance()->shaderProgramID;

	//get shader uniform and attribute IDs and store location
	m_viewUniformID = TheShader::Instance()->getUniform("view");
	m_positionUniformID = TheShader::Instance()->getUniform("cameraPosition");

	setLookAtDirection(0, 0, 1);
}


POVCamera::~POVCamera()
{
}


void POVCamera::setVelocity(GLfloat velocity){

	m_velocity = velocity;
}


void POVCamera::setViewUniformID(string uniform){

	m_viewUniformID = glGetUniformLocation(TheShader::Instance()->shaderProgramID, uniform.c_str());
}


void POVCamera::setLookAtDirection(GLfloat x, GLfloat y, GLfloat z){

	m_lookAtDirection.x = x;
	m_lookAtDirection.y = y;
	m_lookAtDirection.z = z;
}


vec3 POVCamera::getLookAt(){

	return position + m_lookAtDirection;
}


vec3 POVCamera::getPos(){

	return position;
}


void POVCamera::update(){

	keystates = SDL_GetKeyboardState(0);

	if (keystates[SDL_SCANCODE_W]) { position.z -= m_velocity / 40; }

	if (keystates[SDL_SCANCODE_A]){ position.x -= m_velocity / 40; }

	if (keystates[SDL_SCANCODE_S]){ position.z += m_velocity / 40; }

	if (keystates[SDL_SCANCODE_D]){ position.x += m_velocity / 40; }
	
	if (keystates[SDL_SCANCODE_Q]){ position.y += m_velocity / 40; }

	if (keystates[SDL_SCANCODE_E]){ position.y -= m_velocity / 40; }

	if (keystates[SDL_SCANCODE_RIGHT]) { rotateY(m_velocity); }

	if (keystates[SDL_SCANCODE_LEFT]) { rotateY(-m_velocity); }

	if (keystates[SDL_SCANCODE_UP]) { rotateX(-m_velocity); }

	if (keystates[SDL_SCANCODE_DOWN]) { rotateX(m_velocity); }

	else{ stop(); }



	m_lookAtDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::mat4 m_totalRotation = m_rotationMatrixY * m_rotationMatrixX;

	m_lookAtDirection = glm::vec3(m_totalRotation * glm::vec4(m_lookAtDirection, 1.0f));

	m_moveDirection = glm::vec3(m_rotationMatrixY * glm::vec4(m_moveDirection, 1.0f));

	if (m_moveDirection != glm::vec3(0.0f)){

		m_position += m_moveDirection * m_velocity;
	}

	//update POVCamera's view matrix
	m_viewMatrix = glm::lookAt(position, position + m_lookAtDirection, m_upVector);

}


void POVCamera::render(){

	//send view matrix data to vertex shader
	glUniformMatrix4fv(m_viewUniformID, 1, GL_FALSE, &m_viewMatrix[0][0]);

	//send POVCamera position to frag shader
	glUniform3fv(m_positionUniformID, 1, &position.x);
}


void POVCamera::stop(){

	m_moveDirection = glm::vec3(0.0f);
}


void POVCamera::moveUp(){

	m_moveDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}


void POVCamera::moveDown(){

	m_moveDirection = glm::vec3(0.0f, -1.0f, 0.0f);
}


void POVCamera::moveLeft(){

	m_moveDirection = glm::vec3(-1.0f, 0.0f, 0.0f);
}


void POVCamera::moveRight(){

	m_moveDirection = glm::vec3(1.0f, 0.0f, 0.0f);
}


void POVCamera::moveForward(){

	m_moveDirection = glm::vec3(0.0f, 0.0f, -1.0f);
}


void POVCamera::moveBackward(){

	m_moveDirection = glm::vec3(0.0f, 0.0f, 1.0f);
}


void POVCamera::rotateX(GLfloat motionY){

	GLfloat angle = motionY * m_sensitivity;

	GLdouble dot = glm::dot(m_lookAtDirection, m_upVector);

	if ((motionY > 0 && dot >= m_threshold.x) || (motionY < 0 && dot <= m_threshold.y)){

		m_rotationMatrixX = glm::rotate(m_rotationMatrixX, glm::radians(angle), vec3(-1.0f, 0.0f, 0.0f));
	}
}


void POVCamera::rotateY(GLfloat motionX){

	GLfloat angle = motionX * m_sensitivity;

	m_rotationMatrixY = glm::rotate(m_rotationMatrixY, glm::radians(angle), vec3(0.0f, -1.0f, 0.0f));
}

