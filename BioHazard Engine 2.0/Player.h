#pragma once
#include <glew.h>
#include <glm.hpp>

#include "EventHandler.h"
#include "ShaderManager.h"

#include <vector>
#include <string>
using std::vector;
using std::string;
using namespace glm;

class Player : public EventHandler{

private:

	uniformShaderType shaderType;

	vec3 position;
	vec3 color;

	vector<GLfloat> vertices;
	vector<GLfloat> colours;
	vector<GLuint> indices;
	vector<GLfloat> UVs;
	vector<GLfloat> UVs2;

	vector<GLfloat> gridVerts;
	vec3 gridpos;


	GLuint vertVBO;//local copys of IDs
	GLuint colVBO;
	GLuint ebo;
	GLuint vao;
	GLuint textureVBO;
	GLuint textureVBO2;

	GLuint shaderID;

	GLuint vertexAttributeID;
	GLuint colourAttributeID;
	GLuint textureAttributeID; //UVs for first texture
	GLuint textureAttributeID2; //UVs for second texture
	GLuint textureUniformID1;
	GLuint textureUniformID2;
	GLuint mixColourID;
	GLuint mixValueID;

	GLuint lightPositionUniformID;
	GLuint lightAmbientUniformID;
	GLuint lightDiffuseUniformID;
	GLuint lightSpecularUniformID;

	//Lighting
	GLuint isLitID;

	GLuint modelUniformID;
	mat4 modelMatrix;

	GLuint viewUniformID;
	mat4 viewMatrix;

	GLuint projectionUniformID;

	bool R_enabled = false;
	bool G_enabled = false;
	bool B_enabled = false;


	bool reverse = false;
	float i = 0;

public:
	Player();
	~Player();

	bool demoSelected = false;
	string demoChoice; //For demo purposes

	void update();
	void render();

	void onKeyboardEvent(const SDL_KeyboardEvent& e);
};

