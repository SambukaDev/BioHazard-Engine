#pragma once
#include <glew.h>
#include "Singleton.h"
#include <string>
#include <map>
using std::map;
using std::string;


class BufferManager : public Uncopyable{

private:

	friend Singleton < BufferManager >;



	void createBuffers();

public:
	BufferManager();
	~BufferManager();

	GLuint vertexAttributeID;
	GLuint colourAttributeID;
	GLuint uniform;
	GLfloat mixVal;

	GLuint vertexVBO;
	GLuint colourVBO;
	GLuint EBO;
	GLuint VAO;

	GLuint frameBufferID;

	GLuint init();

	void generateBuffer(GLuint* ID);
	void fillBuffer(GLuint ID, const void* data, size_t numElements, bool dynamic);
	void fillArrayBuffer(GLuint ID, const void* data, size_t numElements);
	void linkBuffer(GLuint ID, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

	void generateArray(GLuint* ID);
	void bindArray(GLuint ID);

	void generateFrameBuffer();
	void bindFrameBuffer(GLint width, GLint height);
	void unbindFrameBuffer();
	GLuint createFrameBufferTexture(GLint width, GLint height);
	GLuint createDepthTexture(GLint width, GLint height);
	GLuint createDepthBuffer(GLint width, GLint height);

	void deleteBuffer(GLuint ID);
	void deleteArray(GLuint ID);
	void deleteFrameBuffer(GLuint ID);
};

typedef Singleton<BufferManager> TheBuffer;