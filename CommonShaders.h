#pragma once

#include "pgr.h"

/**
 * \brief Contains positions of all shaders used for shader program
 */
class CommonShaders
{
public:
	GLuint Index;  ///< identifier for the shader program

	// vertex attributes
	GLint Pos;  ///< position of vertex
	GLint Color;  ///< color of vertex
	GLint Normal;  ///< normal of vertex
	GLint TexNormal;  ///< normal of texture
	GLint TexCoord;  ///< coordinate in texture

	GLint ModelMat;   ///< modeling matrix
	GLint ViewMat;  ///< view/camera matrix
	GLint ProjectionMat;  ///< projection matrix
	GLint NormalMat;  ///< inverse transposed Mmatrix

	GLint Time;  ///< elapsed time in seconds

	// material 
	GLint MaterialDiffuse;   
	GLint MaterialAmbient;   
	GLint MaterialSpecular; 
	GLint MaterialShininess; 
	// texture
	GLint UseTexture; 
	GLint TexSampler;  ///< sampler to proccess image texture
	// light
	GLint DirLightColor;
	GLint DirLightDirection;
	
	GLint PointLightColor; 
	GLint PointLightPosition;
	GLint PointLightConstant;
	GLint PointLightLinear;
	GLint PointLightQuadratic;
	GLint PointLightUse;

	GLint SpotLightColor;
	GLint SpotLightPosition;
	GLint SpotLightDirection;
	GLint SpotLightCutOff;
	GLint SpotLightUse;

	GLint ViewPos;  ///< Position of view in global

	GLint FogColor;
	GLint FogDensity;
	GLint UseFog;

	GLint NumImages;  ///< number of images in sprite
	GLint NumColumns;  ///< number of columns in sprite
	GLint CurrImage;  ///< current image in sprite

	GLint Shift;  ///< how much should texture shift

	GLint Resolution;
	
	GLint IsUi;

	bool Initialized;

	CommonShaders();
};