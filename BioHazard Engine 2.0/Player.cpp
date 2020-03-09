#include "Player.h"
#include "BufferManager.h"
#include "ShaderManager.h"
#include "Input.h"
#include "TextureManager.h"
#include "ScreenManager.h"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <iostream>
using namespace std;

Player::Player(){

	vertices.reserve(72);//allocate memory
	colours.reserve(24);
	indices.reserve(36);
	UVs.reserve(24);
	UVs2.reserve(24);
	//gridVerts.reserve();


	//fill with clour data
	//colours.push_back(1.0f); //Colourful
	//colours.push_back(0.0f);
	//colours.push_back(0.0f);

	//colours.push_back(0.0f);
	//colours.push_back(0.0f);
	//colours.push_back(1.0f);
	//
	//colours.push_back(0.0f);
	//colours.push_back(1.0f);
	//colours.push_back(0.0f);
	//
	//colours.push_back(0.0f);
	//colours.push_back(1.0f);
	//colours.push_back(1.0f);

	//=======================

	////fill with clour data
	//colours.push_back(1.0f); //No colour mix
	//colours.push_back(1.0f);
	//colours.push_back(1.0f);

	//colours.push_back(1.0f);
	//colours.push_back(1.0f);
	//colours.push_back(1.0f);

	//colours.push_back(1.0f);
	//colours.push_back(1.0f);
	//colours.push_back(1.0f);

	//colours.push_back(1.0f);
	//colours.push_back(1.0f);
	//colours.push_back(1.0f);

	for (int i = 0; i < 6; i++) {

		//fill with clour data
		colours.push_back(1.0f); //No colour mix
		colours.push_back(1.0f);
		colours.push_back(1.0f);

		colours.push_back(1.0f);
		colours.push_back(1.0f);
		colours.push_back(1.0f);

		colours.push_back(1.0f);
		colours.push_back(1.0f);
		colours.push_back(1.0f);

		colours.push_back(1.0f);
		colours.push_back(1.0f);
		colours.push_back(1.0f);
	}


	////fill with indices data
	//indices.push_back(0);//Front
	//indices.push_back(1);
	//indices.push_back(3);
	//indices.push_back(1);
	//indices.push_back(2);
	//indices.push_back(3);


	for (int i = 0; i < 6; i++) {

		//fill with indices data
		indices.push_back(0 + 4 * i);
		indices.push_back(1 + 4 * i);
		indices.push_back(3 + 4 * i);
		indices.push_back(1 + 4 * i);
		indices.push_back(2 + 4 * i);
		indices.push_back(3 + 4 * i);
	}


	for (int i = 0; i < 6; i++){

		//fill with UV texture data
		UVs.push_back(0.0f);//X
		UVs.push_back(0.0f);//Y

		UVs.push_back(1.0f);//X
		UVs.push_back(0.0f);//Y

		UVs.push_back(1.0f);//X
		UVs.push_back(1.0f);//Y

		UVs.push_back(0.0f);//X
		UVs.push_back(1.0f);//Y
	}

	for (int i = 0; i < 6; i++) {

		//Second UVs
		UVs2.push_back(0.0f);//X
		UVs2.push_back(0.0f);//Y

		UVs2.push_back(1.0f);//X
		UVs2.push_back(0.0f);//Y

		UVs2.push_back(1.0f);//X
		UVs2.push_back(1.0f);//Y

		UVs2.push_back(0.0f);//X
		UVs2.push_back(1.0f);//Y
	}

	gridpos = vec3(0.0f, 0.0f, 0.0f);
	gridVerts.push_back(gridpos.x);
	gridVerts.push_back(gridpos.y);

	gridVerts.push_back(gridpos.x + 1);
	gridVerts.push_back(gridpos.y + 1);

	//Initalise the buffer manager (generates the buffers)
	//TheBuffer::Instance()->init();

	TheBuffer::Instance()->generateBuffer(&textureVBO);
	TheBuffer::Instance()->generateBuffer(&textureVBO2); //Second UVs


	shaderID = TheShader::Instance()->shaderProgramID;

	//Get attribute location from the GPU shader
	//vertexAttributeID = glGetAttribLocation(shaderID, "position");
	//colourAttributeID = glGetAttribLocation(shaderID, "colourIn");

	vertexAttributeID = TheShader::Instance()->getAttribute("position");
	colourAttributeID = TheShader::Instance()->getAttribute("colourIn");


	//Gets the IDs from the Buffer manager
	vertVBO = TheBuffer::Instance()->vertexVBO;
	colVBO = TheBuffer::Instance()->colourVBO;
	ebo = TheBuffer::Instance()->EBO;
	vao = TheBuffer::Instance()->VAO;


	//Gets uniform IDs from the GPU shader
	//mixColourID = glGetUniformLocation(shaderID, "mixColour"); //Colour
	//mixValueID = glGetUniformLocation(shaderID, "mixValue"); //Interpolation value


	lightPositionUniformID = TheShader::Instance()->getUniform("light.position");
	lightAmbientUniformID = TheShader::Instance()->getUniform("light.ambient");
	lightDiffuseUniformID = TheShader::Instance()->getUniform("light.diffuse");
	lightSpecularUniformID = TheShader::Instance()->getUniform("light.specular");

	//glUniform3fv(lightPositionUniformID, 1, &position.x);
	//glUniform3fv(lightAmbientUniformID, 1, &ambient.r);
	//glUniform3fv(lightDiffuseUniformID, 1, &diffuse.r);
	//glUniform3fv(lightSpecularUniformID, 1, &specular.r);



	mixColourID = TheShader::Instance()->getUniform("mixColour");
	mixValueID = TheShader::Instance()->getUniform("mixValue");


	//textureAttributeID = glGetAttribLocation(shaderID, "textureIn"); //UVs for first texture
	//textureAttributeID2 = glGetAttribLocation(shaderID, "textureIn2"); //UVs for second texture

	textureAttributeID = TheShader::Instance()->getAttribute("textureIn");
	textureAttributeID2 = TheShader::Instance()->getAttribute("textureIn2");

	//textureUniformID1 = glGetUniformLocation(shaderID, "textureImage"); //Texture 1
	//textureUniformID2 = glGetUniformLocation(shaderID, "otherTexture"); //Texture 2

	textureUniformID1 = TheShader::Instance()->getUniform("textureImage");
	textureUniformID2 = TheShader::Instance()->getUniform("otherTexture");

	//modelUniformID = glGetUniformLocation(shaderID, "model"); //Model Matrix
	//viewUniformID = glGetUniformLocation(shaderID, "view"); //View Matrix
	//projectionUniformID = glGetUniformLocation(shaderID, "projection"); //Projection Matrix

	modelUniformID = TheShader::Instance()->getUniform("model");
	viewUniformID = TheShader::Instance()->getUniform("view");
	projectionUniformID = TheShader::Instance()->getUniform("projection");

	//For demo purposes
	/*demoChoice = "";
	while (!demoSelected) {

		cout << "Type 'FILM' for the film demo" << endl;
		cout << "Type 'WATER' for the water demo" << endl;
		cout << "Choice: ";
		cin >> demoChoice;
		cout << "\n\n";

		if (demoChoice == "FILM") {

			cout << "FILM selected" << endl;
			demoSelected = true;
		}
		else if (demoChoice == "WATER") {

			cout << "WATER selected" << endl;
			demoSelected = true;
		}
		else {

			cout << "INVALID INPUT...\n\n" << endl;
		}
	}*/

	////TheTexture::Instance()->loadFromFile("Textures/Crate.jpg", "CRATE");
	//if (demoChoice == "WATER") TheTexture::Instance()->loadFromFile("Textures/Water.jpg", "WATER");
	//if (demoChoice == "FILM") TheTexture::Instance()->loadFromFile("Textures/Film.png", "FILM");

	isLitID = TheShader::Instance()->getUniform("isLit");

	//Registers this GO for input
	TheInput::Instance()->registerGameObject(this);
}


Player::~Player(){

	TheTexture::Instance()->unloadFromMemory();

	//Unregisters this GO upon deletion
	TheInput::Instance()->unregisterGameObject(this);
}


void Player::update(){

	//Set model matrix to identity
	modelMatrix = mat4(1.0f);
	viewMatrix = mat4(1.0f); //TO BE CONTAINED IN CAMERA ONCE IMPLEMENTED


	//Set Projection
	//ortho(0.0f, 1024.0f, 0.0f, 768.0f);
	TheScreen::Instance()->projectionMatrix = perspective(radians(60.0f), 1024.0f / 768.0f, 0.1f, 1000.0f);

	//Apply translation
	//modelMatrix = translate(modelMatrix, vec3(0.25, 0.5, 0.0));

	//modelMatrix = glm::rotate(modelMatrix, radians(90.0f), vec3(0, 1, 0));

	//Set camera view
	viewMatrix = lookAt(vec3(0, 0, 2), vec3(0, 0, -1), vec3(0, 1, 0));




	vertices.clear(); //Clear the old data

	//front top left
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z + 0.5);

	//front top right
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z + 0.5);

	//front bottom right
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z + 0.5);

	//front bottom left
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z + 0.5);

	//===================================

	//back top left
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z - 0.5);

	//back top right
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z - 0.5);

	//back bottom right
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z - 0.5);

	//back bottom left
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z - 0.5);

	//===================================

	//left top left
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z - 0.5);

	//left top right
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z + 0.5);

	//left bottom right
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z + 0.5);

	//left bottom left
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z - 0.5);

	//===================================

	//right top left
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z + 0.5);

	//right top right
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z - 0.5);

	//right bottom right
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z - 0.5);

	//right bottom left
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z + 0.5);

	//===================================

	//top top left
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z - 0.5);

	//top top right
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z - 0.5);

	//top bottom right
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z + 0.5);

	//top bottom left
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z + 0.5);

	//===================================

	//bottom top left
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z + 0.5);

	//bottom top right
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z + 0.5);

	//bottom bottom right
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z - 0.5);

	//bottom bottom left
	vertices.push_back(position.x - 0.5f);
	vertices.push_back(position.y - 0.5f);
	vertices.push_back(position.z - 0.5);




	//Scroll the Texture along Y axis
	UVs[1] = UVs[1] + 0.005;

	UVs[3] = UVs[3] + 0.005;

	UVs[5] = UVs[5] + 0.005;

	UVs[7] = UVs[7] + 0.005;

	//if (demoChoice == "WATER") {
	//	//Second UVs
	//	UVs2[0] = UVs2[0] - 0.005;

	//	UVs2[2] = UVs2[2] - 0.005;

	//	UVs2[4] = UVs2[4] - 0.005;

	//	UVs2[6] = UVs2[6] - 0.005;
	//}

	//GLuint vertAttribID = TheBuffer::Instance()->vertexAttributeID;
	//GLuint colAttribID = TheBuffer::Instance()->colourAttributeID;


	//Sets the shader Uniform variable
	glUniform3f(mixColourID, 0.0f, 0.0f, 1.0f);

	////Sets the shader Uniform variable
	//shaderType = uniform3f;
	//TheShader::Instance()->setShaderVariable(mixColourID, shaderType, 0.0f, 0.0f, 1.0f, 0.0f);

	//Changes the colour interpolation value for a pulsing effect
	//if (reverse) {
	//	i -= 0.005;
	//}else { i += 0.005; }

	//if (i > 1) reverse = true;
	//if (i < 0) reverse = false;

	//if (demoChoice == "WATER") {

	//	i = 0.5;
	//}
	//else { i = 0; }

	//Sets the shader Uniform variable
	glUniform1f(mixValueID, i);

	////Sets the shader Uniform variable
	//shaderType = uniform1f;
	//TheShader::Instance()->setShaderVariable(mixValueID, shaderType, i, 0.0f, 0.0f, 0.0f);
	
	//Bind the vao for use
	glBindVertexArray(vao);

		////Vertex Data
		//TheBuffer::Instance()->fillBuffer(vertVBO, &vertices[0], vertices.size(), true);
		//TheBuffer::Instance()->linkBuffer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

		////Grid
		//TheBuffer::Instance()->fillBuffer(vertVBO, &gridVerts[0], gridVerts.size(), true);
		//TheBuffer::Instance()->linkBuffer(vertexAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
		//Colour Data
		TheBuffer::Instance()->fillBuffer(colVBO, &colours[0], colours.size(), true);
		TheBuffer::Instance()->linkBuffer(colourAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);


		//First UVs
		TheBuffer::Instance()->fillBuffer(textureVBO, &UVs[0], UVs.size(), true);
		TheBuffer::Instance()->linkBuffer(textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//Second UVs
		TheBuffer::Instance()->fillBuffer(textureVBO2, &UVs2[0], UVs2.size(), true);
		TheBuffer::Instance()->linkBuffer(textureAttributeID2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	

		//EBO
		TheBuffer::Instance()->fillArrayBuffer(ebo, &indices[0], indices.size());

	//Unbind the vao
	glBindVertexArray(0);

}


void Player::render(){

	shaderType = uniform1i;
	setShaderVariable(isLitID, shaderType, 1, 0, 0, 0); //Set the shader to light this Game Object

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->textureIDMap["CRATE"]);

	//if (demoChoice == "WATER") {
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->textureIDMap["WATER"]);

	//	glActiveTexture(GL_TEXTURE1);
	//	glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->textureIDMap["WATER"]);
	//}
	//if (demoChoice == "FILM") {
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->textureIDMap["FILM"]);
	//}

	glUniform1i(textureUniformID1, 0);
	glUniform1i(textureUniformID2, 1);

	shaderType = uniform1i;
	setShaderVariable(textureUniformID1, shaderType, 0, 0, 0, 0);
	setShaderVariable(textureUniformID2, shaderType, 1, 0, 0, 0);


	//Send model matrix to shader
	glUniformMatrix4fv(modelUniformID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewUniformID, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionUniformID, 1, GL_FALSE, &TheScreen::Instance()->projectionMatrix[0][0]);


	//Bind the vao
	glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, vertices.size() * 3, GL_UNSIGNED_INT, 0); //Draw using EBO
		//glDrawArrays(GL_LINES, 0, 4);

	glBindVertexArray(0); //Unbind the vao
}


void Player::onKeyboardEvent(const SDL_KeyboardEvent& e){

	//GameObject Input
	switch (e.keysym.sym) {

	case SDLK_RIGHT:

		position.x += 0.05f;

		break;

	case SDLK_LEFT:

		position.x -= 0.05f;

		break;

	case SDLK_UP:

		//position.y += 0.05f;

		//Scroll the Texture along Y axis
		UVs[1] = UVs[1] + 0.05;
		
		UVs[3] = UVs[3] + 0.05;
		
		UVs[5] = UVs[5] + 0.05;
		
		UVs[7] = UVs[7] + 0.05;

		break;

	case SDLK_DOWN:

		//position.y -= 0.05f;

		//Scroll the Texture along Y axis
		UVs[1] = UVs[1] - 0.05;
		
		UVs[3] = UVs[3] - 0.05;
		
		UVs[5] = UVs[5] - 0.05;

		UVs[7] = UVs[7] - 0.05;

		break;

	case SDLK_r:

		if (!R_enabled) {

			R_enabled = true;

			colours[0] = 1.0f;
			colours[3] = 1.0f;
			colours[6] = 1.0f;
			colours[9] = 1.0f;

		}
		else {

			colours[0] = 0.0f;
			colours[3] = 0.0f;
			colours[6] = 0.0f;
			colours[9] = 0.0f;

			R_enabled = false;
		}

		break;

	case SDLK_g:

		if (!G_enabled) {

			G_enabled = true;

			colours[1] = 1.0f;
			colours[4] = 1.0f;
			colours[7] = 1.0f;
			colours[10] = 1.0f;

		}
		else {

			colours[1] = 0.0f;
			colours[4] = 0.0f;
			colours[7] = 0.0f;
			colours[10] = 0.0f;

			G_enabled = false;
		}

		break;

	case SDLK_b:

		if (!R_enabled) {

			R_enabled = true;

			colours[2] = 1.0f;
			colours[5] = 1.0f;
			colours[8] = 1.0f;
			colours[11] = 1.0f;

		}
		else {

			colours[2] = 0.0f;
			colours[5] = 0.0f;
			colours[8] = 0.0f;
			colours[11] = 0.0f;

			R_enabled = false;
		}

		break;

	}

}

