#pragma once
#include "ShaderManager.h"
#include "GameObject.h"

#include <string>

#include <vector>
using std::vector;

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
using glm::vec3;
using glm::mat4;
using glm::uint8;


class Light : public GameObject{

private:

	uniformShaderType shaderType;

	const uint8* keystates;

	std::string lightID;

	//GLuint isLitID;
	GLuint lightPositionUniformID;
	GLuint lightAmbientUniformID;
	GLuint lightDiffuseUniformID;
	GLuint lightSpecularUniformID;
	GLuint lightDirectionID;
	GLuint lightAngleID;

	//spot
	vec3 coneDirection;
	GLfloat coneAngle;

	bool isRed, isGreen, isBlue;

public:
	Light(GLint id);
	~Light();

	bool colourChangable = false;
	bool isControlable = false;
	bool isAnimate = true;

	void setLightID(GLint id);

	void setAmbient(vec3 amb);
	void setDiffuse(vec3 diff);
	void setSpecular(vec3 spec);
	void setPosition(vec3 pos);
	void setDirection(vec3 dir);
	void setAngle(GLfloat ang);

	void animate(GLfloat start, GLfloat finish);

	void update();
	void render();
};

