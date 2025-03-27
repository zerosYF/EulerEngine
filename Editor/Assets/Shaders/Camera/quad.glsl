#type vertex
#version 450 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aTexCoord;
layout(location = 2) in vec4 aColor;
layout(location = 3) in int aGameObjectID;

out vec2 TexCoord;
out vec4 color;
out flat int ObjID;

uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * vec4(aPosition, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	color = aColor;
	ObjID = aGameObjectID;
}

#type fragment
#version 450 core

in vec2 TexCoord;
in vec4 color;
in flat int ObjID;

uniform int texture_index;
uniform sampler2D textures[32];

layout(location = 0) out vec4 Color;
layout(location = 1) out int Color_red;
void main() {
	
	Color = mix(texture(textures[texture_index], TexCoord), color, 0.2f);
	Color_red = ObjID;
}