#include "ShaderManager.h"
#include <iostream>

#include <fstream>

using std::cout;
using std::endl;
using std::fstream;

ShaderManager::ShaderManager(){

	vertexShaderID = 0;
	fragmentShaderID = 0;
	shaderProgramID = 0;
}


ShaderManager::~ShaderManager()
{
}


GLuint ShaderManager::getAttribute(string attrib){

	//Searchs if ID has been previously stored
	map<string, GLuint>::iterator it = shaderVariableIDMap.find(attrib);

	//If not found, get ID
	if (it == shaderVariableIDMap.end()) {

		//Gets the attribute ID and stores it
		shaderVariableIDMap[attrib] = glGetAttribLocation(shaderProgramID, attrib.c_str());
	}

	//Return ID
	return shaderVariableIDMap[attrib];
}


GLuint ShaderManager::getUniform(string uniform){

	//Searchs if ID has been previously stored
	map<string, GLuint>::iterator it = shaderVariableIDMap.find(uniform);

	//If not found, get ID
	if (it == shaderVariableIDMap.end()) {

		//Gets the uniform ID and stores it
		shaderVariableIDMap[uniform] = glGetUniformLocation(shaderProgramID, uniform.c_str());
	}

	//Return ID
	return shaderVariableIDMap[uniform];
}


void ShaderManager::createShaderProgram(){

	//Create program & assign its ID to the ID for handling later
	shaderProgramID = glCreateProgram();

	if (shaderProgramID == 0) {

		cout << "\n==================================================" << endl;
		cout << "Shader Manager: Error with creating Shader Program" << endl;
		cout << "==================================================\n" << endl;
	}
}


void ShaderManager::createShaders(){

	//Create vertex shader
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (vertexShaderID == 0) {

		cout << "\n================================================" << endl;
		cout << "Shader Manager: Error with creating Vertex Shader" << endl;
		cout << "=================================================\n" << endl;

	}

	//Create fragment shader
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (fragmentShaderID == 0) {

		cout << "\n===================================================" << endl;
		cout << "Shader Manager: Error with creating Fragment Shader" << endl;
		cout << "===================================================\n" << endl;
	}
}


void ShaderManager::compileShaders(string fileName, GLuint shaderID){

	fstream file;
	string lineText = "";
	string finalString = "";


	/*
	COMPILE THE VERTEX SHADER
	*/
	//file.open("Shaders/Main.vert");
	file.open(fileName.c_str());

	if (!file) {

		cout << "\n========================================================" << endl;
		cout << "Shader Manager: Error with opening Main.vert Shader file" << endl;
		cout << "========================================================\n" << endl;
	}

	while (!file.eof()) {

		getline(file, lineText);
		finalString += lineText + "\n";
	}

	file.close();

	//Converts string into GLChar (format accepted by the GPU)
	const GLchar* finalCode = static_cast<const GLchar*>(finalString.c_str());

	//Send the data to the GPU
	glShaderSource(shaderID, 1, &finalCode, NULL);

	//Compile the Shader code
	glCompileShader(shaderID);

	//Check for compilation errors
	GLint compileResult;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);


	if (compileResult == GL_FALSE) {

		GLchar error[1000];
		GLsizei length = 1000;

		//Gets the errors from the shader error log
		glGetShaderInfoLog(shaderID, length, &length, error);

		cout << "\n===================================================" << endl;
		cout << "Shader Manager: Error with compilling Shader" << endl;
		cout << "===================================================\n" << endl;
		cout << error << "\n" << endl;

//#error Shader Manager: Error with compilling Shader
	}




	///*
	//COMPILE THE FRAGMENT SHADER
	//*/
	//finalString = "";

	//file.open("Shaders/Main.frag");

	//if (!file) {

	//	cout << "\n========================================================" << endl;
	//	cout << "Shader Manager: Error with opening Main.frag Shader file" << endl;
	//	cout << "========================================================\n" << endl;
	//}

	//while (!file.eof()) {

	//	getline(file, lineText);
	//	finalString += lineText + "\n";
	//}

	//file.close();


	//finalCode = static_cast<const GLchar*>(finalString.c_str());

	//glShaderSource(fragmentShaderID, 1, &finalCode, NULL);

	//glCompileShader(fragmentShaderID);


	//compileResult = 0;

	//glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &compileResult);


	//if (compileResult == GL_FALSE) {

	//	GLchar error[1000];
	//	GLsizei length = 1000;

	//	glGetShaderInfoLog(fragmentShaderID, length, &length, error);

	//	cout << "\n=====================================================" << endl;
	//	cout << "Shader Manager: Error with compilling Fragment Shader" << endl;
	//	cout << "-----------------------------------------------------\n" << endl;
	//	cout << error << "\n" << endl;
	//	cout << "=====================================================" << endl;
	//}
}


void ShaderManager::attachShaders() {

	glAttachShader(shaderProgramID, vertexShaderID);

	glAttachShader(shaderProgramID, fragmentShaderID);
}


void ShaderManager::linkProgram(){

	glLinkProgram(shaderProgramID);

	glUseProgram(shaderProgramID);


	GLint linkResult;

	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE) {

		GLchar error[1000];
		GLsizei length = 1000;

		glGetProgramInfoLog(shaderProgramID, length, &length, error);

		cout << "\n=========================================" << endl;
		cout << "Shader Manager: Error with linking Shader" << endl;
		cout << "=========================================\n" << endl;
	}

}


void ShaderManager::detatchShaders(){

	glDetachShader(shaderProgramID, fragmentShaderID);
	glDetachShader(shaderProgramID, vertexShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(shaderProgramID);
}


void ShaderManager::destroyShaderProgram(){

	glDeleteProgram(shaderProgramID);
}

