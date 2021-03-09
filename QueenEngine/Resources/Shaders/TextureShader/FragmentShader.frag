#version 330 core

layout(location = 0) out vec4 color;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normals;
in vec3 LightPos;

uniform sampler2D myTexture;
uniform vec4 gLightColor;

uniform float ambientStrength;
uniform float specularStrength;

void main()
{
	//ambient
	
    vec4 ambient = ambientStrength * gLightColor;

	//diffuse
	vec3 norm = normalize(Normals);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * gLightColor;

	//specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = specularStrength * spec * gLightColor; 

	color = texture(myTexture, TexCoord) * vec4(ambient + diffuse + specular);
} 