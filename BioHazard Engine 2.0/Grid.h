#pragma once
#include <glew.h>
#include <glm.hpp>

#include <vector>
using std::vector;
using namespace glm;

class Grid{

private:

	vec3 position;
	vec3 color;

	vector<GLfloat> vertices;
	vector<GLfloat> colours;

	GLuint vertVBO;//local copys of IDs
	GLuint colVBO;
	GLuint ebo;
	GLuint vao;

	GLuint shaderID;

	GLuint isLitID;

	GLuint vertexAttributeID;
	GLuint colourAttributeID;
	GLuint mixColourID;
	GLuint mixValueID;

	GLuint modelUniformID;
	mat4 modelMatrix;

	

	GLuint projectionUniformID;


public:
	Grid();
	~Grid();

	void update();
	void render();
};

