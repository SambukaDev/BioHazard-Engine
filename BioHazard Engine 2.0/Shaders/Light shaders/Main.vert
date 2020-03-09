#version 330 core

in vec3 position;
in vec3 colourIn;

out vec3 colourOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void){

	colourOut = colourIn;
	gl_Position = projection * view * model * vec4(position, 1.0);
}