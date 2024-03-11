#include "CommonShaders.h"

CommonShaders::CommonShaders()
{
	Index = 0;

	Pos = -1;
	Color = -1;
	Normal = -1;
	TexNormal = -1;
	TexCoord = -1;

	ModelMat = -1;
	ViewMat = -1;
	ProjectionMat = -1;
	NormalMat = -1;

	Time = -1;

	// material 
	MaterialDiffuse = -1;
	MaterialAmbient = -1;
	MaterialSpecular = -1;
	MaterialShininess = -1;
	// texture
	UseTexture = -1;
	TexSampler = -1;
	// light
	DirLightColor = -1;
	DirLightDirection = -1;

	PointLightColor = -1;
	PointLightPosition = -1;
	PointLightConstant = -1;
	PointLightLinear = -1;
	PointLightQuadratic = -1;
	PointLightUse = -1;

	SpotLightColor = -1;
	SpotLightPosition = -1;
	SpotLightDirection = -1;
	SpotLightCutOff = -1;
	SpotLightUse = -1;

	ViewPos = -1;

	FogColor = -1;
	FogDensity = -1;
	UseFog = -1;

	NumImages = -1;
	NumColumns = -1;
	CurrImage = -1;

	Shift = -1;

	Resolution = -1;

	IsUi = -1;

	Initialized = false;
}