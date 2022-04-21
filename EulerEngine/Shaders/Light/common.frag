#version 330
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
	sampler2D diffuseTex1;
	sampler2D specularTex1;
};
struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float reflectStrength;
};
uniform Material material;
uniform Light light;
uniform vec3 viewPos;

vec3 ambientLight(){
	return light.ambient * texture(material.diffuseTex1,TexCoord).rgb;
}
vec3 diffuseLight(vec3 n,vec3 lightDir){
	float diff = max(dot(n,lightDir),0.0f);
	return diff * light.diffuse * texture(material.diffuseTex1,TexCoord).rgb;
}
vec3 specularLight(vec3 n,vec3 lightDir){
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,n);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),light.reflectStrength);
	return spec * light.specular * texture(material.specularTex1,TexCoord).rgb;
}

void main(){
	vec3 n = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 a = ambientLight();
	vec3 d = diffuseLight(n,lightDir);
	vec3 s = specularLight(n,lightDir);
	vec3 result = (a+d+s);
	FragColor = vec4(result,1.0f);
}