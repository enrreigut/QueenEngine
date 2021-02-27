#version 330 core

layout(location = 0) out vec4 color;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normals;
in vec3 LightPos;

uniform sampler2D myTexture;
uniform vec3 gLightColor;

void main()
{
	//ambient
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * gLightColor;

	//diffuse
	vec3 norm = normalize(Normals);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * gLightColor;

	//specular
	float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * gLightColor; 

	color = texture(myTexture, TexCoord) * vec4((ambient + diffuse + specular), 1.0);
} 