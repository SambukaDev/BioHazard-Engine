#include "BufferManager.h"
#include "ShaderManager.h"
#include "ScreenManager.h"
#include <iostream>

void BufferManager::createBuffers(){

	init();
}

BufferManager::BufferManager(){

	vertexVBO = 0;
	colourVBO = 0;
	EBO = 0;
	VAO = 0;

	//Get attribute location
	vertexAttributeID = glGetAttribLocation(TheShader::Instance()->shaderProgramID, "position");
	colourAttributeID = glGetAttribLocation(TheShader::Instance()->shaderProgramID, "colourIn");
	//uniform = glGetUniformLocation(TheShader::Instance()->shaderProgramID, "colourIn");
}


BufferManager::~BufferManager(){

	deleteBuffer(vertexVBO);
	deleteBuffer(colourVBO);
	deleteBuffer(EBO);

	deleteArray(VAO);

	deleteFrameBuffer(frameBufferID);
}


GLuint BufferManager::init(){

	//Initalise the buffer manager (generates the buffers)
	generateArray(&VAO);
	generateBuffer(&vertexVBO);
	generateBuffer(&colourVBO);
	generateBuffer(&EBO);

	//bindArray(VAO);

		
		/*if (dynamic) { fillBuffer(vertexVBO, vert, true); }
		else{ fillBuffer(vertexVBO, vert, false); }
		linkBuffer(vertexAttributeID, 3, GL_FLOAT, false, 0, 0);*/

		
		/*if (dynamic) { fillBuffer(colourVBO, col, true); }
		else { fillBuffer(colourVBO, col, false); }
		linkBuffer(colourAttributeID, 3, GL_FLOAT, false, 0, 0);*/

		
		//fillBuffer(EBO, indices);

	//bindArray(0);

	return VAO;
}


void BufferManager::generateBuffer(GLuint* ID){

	glGenBuffers(1, ID);
}


void BufferManager::fillBuffer(GLuint ID, const void* data, size_t numElements, bool dynamic) {

	glBindBuffer(GL_ARRAY_BUFFER, ID);//bind

	if (dynamic) {
		glBufferData(GL_ARRAY_BUFFER, numElements * sizeof(GLfloat), data, GL_DYNAMIC_DRAW); //fill
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, numElements * sizeof(GLfloat), data, GL_STATIC_DRAW); //fill
	}
}


void BufferManager::fillArrayBuffer(GLuint ID, const void* data, size_t numElements) {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);//bind
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements * sizeof(GLuint), data, GL_STATIC_DRAW); //fill
}


void BufferManager::linkBuffer(GLuint ID, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer){

	glVertexAttribPointer(ID, size, type, normalized, stride, pointer); //link

	glEnableVertexAttribArray(ID);
}


void BufferManager::generateArray(GLuint* ID){

	glGenVertexArrays(1, ID);
}


void BufferManager::bindArray(GLuint ID){

	glBindVertexArray(ID);
}


void BufferManager::generateFrameBuffer(){

	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
}


void BufferManager::bindFrameBuffer(GLint width, GLint height){

	glBindTexture(GL_TEXTURE_2D, 0); //Incase another texture is already bound
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID); //Bind FBO
	TheScreen::Instance()->setViewPort(0, 0, width, height); //Set viewport resolution to that of our texture
}


void BufferManager::unbindFrameBuffer(){

	glBindFramebuffer(GL_FRAMEBUFFER, 0); //Unbind to return to default OpenGL framebuffer
	TheScreen::Instance()->setViewPort(0, 0, TheScreen::Instance()->getWidth(), TheScreen::Instance()->getHeight()); //Set viewport resolution back to normal screen resolution
}


GLuint BufferManager::createFrameBufferTexture(GLint width, GLint height){

	unsigned char* pixels;

	GLuint ID;
	glGenTextures(1, &ID); //Gen texture ID
	glBindTexture(GL_TEXTURE_2D, ID); //Bind to the ID
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels); //Get texture data

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ID, 0); //Set texture to be used

	return ID;
}


GLuint BufferManager::createDepthTexture(GLint width, GLint height){

	unsigned char* pixels;

	GLuint ID;
	glGenTextures(1, &ID); //Gen texture ID
	glBindTexture(GL_TEXTURE_2D, ID); //Bind the ID
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, pixels); //Get texture Data

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ID, 0); //Set texture to be used

	return ID;
}


GLuint BufferManager::createDepthBuffer(GLint width, GLint height){

	GLuint ID;

	glGenRenderbuffers(1, &ID); //Gen bufffer ID
	glBindRenderbuffer(GL_RENDERBUFFER, ID); //Bind the ID
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height); //Specify the type

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, ID);

	return ID;
}


void BufferManager::deleteBuffer(GLuint ID){

	glDeleteBuffers(1, &ID);
}


void BufferManager::deleteArray(GLuint ID){

	glDeleteVertexArrays(1, &ID);
}


void BufferManager::deleteFrameBuffer(GLuint ID) {

	glDeleteFramebuffers(1, &ID);
}

