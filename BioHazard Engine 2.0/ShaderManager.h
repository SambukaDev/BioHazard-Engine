#pragma once
#include <glew.h>
#include "Singleton.h"

#include <map>
#include <string>
using std::string;
using std::map;


class ShaderManager : public Uncopyable{

private:

	friend Singleton < ShaderManager >;

	map<string, GLuint> shaderVariableIDMap;

public:
	ShaderManager();
	~ShaderManager();

	GLuint shaderProgramID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	GLuint getAttribute(string attrib);
	GLuint getUniform(string uniform);
	
	//template <typename T>
	//void setShaderVariable(GLuint locationID, uniformShaderType type, T var1, T var2, T var3, T var4);

	void createShaderProgram();
	void createShaders();

	void compileShaders(string fileName, GLuint shaderID);
	void attachShaders();
	void linkProgram();
	
	void detatchShaders();
	void destroyShaderProgram();
};

typedef Singleton<ShaderManager> TheShader;

enum uniformShaderType
{
	uniform1f,
	uniform1fv,
	uniform1i,
	uniform1iv,
	uniform1ui,
	uniform1uiv,

	uniform2f,
	uniform2fv,
	uniform2i,
	uniform2iv,
	uniform2ui,
	uniform2uiv,

	uniform3f,
	uniform3fv,
	uniform3i,
	uniform3iv,
	uniform3ui,
	uniform3uiv,

	uniform4f,
	uniform4fv,
	uniform4i,
	uniform4iv,
	uniform4ui,
	uniform4uiv
};

template <typename T>
void setShaderVariable(GLuint locationID, uniformShaderType type, T var1, T var2, T var3, T var4) {

	switch (type) {

	case uniform1f:	  glUniform1f(locationID, var1); break;
		//case uniform1fv:  glUniform1fv(locationID, &var1); break;
	case uniform1i:	  glUniform1i(locationID, var1); break;
		//case uniform1iv:  glUniform1iv(locationID, var1); break;
	case uniform1ui:  glUniform1ui(locationID, var1); break;
		//case uniform1uiv: glUniform1uiv(locationID, var1); break;

	case uniform2f:	  glUniform2f(locationID, var1, var2); break;
		//case uniform2fv:  glUniform2fv(locationID, var1, var2); break;
	case uniform2i:   glUniform2i(locationID, var1, var2); break;
		//case uniform2iv:  glUniform2iv(locationID, var1, var2); break;
	case uniform2ui:  glUniform2ui(locationID, var1, var2); break;
		//case uniform2uiv: glUniform2uiv(locationID, var1, var2); break;

	case uniform3f:	  glUniform3f(locationID, var1, var2, var3); break;
		//case uniform3fv:  glUniform3fv(locationID, var1, var2, var3); break;
	case uniform3i:   glUniform3i(locationID, var1, var2, var3); break;
		//case uniform3iv:  glUniform3iv(locationID, var1, var2, var3); break;
	case uniform3ui:  glUniform3ui(locationID, var1, var2, var3); break;
		//case uniform3uiv: glUniform3uiv(locationID, var1, var2, var3); break;

	case uniform4f:	  glUniform4f(locationID, var1, var2, var3, var4); break;
		//case uniform4fv:  glUniform4fv(locationID, var1, var2, var3, var4); break;
	case uniform4i:   glUniform4i(locationID, var1, var2, var3, var4); break;
		//case uniform4iv:  glUniform4iv(locationID, var1, var2, var3, var4); break;
	case uniform4ui:  glUniform4ui(locationID, var1, var2, var3, var4); break;
		//case uniform4uiv: glUniform4uiv(locationID, var1, var2, var3, var4); break;
	}

}
