#include "Camera.h"
#include "Input.h"
#include <gtc\matrix_transform.hpp>

Camera::Camera(){

	//positionUniformID = TheShader::Instance()->getUniform("cameraPosition");
	//positionUniformID = TheShader::Instance()->getUniform("viewDirection");

	//glUniform3fv(positionUniformID, 1, &position.x);
	//glUniform3fv(viewDirectionUniformID, 1, &viewDirection.x);

	viewUniformID = TheShader::Instance()->getUniform("view");
	position.y = 1;

	movementSpeed = 5.0f;

	positionUniformID = TheShader::Instance()->getUniform("cameraPosition");

	//TheInput::Instance()->registerGameObject(this);
}


Camera::~Camera(){

	//TheInput::Instance()->unregisterGameObject(this);
}



void Camera::update(){

	//reset view
	viewDirection = glm::vec3(0, 0, -1);

	//read keys for position
	keystates = SDL_GetKeyboardState(0);
	if (keystates[SDL_SCANCODE_W]) {

		moveDirection = glm::vec3(0, 0, -0.5);
	}

	if (keystates[SDL_SCANCODE_A]) {

		moveDirection = glm::vec3(-0.5, 0, 0);
	}

	if (keystates[SDL_SCANCODE_S]) {

		moveDirection = glm::vec3(0, 0, 0.5);
	}

	if (keystates[SDL_SCANCODE_D]) {

		moveDirection = glm::vec3(0.5, 0, 0);
	}

	//rotation = mat4(1);

	//read keys to rotate cam
	if (keystates[SDL_SCANCODE_UP]) {

		xRotation = glm::rotate(xRotation, glm::radians(10.0f), vec3(1, 0, 0));
	}

	if (keystates[SDL_SCANCODE_DOWN]) {

		xRotation = glm::rotate(xRotation, glm::radians(-10.0f), vec3(1, 0, 0));
	}

	if (keystates[SDL_SCANCODE_LEFT]) {

		yRotation = glm::rotate(yRotation, glm::radians(-10.0f), vec3(0, 1, 0));
	}

	if (keystates[SDL_SCANCODE_RIGHT]) {

		yRotation = glm::rotate(yRotation, glm::radians(10.0f), vec3(0, 1, 0));
	}

	//moveDirection = vec3(0);

	//create rot matrix based on rotation angle
	
	//rotation = glm::rotate(rotation, glm::radians(10.0f), vec3(0, 1, 0));

	totalRotation = xRotation * yRotation;

	//mult rot matrix * moveDir
	moveDirection = vec3(totalRotation * glm::vec4(moveDirection, 1));

	//mult rot matrix * viewdir
	viewDirection = vec3(totalRotation * glm::vec4(viewDirection, 1));

	//update position
	position += moveDirection;

	moveDirection = vec3(0);

	
	
}

int i = 0; vec3 pos;
bool Xnegative, Xpositive, Ynegative, Ypositive, Znegative, Zpositive;
void Camera::render(){

	viewMatrix = mat4(1.0f);

	//vec3 pos;
	//pos.x = 0;
	//pos.y = 2;
	//pos.z = 1;
	if (i == 0) {
		pos.x = 0;
		pos.y = 4;
		pos.z = 2;
		i = 1;
	}

	//pos.x += 0.01;
	//pos.z -= 0.01;
	//pos.y -= 0.01;

	if (pos.x < 0.2) { Xpositive = true; Xnegative = false; }
	if (pos.x > 3) { Xpositive = false; Xnegative = true; }

	if (Xpositive) {
		pos.x += 0.01;
	}
	if (Xnegative) {
		pos.x -= 0.01;
	}

	if (pos.y < 0.2) { Ypositive = true; Ynegative = false; }
	if (pos.y > 3) { Ypositive = false; Ynegative = true; }

	if (Ypositive) {
		pos.y += 0.01;
	}
	if (Ynegative) {
		pos.y -= 0.01;
	}

	if (pos.z < 0.2) { Zpositive = true; Znegative = false; }
	if (pos.z > 3) { Zpositive = false; Znegative = true; }

	if (Zpositive) {
		pos.z += 0.01;
	}
	if (Znegative) {
		pos.z -= 0.01;
	}

	vec3 lookat;
	lookat.x = 0;
	lookat.y = 0;
	lookat.z = 0;

	//Set camera view
	//viewMatrix = glm::lookAt(position, viewDirection, vec3(0, 1, 0));
	viewMatrix = glm::lookAt(pos, lookat, vec3(0, 1, 0));

	position = pos;

	//send view matrix to shader
	glUniformMatrix4fv(viewUniformID, 1, GL_FALSE, &viewMatrix[0][0]);

	glUniform3fv(positionUniformID, 1, &position.x);

}


//void Camera::onKeyboardEvent(const SDL_KeyboardEvent& e) {
//
//	//GameObject Input
//	switch (e.keysym.sym) {
//
//	case SDLK_RIGHT:
//
//		moveDirection = glm::vec3(1, 0, 0);
//
//		break;
//
//	case SDLK_LEFT:
//
//		moveDirection = glm::vec3(-1, 0, 0);
//
//		break;
//
//	case SDLK_UP:
//
//		moveDirection = glm::vec3(0, 1, 0);
//
//		break;
//
//	case SDLK_DOWN:
//
//		moveDirection = glm::vec3(0, -1, 0);
//
//		break;
//
//	default:
//
//		moveDirection = vec3(0);
//
//		break;
//	}
//}

