#version 330 core

in vec3 colourOut;
out vec4 pixelColour;

void main(void){

	pixelColour = vec4(colourOut, 1.0);
}