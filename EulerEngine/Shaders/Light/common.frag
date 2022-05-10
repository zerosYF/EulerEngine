#version 330
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material{
	sampler2D diffuseTex1;
	sampler2D specularTex1;
	float reflectStrength;
};
struct PointLight{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quatratic;
};
struct DirLight{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct SpotLight{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quatratic;
};
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform int dirLightCnt = 0;
uniform int pointLightCnt = 0;
uniform int spotLightCnt = 0;

uniform vec3 viewPos;
//--------------------------------------------------------------------------
vec3 ambientCal(vec3 ambient){
	return ambient * texture(material.diffuseTex1,TexCoord).rgb;
}
vec3 diffuseCal(vec3 n,vec3 lightDir,vec3 diffuse){
	float diff = max(dot(n,lightDir),0.0f);
	return diff * diffuse * texture(material.diffuseTex1,TexCoord).rgb;
}
vec3 specularCal(vec3 n,vec3 lightDir,vec3 specular){
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,n);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.reflectStrength);
	return spec * specular * texture(material.specularTex1,TexCoord).rgb;
}
//--------------------------------------------------------------------------
vec3 CalSpotLight(SpotLight spotLight){
	vec3 n = normalize(Normal);
	vec3 lightDir = normalize(spotLight.position - FragPos);
	vec3 d = normalize(-spotLight.direction);

	vec3 color = ambientCal(spotLight.ambient);
	color += diffuseCal(n,lightDir,spotLight.diffuse);
	color += specularCal(n,lightDir,spotLight.specular);

	float theta = dot(lightDir,d);
	float x = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta-spotLight.outerCutOff)/x,0.0f,1.0f);
	float distance = length(spotLight.position - FragPos);
	float attenuation = 1.0f/(spotLight.constant+spotLight.linear*distance+spotLight.quatratic*distance*distance);
	return color*intensity*attenuation;
}
vec3 CalPointLight(PointLight pointLight){
	vec3 n = normalize(Normal);
	vec3 lightDir = normalize(pointLight.position - FragPos);
	vec3 color = ambientCal(pointLight.ambient);
	color += diffuseCal(n,lightDir,pointLight.diffuse);
	color += specularCal(n,lightDir,pointLight.specular);

	float distance = length(pointLight.position - FragPos);
	float attenuation = 1.0f/(pointLight.constant+pointLight.linear*distance+pointLight.quatratic*distance*distance);
	return color * attenuation;
}

vec3 CalDirLight(DirLight dirLight){
	vec3 n = normalize(Normal);
	vec3 lightDir = normalize(-dirLight.direction);
	vec3 color = ambientCal(dirLight.ambient);
	color += diffuseCal(n,lightDir,dirLight.diffuse);
	color += specularCal(n,lightDir,dirLight.specular);
	return color;
}

void main(){
	vec3 dirlight_res = vec3(0.0);
	vec3 spotlight_res = vec3(0.0);
	vec3 pointlight_res = vec3(0.0);
	for(int i=0;i<dirLightCnt;i++){
		dirlight_res += CalDirLight(dirLight);
	}
	for(int i=0;i<spotLightCnt;i++){
		spotlight_res += CalSpotLight(spotLight);
	}
	for(int i=0;i<pointLightCnt;i++){
		pointlight_res += CalPointLight(pointLight);
	}
	vec3 result = dirlight_res + spotlight_res + pointlight_res;
	FragColor = vec4(result,1.0f);
}