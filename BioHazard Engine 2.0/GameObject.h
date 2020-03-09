#pragma once
#include <glew.h>

#include <vector>
using std::vector;

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
using glm::vec3;
using glm::mat4;
using glm::mat3;

class GameObject{

protected:

	vector<GLfloat> vertices;
	vector<GLfloat> normals;
	vector<GLfloat> UVs;
	vector<GLfloat> UVs2;
	vector<GLfloat> colours;
	vector<GLuint> indices;

	GLuint vao;
	GLuint ebo;

	GLuint vertVBO;
	GLuint normalVBO;
	GLuint colVBO;
	GLuint textureVBO;
	GLuint textureVBO2;

	GLuint vertexAttributeID;
	GLuint normalAttributeID;
	GLuint textureAttributeID;
	GLuint textureAttributeID2;
	GLuint colourAttributeID;
	GLuint modelUniformID;
	GLuint normalMatrixUniformID;

	mat4 modelMatrix;
	mat3 normalMatrix;

	GLuint isLitID;
	GLuint materialPositionUniformID;
	GLuint materialAmbientUniformID;
	GLuint materialDiffuseUniformID;
	GLuint materialSpecularUniformID;
	GLuint materialShininessUniformID;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	GLfloat m_shininess;

	vec3 position;

public:
	GameObject() {};
	~GameObject() {};

	virtual void update() {};
	virtual void render() {};
};

