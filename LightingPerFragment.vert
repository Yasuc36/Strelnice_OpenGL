#version 140
in vec4 inputColor;
in vec3 position;
in vec3 inputNormal;
in vec2 inputTexCoord;
uniform mat4 modelMat;     
uniform mat4 viewMat;      
uniform mat4 projectionMat;
out vec4 color;
out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;
	
void main()
{
	gl_Position = projectionMat * viewMat * modelMat * vec4(position, 1.0f);  // position on 2D screen calculated from 3D global coordinates
	fragPos = vec3(modelMat * vec4(position, 1.0f));
	color = inputColor;
	texCoord = inputTexCoord;  // coord in texture
	normal = inputNormal * mat3(transpose(inverse(modelMat)));  // For non-uniform scales. we need normals to have same direction. Costly operation
}