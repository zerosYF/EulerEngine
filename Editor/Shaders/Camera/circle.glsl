#type vertex
#version 450 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aLocalPosition;
layout(location = 2) in vec4 aColor;
layout(location = 3) in float aThickness;
layout(location = 4) in float aFade;
layout(location = 5) in int aGameObjectID;

out flat int ObjID;
out vec3 localPosition;
out vec4 color;
out float thickness;
out float fade;

uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * vec4(aPosition, 1.0f);
	ObjID = aGameObjectID;
	localPosition = aLocalPosition;
	color = aColor;
	thickness = aThickness;
	fade = aFade;
}

#type fragment
#version 450 core

in flat int ObjID;
in vec3 localPosition;
in vec4 color;
in float thickness;
in float fade;

layout(location = 0) out vec4 Color;
layout(location = 1) out int Color_red;
void main() {
	float distance = 1.0 - length(localPosition);
	float circle_alpha = smoothstep(0.0, fade, distance);
	circle_alpha *= smoothstep(thickness + fade, thickness, distance);
	Color = color;
	Color.a *= circle_alpha;
	Color_red = ObjID;
}