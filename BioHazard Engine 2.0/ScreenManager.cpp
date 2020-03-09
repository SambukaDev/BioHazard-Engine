#include "ScreenManager.h"
#include <iostream>
#include <vector>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include "ShaderManager.h"

using std::cout;
using std::endl;
using std::vector;
using namespace glm;


ScreenManager::ScreenManager()
{
}


ScreenManager::~ScreenManager()
{
}

bool ScreenManager::init(){

	//Initalise SDL Video & Events Modules
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1) { cout << "SCRREN-MANAGER: Error initalising SDL" << endl; system("pause"); return false; };


	//Sets the colour res to 32 bit
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Set GL context to target the core API levels
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Set GL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);



	//Creates the window
	window = SDL_CreateWindow("BioHazard Engine 2.0", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL); // | SDL_WINDOW_BORDERLESS);

	if (window == nullptr) { cout << "SCRREN-MANAGER: Error Creating Window" << endl; system("pause"); return false; }

	//Passes the window handler to OpenGL
	context = SDL_GL_CreateContext(window);

	if (context == 0) { cout << "SCRREN-MANAGER: Error assigning Window to Context" << endl; system("pause"); return false; }



	if (glewInit() != GLEW_OK) {
		
		cout << "SCRREN-MANAGER: Error with glew initalisation" << endl;
		return false;
	}

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	projectionMatrix = mat4(1.0f);


	return true;
}


void ScreenManager::set2DProjection(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top){

	//projectionMatrix = ortho(0.0f, 1024.0f, 0.0f, 768.0f);

	//Sets orthographic projection
	projectionMatrix = ortho(left, right, bottom, top);
}


void ScreenManager::set3DProjection(GLfloat FOV, GLfloat aspect, GLfloat near, GLfloat far){

	//projectionMatrix = perspective(radians(60.0f), 1024.0f / 768.0f, 0.1f, 1000.0f);

	//Sets perspective projection
	projectionMatrix = perspective(radians(FOV), aspect, near, far);
}


void ScreenManager::setViewPort(GLint x, GLint y, GLsizei width, GLsizei height){

	glViewport(x, y, width, height);
}


void ScreenManager::setProjection(){

	GLuint projectionUniformID = TheShader::Instance()->getUniform("projection");
	glUniformMatrix4fv(projectionUniformID, 1, GL_FALSE, &TheScreen::Instance()->projectionMatrix[0][0]);
}


void ScreenManager::profile(){
	cout << "\n================================================" << endl;

	//Gets the Hardware details and the API versions then prints them to the console
	cout << "Hardware Vendor: " << (const char*)(glGetString(GL_VENDOR)) << endl;
	cout << "Hardware Model: " << (const char*)(glGetString(GL_RENDERER)) << endl;
	cout << "OpenGL Version: " << (const char*)(glGetString(GL_VERSION)) << endl;
	cout << "GLSL Shader Version: " << (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION)) << endl;

	cout << "================================================\n" << endl;
}


bool ScreenManager::extensions(const string ext){

	GLint totalExtentions; //Stores the total num of extensions the GPU supports

	std::vector<std::string> extensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtentions); //Stores the total num of extensions the GPU supports in totalextensions

	for (GLint i = 0; i < totalExtentions; i++){

		std::string tempString = (const char*)glGetStringi(GL_EXTENSIONS, i); //Loops through each extension and stores the name in the extensions vector
		extensions.push_back(tempString);
	}


	//If extension to search for is not specified then just print the list to the console
	if (ext == "") {
		for (int i = 0; i < extensions.size(); i++) {

			cout << "Extension #" << i << ":" << extensions[i] << endl; //Loops through all the stored extensions and prints the name to the console
		}
	}
	else { //Else search for that extension. Returns true if found

		for (int i = 0; i < extensions.size(); i++) {

			if (ext == extensions[i]) {

				return true;
			}
		}
	}

	return false;
}


const GLfloat ScreenManager::getWidth(){

	return SCREEN_WIDTH; //returns the screen width
}


const GLfloat ScreenManager::getHeight(){

	return SCREEN_HEIGHT; //returns the screen height
}


GLfloat ScreenManager::getAspectRatio(){

	return (SCREEN_WIDTH / SCREEN_HEIGHT); //Rerturns the screens aspect ratio
}


void ScreenManager::clearScreen(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the screen buffer
}


void ScreenManager::swapBuffer(){

	SDL_GL_SwapWindow(window); //Swaps the screens buffers
}


void ScreenManager::shutdown(){

	//Destroy the context
	SDL_GL_DeleteContext(context);

	//Destroy the window
	SDL_DestroyWindow(window);

	//Uninitilise SDL
	SDL_Quit();
}

