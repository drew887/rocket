#version 330
 layout(location=0 ) in vec2 position;
 layout(location=1 )in vec3 colour;
 out vec3 out_colour;

 uniform mat4 world;
 uniform mat4 model;

 void main(void){
	gl_Position = world * model * vec4(position, 0.0, 1.0);
	out_colour = colour;
 }