#include "Light.h"
#include "BufferManager.h"
#include <SDL.h>


Light::Light(GLint id){

	setLightID(id);

	isLitID = TheShader::Instance()->getUniform("isLit");
	//shaderType = uniform1i;
	//setShaderVariable(isLitID, shaderType, 0, 0, 0, 0); //Set the shader to disable light for this Game Object

	vertexAttributeID = TheShader::Instance()->getAttribute("position");
	colourAttributeID = TheShader::Instance()->getAttribute("colourIn");

	modelUniformID = TheShader::Instance()->getUniform("model");

	//modelMatrix = glm::scale(modelMatrix, vec3(2, 2, 2));

	//Generate IDs
	TheBuffer::Instance()->generateArray(&vao);
	TheBuffer::Instance()->generateBuffer(&vertVBO);
	TheBuffer::Instance()->generateBuffer(&colVBO);

	//Set initial position to 0, 1, 0
	//position.y = 1;

	colours.push_back(1.0f);
	colours.push_back(1.0f);
	colours.push_back(1.0f);

	ambient.r = 0;
	ambient.g = 0;
	ambient.b = 0;

	diffuse.r = 0;
	diffuse.g = 0;
	diffuse.b = 0;

	specular.r = 0;
	specular.g = 0;
	specular.b = 0;

	coneDirection.x = 0;
	coneDirection.y = 0;
	coneDirection.z = 0;

	position.x = 0;
	position.y = 0;
	position.z = 0;

	coneAngle = 180;


	//Point
	lightPositionUniformID = TheShader::Instance()->getUniform(lightID + ".position");
	lightAmbientUniformID = TheShader::Instance()->getUniform(lightID + ".ambient");
	lightDiffuseUniformID = TheShader::Instance()->getUniform(lightID + ".diffuse");
	lightSpecularUniformID = TheShader::Instance()->getUniform(lightID + ".specular");
	lightDirectionID = TheShader::Instance()->getUniform(lightID + ".coneDirection");
	lightAngleID = TheShader::Instance()->getUniform(lightID + ".coneAngle");


	////Directional
	//dirLightDirectionUniformID = TheShader::Instance()->getUniform("dirLight.direction");
	//dirLightAmbientUniformID = TheShader::Instance()->getUniform("dirLight.ambient");
	//dirLightDiffuseUniformID = TheShader::Instance()->getUniform("dirLight.diffuse");
	//dirLightSpecularUniformID = TheShader::Instance()->getUniform("dirLight.specular");

	isRed = true;
	isGreen = true;
	isBlue = true;
}


Light::~Light()
{
}


void Light::update(){

	//read keys for position
	keystates = SDL_GetKeyboardState(0);

	if (isControlable) {
		//Move light back
		if (keystates[SDL_SCANCODE_I]) {

			position.z -= 0.025;
		}
		//Move light forward
		if (keystates[SDL_SCANCODE_K]) {

			position.z += 0.025;
		}
		//Move light left
		if (keystates[SDL_SCANCODE_J]) {

			position.x -= 0.025;
		}
		//Move light right
		if (keystates[SDL_SCANCODE_L]) {

			position.x += 0.025;
		}
		////Move light down
		//if (keystates[SDL_SCANCODE_Q]) {

		//	position.y += 0.025;
		//}
		////Move light up
		//if (keystates[SDL_SCANCODE_E]) {

		//	position.y -= 0.025;
		//}
	}

	if (colourChangable) {
		//Change light colour
		if (keystates[SDL_SCANCODE_R]) {

			if (isRed) {
				ambient.r = 1;
				isRed = false;
				SDL_Delay(10);
			}
			else {
				ambient.r = 0;
				isRed = true;
				SDL_Delay(10);
			}
		}
		if (keystates[SDL_SCANCODE_G]) {

			//ambient = vec3(0.1, 0.8, 0.1);

			//if (isGreen) isGreen = false;
			//else isGreen = true;
			//if (!isGreen) ambient.g = 0.1;
			//if (isGreen) ambient.g = 0.8;

			if (isGreen) {
				ambient.g = 1;
				isGreen = false;
				SDL_Delay(10);
			}
			else {
				ambient.g = 0;
				isGreen = true;
				SDL_Delay(10);
			}
		}
		if (keystates[SDL_SCANCODE_B]) {

			//ambient = vec3(0.1, 0.1, 0.8);

			//if (isBlue) isBlue = false;
			//else isBlue = true;
			//if (!isBlue) ambient.b = 0.1;
			//if (isBlue) ambient.b = 0.8;

			if (isBlue) {
				ambient.b = 1;
				isBlue = false;
				SDL_Delay(10);
			}
			else {
				ambient.b = 0;
				isBlue = true;
				SDL_Delay(10);
			}
		}
	}

	//Apply changes to position
	vertices.clear();
	vertices.push_back(position.x);
	vertices.push_back(position.y);
	vertices.push_back(position.z);

	//modelMatrix = translate(modelMatrix, position);



	glUniform3fv(lightPositionUniformID, 1, &position.x);
	glUniform3fv(lightAmbientUniformID, 1, &ambient.r);
	glUniform3fv(lightDiffuseUniformID, 1, &diffuse.r);
	glUniform3fv(lightSpecularUniformID, 1, &specular.r);
	glUniform3fv(lightDirectionID, 1, &coneDirection.x);
	glUniform1f(lightAngleID, coneAngle);


	//glUniform3fv(spotLightPositionUniformID, 1, &position.x);
	//glUniform3fv(spotLightIntensityID, 1, &spotIntensity.x);
	//glUniform3fv(spotLightDirectionID, 1, &direction.x);
	//glUniform1f(spotLightExponentUniformID, exponent);
	//glUniform1f(spotLightCutoffUniformID, cutoff);


	////Directinal
	//glUniform3fv(dirLightDirectionUniformID, 1, &direction.x);
	//glUniform3fv(dirLightAmbientUniformID, 1, &ambient.r);
	//glUniform3fv(dirLightDiffuseUniformID, 1, &diffuse.r);
	//glUniform3fv(dirLightSpecularUniformID, 1, &specular.r);


	//Bind the vao for use
	glBindVertexArray(vao);

		//Vertex Data
		TheBuffer::Instance()->fillBuffer(vertVBO, &vertices[0], vertices.size(), true);
		TheBuffer::Instance()->linkBuffer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Colour Data
		TheBuffer::Instance()->fillBuffer(colVBO, &colours[0], colours.size(), true);
		TheBuffer::Instance()->linkBuffer(colourAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Unbind the vao
	glBindVertexArray(0);


	//setShaderVariable(isLitID, shaderType, 1, 0, 0, 0); //Set the shader to disable light for this Game Object
}


void Light::render(){

	glUniform1i(isLitID, 0); //Set the obj to not be lit

	glPointSize(20.0f);

	//Send model matrix to shader
	glUniformMatrix4fv(modelUniformID, 1, GL_FALSE, &modelMatrix[0][0]);


	//Bind the vao
	glBindVertexArray(vao);

		glDrawArrays(GL_POINT, 0, 1); //Draw
		//glDrawArrays(GL_LINES, 0, 4);

	glBindVertexArray(0); //Unbind the vao


	//glUniform1i(isLitID, 1); //Sets future obj to be lit (avoids writing this in every obj)
}


void Light::setLightID(GLint id){

	char buffer[10];
	itoa(id, buffer, 10);
	string temp = buffer;
	lightID = "lights[" + temp + "]";
}


void Light::setAmbient(vec3 amb){

	ambient = amb;
}


void Light::setDiffuse(vec3 diff){

	diffuse = diff;
}


void Light::setSpecular(vec3 spec){

	specular = spec;
}


void Light::setPosition(vec3 pos){

	position = pos;
}


void Light::setDirection(vec3 dir){

	coneDirection = dir;
}


void Light::setAngle(GLfloat ang){

	coneAngle = ang;
}


bool moveUp, moveDown;
void Light::animate(GLfloat start, GLfloat finish){

	if (isAnimate) {
		GLfloat speed = 0.05;

		if (position.y > finish) { moveDown = true; moveUp = false; }
		else if (position.y < start) { moveDown = false; moveUp = true; }

		if (moveUp) {
			position.y += speed;
		}
		if (moveDown) {
			position.y -= speed;
		}
	}
}

