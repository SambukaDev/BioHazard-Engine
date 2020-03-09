#pragma once
#include<SDL.h>

class EventHandler{

public:

	virtual void onKeyboardEvent(const SDL_KeyboardEvent&) {};
	virtual void onMouseMotionEvent(const SDL_MouseMotionEvent&) {};
	virtual void onMouseButtonEvent(const SDL_MouseButtonEvent&) {};
	virtual void onQuit();
	virtual void activate();
	virtual void deactivate();
	virtual ~EventHandler() = 0 {};
};

