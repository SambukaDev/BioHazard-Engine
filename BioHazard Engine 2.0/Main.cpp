#include <iostream>
//#include <SDL.h>
//#include <glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include "ScreenManager.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include "TimeManager.h"
#include "Input.h"
#include <vector>

#include "Floor.h"
#include "Grid.h"
#include "Camera.h"
#include "POVCamera.h"
#include "Light.h"
#include "Scene.h"


using namespace glm;
using namespace std;


SDL_Event events;
const uint8* keystates;


int main(int argc, char* args[]) {

	TheScreen::Instance()->init(); 

	TheShader::Instance()->createShaderProgram();
	TheShader::Instance()->createShaders();
	TheShader::Instance()->compileShaders("Shaders/Main.vert", TheShader::Instance()->vertexShaderID);
	TheShader::Instance()->compileShaders("Shaders/Main.frag", TheShader::Instance()->fragmentShaderID);
	TheShader::Instance()->attachShaders();
	TheShader::Instance()->linkProgram();



	Scene scene;
	Floor water;
	POVCamera povCam;
	Grid grid;
	Light spot1(0);
	Light spot2(1);
	Light spot3(2);
	Light spot4(3);
	Light point1(4);
	Light point2(5);
	vector<Light*> lights;

	GLuint nl = TheShader::Instance()->getUniform("numLights");
	glUniform1i(nl, 6);

	lights.push_back(&spot1);
	lights.push_back(&spot2);
	lights.push_back(&spot3);
	lights.push_back(&spot4);
	lights.push_back(&point1);
	lights.push_back(&point2);


	spot1.setPosition(vec3(-2, 3, -2));
	spot1.setDirection(vec3(0, -1, 0));
	spot1.setAmbient(vec3(0.5, 0.5, 0.5));
	spot1.setDiffuse(vec3(0.25, 0.25, 0.25));
	spot1.setSpecular(vec3(0.25, 0.25, 0.25));
	spot1.setAngle(20);
	spot1.colourChangable = true;

	spot2.setPosition(vec3(2, 3, -2));
	spot2.setDirection(vec3(0, -1, 0));
	spot2.setAmbient(vec3(0.5, 0.5, 0.5));
	spot2.setDiffuse(vec3(0.5, 0.5, 0.5));
	spot2.setSpecular(vec3(0.5, 0.5, 0.5));
	spot2.setAngle(20);
	spot2.colourChangable = true;

	spot3.setPosition(vec3(-2, 3, 2));
	spot3.setDirection(vec3(0, -1, 0));
	spot3.setAmbient(vec3(0.5, 0.5, 0.5));
	spot3.setDiffuse(vec3(0.25, 0.25, 0.25));
	spot3.setSpecular(vec3(0.25, 0.25, 0.25));
	spot3.setAngle(20);
	spot3.colourChangable = true;

	spot4.setPosition(vec3(2, 3, 2));
	spot4.setDirection(vec3(0, -1, 0));
	spot4.setAmbient(vec3(0.5, 0.5, 0.5));
	spot4.setDiffuse(vec3(0.25, 0.25, 0.25));
	spot4.setSpecular(vec3(0.25, 0.25, 0.25));
	spot4.setAngle(20);
	spot4.colourChangable = true;


	point1.setPosition(vec3(0, 4, 0));
	point1.setDirection(vec3(0, -1, 0));
	point1.setAmbient(vec3(0.1, 0.1, 0.1));
	point1.setDiffuse(vec3(0.5, 0.5, 0.5));
	point1.setSpecular(vec3(0.5, 0.5, 0.5));
	point1.setAngle(180);

	point2.setPosition(vec3(-12, 4, 0));
	point2.setDirection(vec3(0, -1, 0));
	point2.setAmbient(vec3(0.5, 0.5, 0.5));
	point2.setDiffuse(vec3(0.5, 0.5, 0.5));
	point2.setSpecular(vec3(0.5, 0.5, 0.5));
	point2.setAngle(45);
	point2.isControlable = true;
	point2.isAnimate = false;

	//Set camera properties
	povCam.setVelocity(4);
	povCam.setViewUniformID("view");


	bool isRunning = true;
	const GLint FPS = 60; //Games framerate
	const GLint DELAYTIME = int(1000.0f / FPS);
	GLfloat frameTime;

	TheTimeManager::Instance()->start(); // Start the Timer for the program

	TheScreen::Instance()->setProjection();

	while (isRunning) {


		TheTimeManager::Instance()->update(); //Updates the timer
		frameTime = TheTimeManager::Instance()->GetElapsedTimeMilliseconds(); //Gets the time since the last frame

		//glClear(GL_COLOR_BUFFER_BIT);
		TheScreen::Instance()->clearScreen();


		keystates = SDL_GetKeyboardState(0);
		if (keystates[SDL_SCANCODE_ESCAPE]) { break; }
		
		if (keystates[SDL_SCANCODE_A]) { povCam.moveLeft(); }

		if (keystates[SDL_SCANCODE_D]) { povCam.moveRight(); }

		if (keystates[SDL_SCANCODE_Q]) { povCam.moveUp(); }

		if (keystates[SDL_SCANCODE_E]) { povCam.moveDown(); }

		if (keystates[SDL_SCANCODE_W]) { povCam.moveForward(); }

		if (keystates[SDL_SCANCODE_S]) { povCam.moveBackward(); }

		else { povCam.stop(); }

		TheInput::Instance()->update();


		// Update all lights
		for (int i = 0; i < lights.size(); i++){

			lights[i]->update();
			lights[i]->animate(3.1, 10); //Moves the spotlights between the two points
		}


		povCam.update();
		scene.update();
		water.update();
		grid.update();

		//Render all lights
		for (int i = 0; i < lights.size(); i++) {

			lights[i]->render();
		}


		povCam.render();
		scene.render();
		water.render();
		grid.render();


		TheScreen::Instance()->swapBuffer();


		//TheTimeManager::Instance()->output();
		if (frameTime < DELAYTIME) { //FPS

			SDL_Delay((GLint)(DELAYTIME - frameTime));
		}
	}


	TheShader::Instance()->detatchShaders();
	TheShader::Instance()->destroyShaderProgram();


	TheScreen::Instance()->shutdown();

	return 0;
}