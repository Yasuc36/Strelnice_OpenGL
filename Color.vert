#version 140
// uniform
uniform mat4 modelMat;     
uniform mat4 viewMat;      
uniform mat4 projectionMat;
// in
in vec4 inputColor;
in vec3 position;
in vec2 inputTexCoord;
// out
out vec4 color;
out vec2 texCoord;
	
void main()
{
	gl_Position = projectionMat * viewMat * modelMat * vec4(position, 1.0);  // position on 2D screen from 3D Global coordinates
	color = inputColor;
	texCoord = inputTexCoord;
}