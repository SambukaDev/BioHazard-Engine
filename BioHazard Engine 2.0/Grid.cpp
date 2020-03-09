#include "Grid.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include "ScreenManager.h"
#include <gtc\matrix_transform.hpp>


Grid::Grid(){

	vertices.reserve(1200);//allocate memory
	colours.reserve(1200);
	//indices.reserve(36);

	//negative x
	for (int i = 0; i < 50; i++) {

		vertices.push_back(position.x + i);  //x
		vertices.push_back(0.0f);            //y
		vertices.push_back(50.0f);          //z

		colours.push_back(1.0f);             //r
		colours.push_back(1.0f);             //g
		colours.push_back(1.0f);             //b

		vertices.push_back(position.x + i);  //x
		vertices.push_back(0.0f);            //y
		vertices.push_back(-50.0f);         //z

		colours.push_back(1.0f);             //r
		colours.push_back(1.0f);             //g
		colours.push_back(1.0f);             //b

	}

	for (int i = 0; i < 50; i++) {

		vertices.push_back(position.x - i);  //x
		vertices.push_back(0.0f);            //y
		vertices.push_back(50.0f);          //z

		colours.push_back(1.0f);             //r
		colours.push_back(1.0f);             //g
		colours.push_back(1.0f);             //b

		vertices.push_back(position.x - i);  //x
		vertices.push_back(0.0f);            //y
		vertices.push_back(-50.0f);         //z

		colours.push_back(1.0f);             //r
		colours.push_back(1.0f);             //g
		colours.push_back(1.0f);             //b

	}

	for (int i = 0; i < 50; i++) {

		vertices.push_back(-50.0f);			 //x
		vertices.push_back(0.0f);            //y
		vertices.push_back(position.z - i);  //z

		colours.push_back(1.0f);             //r
		colours.push_back(1.0f);             //g
		colours.push_back(1.0f);             //b

		vertices.push_back(50.0f);		 //x
		vertices.push_back(0.0f);            //y
		vertices.push_back(position.z - i);  //z

		colours.push_back(1.0f);             //r
		colours.push_back(1.0f);             //g
		colours.push_back(1.0f);             //b

	}
	
	for (int i = 0; i < 50; i++) {

		vertices.push_back(-50.0f);			 //x
		vertices.push_back(0.0f);            //y
		vertices.push_back(position.z + i);  //z

		colours.push_back(1.0f);             //r
		colours.push_back(1.0f);             //g
		colours.push_back(1.0f);             //b

		vertices.push_back(50.0f);		 //x
		vertices.push_back(0.0f);            //y
		vertices.push_back(position.z + i);  //z

		colours.push_back(1.0f);             //r
		colours.push_back(1.0f);             //g
		colours.push_back(1.0f);             //b

	}
	

	//position = vec3(0.0f, 0.0f, 0.0f);


	shaderID = TheShader::Instance()->shaderProgramID;

	vertexAttributeID = TheShader::Instance()->getAttribute("position");
	colourAttributeID = TheShader::Instance()->getAttribute("colourIn");


	////Gets the IDs from the Buffer manager
	//vertVBO = TheBuffer::Instance()->vertexVBO;
	//colVBO = TheBuffer::Instance()->colourVBO;
	//ebo = TheBuffer::Instance()->EBO;
	//vao = TheBuffer::Instance()->VAO;

	TheBuffer::Instance()->generateArray(&vao);
	TheBuffer::Instance()->generateBuffer(&vertVBO);
	TheBuffer::Instance()->generateBuffer(&colVBO);
	TheBuffer::Instance()->generateBuffer(&ebo);



	/*mixColourID = TheShader::Instance()->getUniform("mixColour");
	mixValueID = TheShader::Instance()->getUniform("mixValue");*/


	modelUniformID = TheShader::Instance()->getUniform("model");
	
	projectionUniformID = TheShader::Instance()->getUniform("projection");


	isLitID = TheShader::Instance()->getUniform("isLit");
}


Grid::~Grid()
{

	//destroy buffers

}


void Grid::update(){

	//Set model matrix to identity
	modelMatrix = mat4(1.0f);
	


	

	TheScreen::Instance()->projectionMatrix = glm::perspective(radians(60.0f), 1024.0f / 768.0f, 0.1f, 1000.0f);

	//Sets the shader Uniform variable
	//glUniform3f(mixColourID, 0.0f, 0.0f, 1.0f);


	//Sets the shader Uniform variable
	//glUniform1f(mixValueID, 1);

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
}


void Grid::render(){

	//Set obj to use color, not shader
	glUniform1i(isLitID, 0);


	glUniformMatrix4fv(modelUniformID, 1, GL_FALSE, &modelMatrix[0][0]);
	
	glUniformMatrix4fv(projectionUniformID, 1, GL_FALSE, &TheScreen::Instance()->projectionMatrix[0][0]);

	//Bind the vao
	glBindVertexArray(vao);

		//glDrawElements(GL_TRIANGLES, vertices.size() * 3, GL_UNSIGNED_INT, 0); //Draw using EBO
		glDrawArrays(GL_LINES, 0, 400);

	glBindVertexArray(0); //Unbind the vao
}

