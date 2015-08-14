#version 330

in vec2 uvCoord;


uniform sampler2D sample;

void main(void){
	##gl_FragColor = vec4(out_colour, 1.0);
	gl_FragColor = vec4(texture(sample, uvCoord).rgb, 1.0);
}