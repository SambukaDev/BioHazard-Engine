#include "Floor.h"
#include "BufferManager.h"
#include "ScreenManager.h"
#include "TextureManager.h"


Floor::Floor(){

	position = vec3(-3, 0, 0);

	ambient.r = 0.5;
	ambient.g = 0.5;
	ambient.b = 0.5;

	diffuse.r = 0.5;
	diffuse.g = 0.5;
	diffuse.b = 0.5;

	specular.r = 0.5;
	specular.g = 0.5;
	specular.b = 0.5;

	m_shininess = 20;


	materialPositionUniformID = TheShader::Instance()->getUniform("material.position");
	materialAmbientUniformID = TheShader::Instance()->getUniform("material.ambient");
	materialDiffuseUniformID = TheShader::Instance()->getUniform("material.diffuse");
	materialSpecularUniformID = TheShader::Instance()->getUniform("material.specular");
	materialShininessUniformID = TheShader::Instance()->getUniform("material.shininess");

	glUniform3fv(materialPositionUniformID, 1, &position.x);
	glUniform3fv(materialAmbientUniformID, 1, &ambient.r);
	glUniform3fv(materialDiffuseUniformID, 1, &diffuse.r);
	glUniform3fv(materialSpecularUniformID, 1, &specular.r);
	glUniform1f(materialShininessUniformID, m_shininess);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	//top left
	vertices.push_back(position.x -0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z + 0);

	//top right
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y + 0.5f);
	vertices.push_back(position.z + 0);

	//bottom right
	vertices.push_back(position.x + 0.5f);
	vertices.push_back(position.y -0.5f);
	vertices.push_back(position.z + 0);

	//bottom left
	vertices.push_back(position.x -0.5f);
	vertices.push_back(position.y -0.5f);
	vertices.push_back(position.z + 0);


	//1st UVs
	UVs.push_back(0.0f);//X
	UVs.push_back(0.0f);//Y

	UVs.push_back(1.0f);//X
	UVs.push_back(0.0f);//Y

	UVs.push_back(1.0f);//X
	UVs.push_back(1.0f);//Y

	UVs.push_back(0.0f);//X
	UVs.push_back(1.0f);//Y

	//2nd UVs
	UVs2.push_back(0.0f);//X
	UVs2.push_back(0.0f);//Y

	UVs2.push_back(1.0f);//X
	UVs2.push_back(0.0f);//Y

	UVs2.push_back(1.0f);//X
	UVs2.push_back(1.0f);//Y

	UVs2.push_back(0.0f);//X
	UVs2.push_back(1.0f);//Y


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


	modelMatrix = glm::scale(modelMatrix, vec3(4, 4, 4));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f), vec3(1, 0, 0));


	//fill with clour data
	colours.push_back(1.0f); //No colour mix
	colours.push_back(0.0f);
	colours.push_back(0.0f);

	colours.push_back(0.0f);
	colours.push_back(0.0f);
	colours.push_back(1.0f);

	colours.push_back(1.0f);
	colours.push_back(0.0f);
	colours.push_back(1.0f);

	colours.push_back(1.0f);
	colours.push_back(1.0f);
	colours.push_back(0.0f);


	vertexAttributeID = TheShader::Instance()->getAttribute("position");
	colourAttributeID = TheShader::Instance()->getAttribute("colourIn");

	normalAttributeID = TheShader::Instance()->getAttribute("normal");
	normalMatrixUniformID = TheShader::Instance()->getUniform("normalMatrix");


	textureAttributeID = TheShader::Instance()->getAttribute("textureIn");
	textureAttributeID2 = TheShader::Instance()->getAttribute("textureIn2");

	textureUniformID1 = TheShader::Instance()->getUniform("textureImage");
	textureUniformID2 = TheShader::Instance()->getUniform("otherTexture");


	TheBuffer::Instance()->generateArray(&vao);
	TheBuffer::Instance()->generateBuffer(&vertVBO);
	TheBuffer::Instance()->generateBuffer(&colVBO);
	TheBuffer::Instance()->generateBuffer(&textureVBO);
	TheBuffer::Instance()->generateBuffer(&textureVBO2);
	TheBuffer::Instance()->generateBuffer(&normalVBO);
	TheBuffer::Instance()->generateBuffer(&ebo);



	modelUniformID = TheShader::Instance()->getUniform("model");

	isLitID = TheShader::Instance()->getUniform("isLit");
	isWaterID = TheShader::Instance()->getUniform("isWater");

	TheTexture::Instance()->loadFromFile("Textures/Water.jpg", "WATER");
}


Floor::~Floor()
{
}


void Floor::update(){


	//Scroll the Texture along Y axis
	UVs[1] = UVs[1] + 0.005;

	UVs[3] = UVs[3] + 0.005;

	UVs[5] = UVs[5] + 0.005;

	UVs[7] = UVs[7] + 0.005;


	//Second UVs
	UVs2[0] = UVs2[0] - 0.005;

	UVs2[2] = UVs2[2] - 0.005;

	UVs2[4] = UVs2[4] - 0.005;

	UVs2[6] = UVs2[6] - 0.005;


	glUniform3fv(materialPositionUniformID, 1, &position.x);
	glUniform3fv(materialAmbientUniformID, 1, &ambient.r);
	glUniform3fv(materialDiffuseUniformID, 1, &diffuse.r);
	glUniform3fv(materialSpecularUniformID, 1, &specular.r);
	glUniform1f(materialShininessUniformID, m_shininess);


	//Extract the 3x3 normal matrix from the transformed model matrix
	normalMatrix = mat3(modelMatrix);
	


	//Bind the vao for use
	glBindVertexArray(vao);

		//Vertex Data
		TheBuffer::Instance()->fillBuffer(vertVBO, &vertices[0], vertices.size(), true);
		TheBuffer::Instance()->linkBuffer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Normal Data
		TheBuffer::Instance()->fillBuffer(normalVBO, &normals[0], normals.size(), true);
		TheBuffer::Instance()->linkBuffer(normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

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


void Floor::render(){

	glUniform1i(isLitID, 1);
	glUniform1i(isWaterID, 1);



	glUniform1i(textureUniformID1, 0);
	glUniform1i(textureUniformID2, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->textureIDMap["WATER"]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->textureIDMap["WATER"]);


	//Send model matrix to shader
	glUniformMatrix4fv(modelUniformID, 1, GL_FALSE, &modelMatrix[0][0]);

	glUniformMatrix3fv(normalMatrixUniformID, 1, GL_FALSE, &normalMatrix[0][0]);

	//Bind the vao
	glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, vertices.size() * 3, GL_UNSIGNED_INT, 0); //Draw using EBO

	glBindVertexArray(0); //Unbind the vao

	glUniform1i(isWaterID, 0);
}

