#pragma once
#include "Singleton.h"
#include < map >
#include "EventHandler.h"


using namespace std;


class Input : public Uncopyable{

private:

	Input() {}

	friend Singleton < Input >;



	bool tempIsRunning;

public:

	map<unsigned int, EventHandler*> m_eventMap;

	void update();
	void registerGameObject(EventHandler* eh);
	void unregisterGameObject(EventHandler* eh);
	void addHandler(EventHandler* handler);
	void removeHandler(EventHandler* handler);

};

typedef Singleton<Input> TheInput;