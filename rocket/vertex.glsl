#version 330
 in vec2 position;

 void main(void){
	gl_Position = vec4(position, 1.0, 1.0);
 }