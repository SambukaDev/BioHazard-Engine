#pragma once
#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <string>
using std::string;
using glm::mat4;

#include "Singleton.h"

class ScreenManager : public Uncopyable{

private:

	friend Singleton < ScreenManager >;

	SDL_Window* window = nullptr;
	SDL_GLContext context = 0;

	const GLfloat SCREEN_WIDTH = 800;
	const GLfloat SCREEN_HEIGHT = 600;


public:
	ScreenManager();
	~ScreenManager();

	bool init();

	mat4 projectionMatrix;

	void set2DProjection(GLfloat FOV, GLfloat aspect, GLfloat near, GLfloat far);
	void set3DProjection(GLfloat FOV, GLfloat aspect, GLfloat near, GLfloat far);
	void setViewPort(GLint x, GLint y, GLsizei width, GLsizei height);
	void setProjection();
	
	void profile();
	bool extensions(const string ext = "");
	const GLfloat getWidth();
	const GLfloat getHeight();
	GLfloat getAspectRatio();

	void clearScreen();
	void swapBuffer();

	void shutdown();
};
typedef Singleton<ScreenManager> TheScreen;
