#include "Cube.h"
#include "BufferManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"


Cube::Cube(string path, string ID){

	texPath = path;
	texID = ID;

	ambient.r = 0.5;//Defualt lighting
	ambient.g = 0.5;
	ambient.b = 0.5;

	diffuse.r = 0.5;
	diffuse.g = 0.5;
	diffuse.b = 0.5;

	specular.r = 0.5;
	specular.g = 0.5;
	specular.b = 0.5;

	m_shininess = 20;


	for (int i = 0; i < 6; i++) {

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


	textureAttributeID = TheShader::Instance()->getAttribute("textureIn");

	materialPositionUniformID = TheShader::Instance()->getUniform("material.position");
	materialAmbientUniformID = TheShader::Instance()->getUniform("material.ambient");
	materialDiffuseUniformID = TheShader::Instance()->getUniform("material.diffuse");
	materialSpecularUniformID = TheShader::Instance()->getUniform("material.specular");
	materialShininessUniformID = TheShader::Instance()->getUniform("material.shininess");

	vertexAttributeID = TheShader::Instance()->getAttribute("position");
	colourAttributeID = TheShader::Instance()->getAttribute("colourIn");

	normalAttributeID = TheShader::Instance()->getAttribute("normal");
	normalMatrixUniformID = TheShader::Instance()->getUniform("normalMatrix");

	modelUniformID = TheShader::Instance()->getUniform("model");

	isLitID = TheShader::Instance()->getUniform("isLit");


	glUniform3fv(materialPositionUniformID, 1, &position.x);
	glUniform3fv(materialAmbientUniformID, 1, &ambient.r);
	glUniform3fv(materialDiffuseUniformID, 1, &diffuse.r);
	glUniform3fv(materialSpecularUniformID, 1, &specular.r);
	glUniform1f(materialShininessUniformID, m_shininess);



	fillIndices();
	fillVerts();
	fillNormals();


	TheBuffer::Instance()->generateArray(&vao);
	TheBuffer::Instance()->generateBuffer(&vertVBO);
	TheBuffer::Instance()->generateBuffer(&colVBO);
	TheBuffer::Instance()->generateBuffer(&textureVBO);
	TheBuffer::Instance()->generateBuffer(&normalVBO);
	TheBuffer::Instance()->generateBuffer(&ebo);

	//"Textures/Wall.jpg";
	TheTexture::Instance()->loadFromFile(texPath.c_str(), texID.c_str());
}


Cube::~Cube()
{
}


void Cube::update(){

	fillVerts();

	//glUniform3fv(materialPositionUniformID, 1, &position.x);
	//glUniform3fv(materialAmbientUniformID, 1, &ambient.r);
	//glUniform3fv(materialDiffuseUniformID, 1, &diffuse.r);
	//glUniform3fv(materialSpecularUniformID, 1, &specular.r);
	//glUniform1f(materialShininessUniformID, m_shininess);


	//Extract the 3x3 normal matrix from the transformed model matrix
	normalMatrix = glm::inverse(mat3(modelMatrix));
	//normalMatrix = mat3(modelMatrix);



	//Bind the vao for use
	glBindVertexArray(vao);

		//Vertex Data
		TheBuffer::Instance()->fillBuffer(vertVBO, &vertices[0], vertices.size(), true);
		TheBuffer::Instance()->linkBuffer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Normal Data
		TheBuffer::Instance()->fillBuffer(normalVBO, &normals[0], normals.size(), true);
		TheBuffer::Instance()->linkBuffer(normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//UVs
		TheBuffer::Instance()->fillBuffer(textureVBO, &UVs[0], UVs.size(), true);
		TheBuffer::Instance()->linkBuffer(textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//EBO
		TheBuffer::Instance()->fillArrayBuffer(ebo, &indices[0], indices.size());

	//Unbind the vao
	glBindVertexArray(0);
}


void Cube::render(){

	glUniform1i(isLitID, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->textureIDMap[texID.c_str()]);

	//Send model matrix to shader
	glUniformMatrix4fv(modelUniformID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix3fv(normalMatrixUniformID, 1, GL_FALSE, &normalMatrix[0][0]);

	glUniform3fv(materialPositionUniformID, 1, &position.x);
	glUniform3fv(materialAmbientUniformID, 1, &ambient.r);
	glUniform3fv(materialDiffuseUniformID, 1, &diffuse.r);
	glUniform3fv(materialSpecularUniformID, 1, &specular.r);
	glUniform1f(materialShininessUniformID, m_shininess);


	//Bind the vao
	glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, vertices.size() * 3, GL_UNSIGNED_INT, 0); //Draw using EBO

	glBindVertexArray(0); //Unbind the vao
}


void Cube::fillVerts(){

	if (vertices.size() > 0) {
		vertices.clear();
	}

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
}


void Cube::fillNormals(){

	//Front face
	normals.push_back(0.0f);
	normals.push_back(0.0f);
	normals.push_back(1.0f);

	normals.push_back(0.0f);
	normals.push_back(0.0f);
	normals.push_back(1.0f);

	normals.push_back(0.0f);
	normals.push_back(0.0f);
	normals.push_back(1.0f);

	normals.push_back(0.0f);
	normals.push_back(0.0f);
	normals.push_back(1.0f);

	//Back face
	normals.push_back(0.0f);
	normals.push_back(0.0f);
	normals.push_back(-1.0f);

	normals.push_back(0.0f);
	normals.push_back(0.0f);
	normals.push_back(1.0f);

	normals.push_back(0.0f);
	normals.push_back(0.0f);
	normals.push_back(-1.0f);

	normals.push_back(0.0f);
	normals.push_back(0.0f);
	normals.push_back(-1.0f);

	//Left face
	normals.push_back(-1.0f);
	normals.push_back(0.0f);
	normals.push_back(0.0f);

	normals.push_back(-1.0f);
	normals.push_back(0.0f);
	normals.push_back(0.0f);

	normals.push_back(-1.0f);
	normals.push_back(0.0f);
	normals.push_back(0.0f);

	normals.push_back(-1.0f);
	normals.push_back(0.0f);
	normals.push_back(0.0f);

	//Right face
	normals.push_back(1.0f);
	normals.push_back(0.0f);
	normals.push_back(0.0f);

	normals.push_back(1.0f);
	normals.push_back(0.0f);
	normals.push_back(0.0f);

	normals.push_back(1.0f);
	normals.push_back(0.0f);
	normals.push_back(0.0f);

	normals.push_back(1.0f);
	normals.push_back(0.0f);
	normals.push_back(0.0f);

	//Top face
	normals.push_back(0.0f);
	normals.push_back(1.0f);
	normals.push_back(0.0f);

	normals.push_back(0.0f);
	normals.push_back(1.0f);
	normals.push_back(0.0f);

	normals.push_back(0.0f);
	normals.push_back(1.0f);
	normals.push_back(0.0f);

	normals.push_back(0.0f);
	normals.push_back(1.0f);
	normals.push_back(0.0f);

	//Bottom face
	normals.push_back(0.0f);
	normals.push_back(-1.0f);
	normals.push_back(0.0f);

	normals.push_back(0.0f);
	normals.push_back(-1.0f);
	normals.push_back(0.0f);

	normals.push_back(0.0f);
	normals.push_back(-1.0f);
	normals.push_back(0.0f);

	normals.push_back(0.0f);
	normals.push_back(-1.0f);
	normals.push_back(0.0f);
}


void Cube::fillIndices(){

	for (int i = 0; i < 6; i++) {

		//fill with indices data
		indices.push_back(0 + 4 * i);
		indices.push_back(1 + 4 * i);
		indices.push_back(3 + 4 * i);
		indices.push_back(1 + 4 * i);
		indices.push_back(2 + 4 * i);
		indices.push_back(3 + 4 * i);
	}
}


void Cube::setDimensions(vec3 dim){

	modelMatrix = glm::scale(modelMatrix, dim);
}


void Cube::setPosition(vec3 pos){

	position = pos;
}


void Cube::setRotation(GLfloat angle, vec3 axis){

	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
}


void Cube::setAmbient(vec3 amb){

	ambient = amb;
}


void Cube::setDiffuse(vec3 diff){

	diffuse = diff;
}


void Cube::setSpecular(vec3 spec, GLfloat shine){

	specular = spec;
	m_shininess = shine;
}

