#type vertex
#version 330
layout(location=0) in vec3 aPosition;
layout(location=1) in vec2 aTexCoords;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(){
	gl_Position = projection*view*model*vec4(aPosition,1.0);
	TexCoords = aTexCoords;
}

#type fragment
#version 330
out vec4 FragColor;
void main(){
	FragColor = vec4(1.0,0.0,0.0,1.0);
}