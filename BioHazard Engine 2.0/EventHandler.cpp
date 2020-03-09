#include "EventHandler.h"
#include "Input.h"

void EventHandler::activate(){

	TheInput::Instance()->registerGameObject(this);
}


void EventHandler::deactivate(){

	TheInput::Instance()->unregisterGameObject(this);
}


void EventHandler::onQuit(){

	SDL_Quit();
}

