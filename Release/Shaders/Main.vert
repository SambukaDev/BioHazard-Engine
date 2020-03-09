#version 330 core

in vec3 position;
out vec4 positionOut;
in vec3 colourIn;

in vec3 normal;
out vec3 normalOut;

out vec3 colourOut;

in vec2 textureIn;
out vec2 textureUV;

in vec2 textureIn2;
out vec2 textureUV2;

uniform vec4 plane; // = vec4(0, -1, 0, 0);

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void){

	colourOut = colourIn;
	normalOut = normal;
	textureUV = textureIn;
	textureUV2 = textureIn2;
	positionOut = model * vec4(position, 1.0);
	gl_Position = projection * view * positionOut;
}