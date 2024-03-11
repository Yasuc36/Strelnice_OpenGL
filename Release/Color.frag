#version 140
// uniform
uniform sampler2D modelTexture;
uniform bool useTexture;

uniform vec4 fogColor;
uniform float fogDensity;
uniform bool useFog;

uniform mat4 projectionMat;
uniform vec2 resolution;

// in
in vec4 color;
in vec2 texCoord;

// out 
out vec4 outColor;

void main()
{
	// distance from camera
	vec3 fragPosView = vec3((gl_FragCoord.xy / resolution.xy) * 2.0 - 1.0, 2.0 * gl_FragCoord.z - 1.0);
	vec4 fragPosWorld4 = inverse(projectionMat) * vec4(fragPosView.xyz, 1.0);
	vec3 fragPosWorld = fragPosWorld4.xyz / fragPosWorld4.w;
	float dist = length(fragPosWorld);

	// texture color
	vec4 texColor = vec4(1.0);
	if(useTexture) texColor = texture(modelTexture, texCoord);	
	outColor = color * texColor;
	
	// fog
	if(useFog)
	{
		float fogAmount = exp(-(fogDensity * dist) * (fogDensity * dist));	
		clamp(fogAmount, 0.0, 1.0);
		outColor = mix(fogColor, outColor, fogAmount);
	}
}