#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>
using std::cout;
using std::endl;


TextureManager::TextureManager(){


}


TextureManager::~TextureManager()
{
}


bool TextureManager::loadFromFile(const string& filename, const string& mapIndex){

	//Generate a texture ID
	glGenTextures(1, &textureID);

		//Bind texture ready for use
		glBindTexture(GL_TEXTURE_2D, textureID);

		//Load image into memory
		SDL_Surface* image = 0;
		image = IMG_Load(filename.c_str());

		if (!image) {

			cout << "TextureManager | Error loading image " << filename << endl;
		}

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		//Makes a copy of all the RAW data
		unsigned char* pixels = (unsigned char*)image->pixels;
		unsigned int width = image->w;
		unsigned int height = image->h;
		unsigned int depth = image->format->BytesPerPixel;
		unsigned int format = ((depth == 4) ? GL_RGBA : GL_RGB);


		//Bind the RAW data with OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

		//Gen mipmaps for LOD
		glGenerateMipmap(GL_TEXTURE_2D);

		//Free SDL image
		SDL_FreeSurface(image);


	glBindTexture(GL_TEXTURE_2D, 0);

	
	//Add the ID to the map
	textureIDMap[mapIndex] = textureID;

	return false;
}


void TextureManager::unloadFromMemory(){

	//Deletes all the textures from memory
	for (auto it = textureIDMap.begin(); it != textureIDMap.end(); it++){

		glDeleteTextures(1, &it->second);
	}
}

