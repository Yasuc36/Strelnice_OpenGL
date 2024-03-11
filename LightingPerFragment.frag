#version 140
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct DirLight
{
	vec3 color;
	vec3 direction;
};

struct PointLight
{
	vec3 color;
	vec3 position;

	float constant;
	float linear;
	float quadratic;
	bool use;
};

struct SpotLight
{
	vec3 color;
	vec3 position;
	vec3 direction;
	float cutOff;
	bool use;
};

//uniform
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform vec3 viewPos;
uniform sampler2D modelTexture;
uniform sampler2D modelNormal;
uniform bool useTexture;
uniform bool isUi;

uniform vec4 fogColor;
uniform float fogDensity;
uniform bool useFog;
  
uniform mat4 projectionMat;
uniform vec2 resolution;

uniform int numImages;
uniform int numColumns;
uniform int currImage;
uniform vec2 shift;

//in
in vec4 color;
in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

//out 
out vec4 outColor;

void main()
{
	// distance from camera
	vec3 fragPosView = vec3((gl_FragCoord.xy / resolution.xy) * 2.0 - 1.0, 2.0 * gl_FragCoord.z - 1.0);
	vec4 fragPosWorld4 = inverse(projectionMat) * vec4(fragPosView.xyz, 1.0);
	vec3 fragPosWorld = fragPosWorld4.xyz / fragPosWorld4.w;
	float cameraDist = length(fragPosWorld);


	// ambient light
	vec3 ambient = vec3(1.0);
	if(!isUi) ambient = material.ambient * 3.0;

	// diffuse and specular lights
	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);
	if(normal != vec3(0.0))
	{		
		// direct light
		vec3 norm = normalize(normal);
		vec3 viewDir = normalize(viewPos - fragPos);
		vec3 dirLightDir = normalize(-dirLight.direction);
		// diffuse shading
		float diff = max(dot(norm, dirLightDir), 0.0);
		// specular shading
		vec3 reflectDir = reflect(-dirLightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		// combine results
		diffuse = dirLight.color * diff * material.diffuse;
		specular = spec * material.specular;	
	}
	// point light
	float linear = 4.0f;
	if(pointLight.use) linear = pointLight.linear;
	float pointDist = length(pointLight.position - fragPos);
	vec3 pointLightAttenuation = (1.0 / (pointLight.constant + linear * pointDist + pointLight.quadratic * (pointDist * pointDist))) * pointLight.color;		
	pointLightAttenuation = max(pointLightAttenuation, 0.3);
	ambient = ambient * pointLightAttenuation;
	diffuse = diffuse * pointLightAttenuation;
	specular = specular * pointLightAttenuation;
	
	// spot light
	vec3 spotFactor = vec3(0.0, 0.0, 0.0);
	if (spotLight.use)
	{
		vec3 spotLightDir = normalize(spotLight.position - fragPos);
		float theta = dot(spotLightDir, normalize(-spotLight.direction));
		if(theta > (spotLight.cutOff)) spotFactor += 0.3;
	}

	//texture color
	vec4 tex_color = vec4(1.0);
	if(useTexture)
	{
		// calcualting texture image for sprite animation
		ivec2 pattern = ivec2(numColumns, ((numImages+numColumns-1)/numColumns));
		vec2 offset = vec2(1.0/pattern.x, 1.0/pattern.y);
		vec2 texCoordBase = texCoord / vec2(pattern);
		vec2 resultTexCoord = texCoordBase + vec2(currImage % pattern.x, pattern.y - 1 - (currImage / pattern.x)) * offset;

		// calculating texture shift
		resultTexCoord += shift;

		// texture color
		tex_color = texture(modelTexture, resultTexCoord);
	}


	// output color without fog
	outColor = color * tex_color * vec4((ambient + diffuse + specular) + spotFactor*spotLight.color, 1.0);

	outColor += vec4(dirLight.direction.xyz, 1.0) * 0.0;

	// fog
	if(useFog)
	{
		float fogAmount = exp(-(fogDensity * cameraDist) * (fogDensity * cameraDist));	
		clamp(fogAmount, 0.0, 1.0);
		outColor = mix(fogColor, outColor, fogAmount);
	}
}