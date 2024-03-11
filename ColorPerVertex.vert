#version 140
in vec4 input_color;
in vec3 position;
in vec3 input_normal;
in vec2 input_texCoord;
//uniform mat4 pvmMat;
uniform mat4 modelMat;     
uniform mat4 viewMat;      
uniform mat4 projectionMat;
out vec4 color;
out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;
	
void main()
{
	//gl_Position = pvmMat * vec4(position, 1.0f);
	gl_Position = projectionMat * viewMat * modelMat * vec4(position, 1.0f);
	//gl_Position = pvmMat * vec4(position, 1.0f);
	fragPos = vec3(modelMat * vec4(position, 1.0f));
	color = input_color;
	texCoord = input_texCoord;
	normal = input_normal;
}