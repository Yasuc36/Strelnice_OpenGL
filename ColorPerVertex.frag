#version 140
in vec4 color;
in vec3 normal;
in vec3 fragPos;
uniform vec3 lightColor;
in vec2 texCoord;
out vec4 out_color;
uniform sampler2D modelTexture;
uniform sampler2D modelNormal;
uniform bool useTexture;
uniform bool isUi;
uniform vec3 lightPos;
//out 

void main()
{
	//ambient
	vec3 ambient = vec3(1.0f);
	if(!isUi) ambient = vec3(lightColor * 0.1f);

	//diffuse light
	vec3 diffuse = vec3(0.0f);
	if(normal != vec3(0.0f))
	{
		vec3 norm = normalize(normal);
		vec3 lightDir = normalize(lightPos - fragPos);
		diffuse = lightColor * max(dot(norm, lightDir), 0.0f);
	}

	//texture color
	vec4 tex_color = vec4(1.0f);
	if(useTexture) tex_color = texture(modelTexture, texCoord);
	
	out_color = color * tex_color * vec4((ambient + diffuse), 1.0f);
}