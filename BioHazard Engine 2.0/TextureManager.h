#pragma once
#include "Singleton.h"
#include <glew.h>
#include <string>
#include <map>
using std::string;
using std::map;

class TextureManager : public Uncopyable{

private:

	friend Singleton < TextureManager >;

	GLuint textureID;


public:
	TextureManager();
	~TextureManager();

	bool loadFromFile(const string& filename, const string& mapIndex);
	void unloadFromMemory();

	map<string, GLuint> textureIDMap;
};

typedef Singleton<TextureManager> TheTexture;