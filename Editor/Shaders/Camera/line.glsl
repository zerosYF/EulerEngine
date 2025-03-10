#type vertex
#version 450 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in int aGameObjectID;

uniform mat4 view;
uniform mat4 projection;

out vec4 color;
out flat int ObjID;

void main(){
	gl_Position = projection * view * vec4(aPosition, 1.0f);
	color = aColor;
	ObjID = aGameObjectID;
}

#type fragment
#version 450 core

in vec4 color;
in flat int ObjID;

layout(location = 0) out vec4 Color;
layout(location = 1) out int Color_red;
void main(){
	Color = color;
	Color_red = ObjID;
}
