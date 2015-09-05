#version 330

in vec2 uvCoord;
uniform sampler2D sample;

void main(void){
	if(texture(sample, uvCoord).a < 0.1){
		discard;
	}
	gl_FragColor = vec4(texture(sample, uvCoord).rgba);
}