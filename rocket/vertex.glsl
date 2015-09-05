#version 330
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvposition;

out vec2 uvCoord;

uniform mat4 world;
uniform mat4 camera;
uniform mat4 model;

void main(void){
	gl_Position = world * camera * model * vec4(position, 0.0, 1.0);
	uvCoord = uvposition;
}