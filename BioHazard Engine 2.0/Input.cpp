#include "Input.h"
#include"EventHandler.h"
#include <SDL.h>
#include <iostream>
//#include "Game.h"


void Input::registerGameObject(EventHandler* eh){

	map<unsigned int, EventHandler*>::iterator it = m_eventMap.find(reinterpret_cast <unsigned int> (eh));

	if (it == m_eventMap.end()){

		m_eventMap[reinterpret_cast <unsigned int> (eh)] = eh;
	}
}


void Input::unregisterGameObject(EventHandler* eh){

	map<unsigned int, EventHandler*>::iterator it = m_eventMap.find(reinterpret_cast <unsigned int> (eh));

	if (it != m_eventMap.end()){

		m_eventMap.erase(reinterpret_cast <unsigned int> (eh));
	}
}


void Input::update(){

	SDL_Event event;

	while (SDL_PollEvent(&event)){ // Polls for input

		switch (event.type){

		//case SDL_KEYUP:

		//	for (map<unsigned int, EventHandler*> ::iterator it = m_eventMap.begin(); it != m_eventMap.end(); ++it){

		//		it->second->onKeyboardEvent(event.key);
		//	}

		//	break;


		case SDL_KEYDOWN:

			for (map<unsigned int, EventHandler*> ::iterator it = m_eventMap.begin(); it != m_eventMap.end(); ++it){

				it->second->onKeyboardEvent(event.key);
			}

			break;


		//case SDL_MOUSEMOTION:

		//	for (map<unsigned int, EventHandler*> ::iterator it = m_eventMap.begin(); it != m_eventMap.end(); ++it){

		//		it->second->onMouseMotionEvent(event.motion);
		//	}

		//	break;


		//case SDL_MOUSEBUTTONUP:

		//	for (map <unsigned int, EventHandler*> ::iterator it = m_eventMap.begin(); it != m_eventMap.end(); ++it){

		//		it->second->onMouseButtonEvent(event.button);
		//	}

		//	break;


		//case SDL_MOUSEBUTTONDOWN:

		//	for (map <unsigned int, EventHandler*> ::iterator it = m_eventMap.begin(); it != m_eventMap.end(); ++it){

		//		it->second->onMouseButtonEvent(event.button);
		//	}

		//	break;


		case SDL_QUIT:

			SDL_Quit();
			//TheGame::Instance()->setIsRunning(false);
			break;


		default:

			break;
		}
	}
}


void Input::addHandler(EventHandler* handler){

	map<unsigned int, EventHandler*> ::iterator it = m_eventMap.find(reinterpret_cast<unsigned int> (handler));

	if (it == m_eventMap.end()){

		m_eventMap[reinterpret_cast<unsigned int> (handler)] = handler;
	}
}


void Input::removeHandler(EventHandler* handler){

	map<unsigned int, EventHandler*> ::iterator it = m_eventMap.find(reinterpret_cast<unsigned int> (handler));

	if (it != m_eventMap.end()){

		m_eventMap.erase(it);
	}
}

