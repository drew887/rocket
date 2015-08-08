#version 330
 in vec2 position;
 uniform mat4 world;
 uniform mat4 model;

 void main(void){
	gl_Position = world * model * vec4(position, -1.0, 1.0);
 }