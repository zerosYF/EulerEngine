#type vertex
#version 330 core
layout(location=0) in vec3 aPosition;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main(){
	gl_Position = projection*view*model*vec4(aPosition,1.0f);
}

#type fragment
#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;

void main(){
	FragColor = vec4(lightColor,1.0f);
}