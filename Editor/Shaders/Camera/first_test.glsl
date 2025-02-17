#type vertex
#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aPosition, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}

#type fragment
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform vec4 color;
uniform int texture_index;
uniform sampler2D textures[32];
void main() {
	
	FragColor = mix(texture(textures[texture_index], TexCoord), color, 0.2f);
}