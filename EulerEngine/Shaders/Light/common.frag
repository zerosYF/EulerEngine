#version 330
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform int reflectStrength;
uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

vec3 ambientLight(){
	float ambientStrength = 0.1f;
	return ambientStrength * lightColor;
}
vec3 diffuseLight(vec3 n,vec3 lightDir){
	float diff = max(dot(n,lightDir),0.0f);
	return diff * lightColor;
}
vec3 specularLight(vec3 n,vec3 lightDir){
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,n);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),reflectStrength);
	return spec * specularStrength * lightColor;
}

void main(){
	vec3 n = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 a = ambientLight();
	vec3 d = diffuseLight(n,lightDir);
	vec3 s = specularLight(n,lightDir);
	vec3 result = (a+d+s);
	FragColor = vec4(result,1.0f)*mix(texture(texture1,TexCoord),texture(texture2,TexCoord),0.2);
}