#version 330

in vec3 out_colour;

void main(void){
	gl_FragColor = vec4(out_colour, 1.0);
}