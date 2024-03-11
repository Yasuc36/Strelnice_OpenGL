#include "ServiceClass.h"

void ServiceClass::LoadShaderPrograms()
{
	std::vector<GLuint> shaderList;

	// Light shader
	shaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "LightingPerFragment.vert"));
	shaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "LightingPerFragment.frag"));
	commonShaders.Index = pgr::createProgram(shaderList);

	commonShaders.Pos = glGetAttribLocation(commonShaders.Index, "position");
	commonShaders.Normal = glGetAttribLocation(commonShaders.Index, "inputNormal");
	commonShaders.TexNormal = glGetUniformLocation(commonShaders.Index, "modelNormal");
	commonShaders.TexCoord = glGetAttribLocation(commonShaders.Index, "inputTexCoord");
	commonShaders.Color = glGetAttribLocation(commonShaders.Index, "inputColor");

	commonShaders.ModelMat = glGetUniformLocation(commonShaders.Index, "modelMat");
	commonShaders.ViewMat = glGetUniformLocation(commonShaders.Index, "viewMat");
	commonShaders.ProjectionMat = glGetUniformLocation(commonShaders.Index, "projectionMat");
	// texture
	commonShaders.TexSampler = glGetUniformLocation(commonShaders.Index, "modelTexture");
	commonShaders.UseTexture = glGetUniformLocation(commonShaders.Index, "useTexture");
	// material
	commonShaders.MaterialAmbient = glGetUniformLocation(commonShaders.Index, "material.ambient");
	commonShaders.MaterialDiffuse = glGetUniformLocation(commonShaders.Index, "material.diffuse");
	commonShaders.MaterialSpecular = glGetUniformLocation(commonShaders.Index, "material.specular");
	commonShaders.MaterialShininess = glGetUniformLocation(commonShaders.Index, "material.shininess");

	// light
	// directional light
	commonShaders.DirLightColor = glGetUniformLocation(commonShaders.Index, "dirLight.color");
	commonShaders.DirLightDirection = glGetUniformLocation(commonShaders.Index, "dirLight.direction");

	// point light
	commonShaders.PointLightColor = glGetUniformLocation(commonShaders.Index, "pointLight.color");
	commonShaders.PointLightPosition = glGetUniformLocation(commonShaders.Index, "pointLight.position");
	commonShaders.PointLightConstant = glGetUniformLocation(commonShaders.Index, "pointLight.constant");
	commonShaders.PointLightLinear = glGetUniformLocation(commonShaders.Index, "pointLight.linear");
	commonShaders.PointLightQuadratic = glGetUniformLocation(commonShaders.Index, "pointLight.quadratic");
	commonShaders.PointLightUse = glGetUniformLocation(commonShaders.Index, "pointLight.use");

	// spot light
	commonShaders.SpotLightColor = glGetUniformLocation(commonShaders.Index, "spotLight.color");
	commonShaders.SpotLightPosition = glGetUniformLocation(commonShaders.Index, "spotLight.position");
	commonShaders.SpotLightDirection = glGetUniformLocation(commonShaders.Index, "spotLight.direction");
	commonShaders.SpotLightCutOff = glGetUniformLocation(commonShaders.Index, "spotLight.cutOff");
	commonShaders.SpotLightUse = glGetUniformLocation(commonShaders.Index, "spotLight.use");

	commonShaders.ViewPos = glGetUniformLocation(commonShaders.Index, "viewPos");  // view position

	// fog
	commonShaders.FogColor = glGetUniformLocation(commonShaders.Index, "fogColor");
	commonShaders.FogDensity = glGetUniformLocation(commonShaders.Index, "fogDensity");
	commonShaders.UseFog = glGetUniformLocation(commonShaders.Index, "useFog");

	// sprite animation
	commonShaders.NumImages = glGetUniformLocation(commonShaders.Index, "numImages");
	commonShaders.NumColumns = glGetUniformLocation(commonShaders.Index, "numColumns");
	commonShaders.CurrImage = glGetUniformLocation(commonShaders.Index, "currImage");

	// sprite shift
	commonShaders.Shift = glGetUniformLocation(commonShaders.Index, "shift");


	commonShaders.Resolution = glGetUniformLocation(commonShaders.Index, "resolution");

	commonShaders.IsUi = glGetUniformLocation(commonShaders.Index, "isUi");

	CHECK_GL_ERROR();

	assert(commonShaders.Pos != -1);
	commonShaders.Initialized = true;

	// Color shaders
	std::vector<GLuint> noLightShaderList;
	noLightShaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "Color.vert"));
	noLightShaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "Color.frag"));
	colorShaders.Index = pgr::createProgram(noLightShaderList);

	colorShaders.Pos = glGetAttribLocation(colorShaders.Index, "position");
	colorShaders.TexCoord = glGetAttribLocation(colorShaders.Index, "inputTexCoord");
	colorShaders.Color = glGetAttribLocation(colorShaders.Index, "inputColor");

	// position
	colorShaders.ModelMat = glGetUniformLocation(colorShaders.Index, "modelMat");
	colorShaders.ViewMat = glGetUniformLocation(colorShaders.Index, "viewMat");
	colorShaders.ProjectionMat = glGetUniformLocation(colorShaders.Index, "projectionMat");
	// texture
	colorShaders.TexSampler = glGetUniformLocation(colorShaders.Index, "modelTexture");
	colorShaders.UseTexture = glGetUniformLocation(colorShaders.Index, "useTexture");
	// fog
	colorShaders.FogColor = glGetUniformLocation(colorShaders.Index, "fogColor");
	colorShaders.FogDensity = glGetUniformLocation(colorShaders.Index, "fogDensity");
	colorShaders.UseFog = glGetUniformLocation(colorShaders.Index, "useFog");

	colorShaders.Resolution = glGetUniformLocation(colorShaders.Index, "resolution");
}

void ServiceClass::CleanupShaderPrograms(void) {

	pgr::deleteProgramAndShaders(commonShaders.Index);
}

void ServiceClass::Update()
{
	// update object states
	for (auto& it : objects) 
	{
		if (it.Initialized)
		{
			it.Update(currentFrame, deltaTime);
			if (it.Name == "Butterfly")
			{
				for (auto& j : it.Instances)
				{
					j.Rotate(1.0f, 1.0f);
					j.Move(0.1f, 1.0f);
				}
			}
		}
	}
}

void ServiceClass::DrawScene(void)
{
	// update cameras
	if (activeCamera == dynamicCamera)
	{
		cameras[dynamicCamera].Position = objects[butterflyPosition].Instances[0].Position;
		cameras[dynamicCamera].Yaw = 270.0f - objects[butterflyPosition].Instances[0].Rotation.y;
	}

	glm::mat4 view = glm::lookAt(cameras[activeCamera].Position, cameras[activeCamera].Position + cameras[activeCamera].Front, cameras[activeCamera].Up);

	glUseProgram(commonShaders.Index);

	// direct light
	glUniform3f(commonShaders.DirLightColor, lights[dirLightPos].Color.r, lights[dirLightPos].Color.g, lights[dirLightPos].Color.b);
	glUniform3f(commonShaders.DirLightDirection, lights[dirLightPos].Directon.x, lights[dirLightPos].Directon.y, lights[dirLightPos].Directon.z);

	// point light
	glUniform3f(commonShaders.PointLightColor, lights[pointLightPos].Color.r, lights[pointLightPos].Color.g, lights[pointLightPos].Color.b);
	glUniform3f(commonShaders.PointLightPosition, lights[pointLightPos].Position.x, lights[pointLightPos].Position.y, lights[pointLightPos].Position.z);
	glUniform1f(commonShaders.PointLightConstant, lights[pointLightPos].Constant);
	glUniform1f(commonShaders.PointLightLinear, lights[pointLightPos].Linear + 0.05f*sin((glutGet(GLUT_ELAPSED_TIME)/300.0f)));
	glUniform1f(commonShaders.PointLightQuadratic, lights[pointLightPos].Quadratic);
	glUniform1i(commonShaders.PointLightUse, lights[pointLightPos].Use);

	// spot light
	glUniform3f(commonShaders.SpotLightColor, lights[spotLightPos].Color.r, lights[spotLightPos].Color.g, lights[spotLightPos].Color.b);
	glUniform3f(commonShaders.SpotLightPosition, cameras[activeCamera].Position.x, cameras[activeCamera].Position.y, cameras[activeCamera].Position.z);
	glUniform3f(commonShaders.SpotLightDirection, cameras[activeCamera].Front.x, cameras[activeCamera].Front.y, cameras[activeCamera].Front.z);
	glUniform1f(commonShaders.SpotLightCutOff, glm::cos(glm::radians(lights[spotLightPos].CutOff)));
	glUniform1i(commonShaders.SpotLightUse, lights[spotLightPos].Use);


	glUniform3f(commonShaders.ViewPos, cameras[activeCamera].Position.x, cameras[activeCamera].Position.y, cameras[activeCamera].Position.z);

	// fog light
	glUniform4f(commonShaders.FogColor, fogColor.r, fogColor.g, fogColor.b, 1.0f);
	glUniform1f(commonShaders.FogDensity, fogDensity*fogMultiplier);
	glUniform1i(commonShaders.UseFog, useFog);
	glUniform2f(commonShaders.Resolution, (float)windowWidth, (float)windowHeight);

	// fog color
	glUseProgram(colorShaders.Index);
	glUniform4f(colorShaders.FogColor, fogColor.r, fogColor.g, fogColor.b, 1.0f);
	glUniform1f(colorShaders.FogDensity, fogDensity);
	glUniform1i(colorShaders.UseFog, useFog);
	glUniform2f(colorShaders.Resolution, (float)windowWidth, (float)windowHeight);

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	for (auto& it : objects)  // First draw objects, that doesn't use blending
	{
		if (!it.UseBlend)
		{
			if (it.Name != "Skybox") it.Draw(view, projection, activeCamera);
			else it.Draw(glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f) + cameras[activeCamera].Front, cameras[activeCamera].Up), projection, activeCamera);
		}
	}
	for (auto& it : objects)  // Then draw objects, that does use blending
	{
		if (it.UseBlend)
		{
			if (it.Name == "GrassStems" || it.Name == "Fire")
			{
				for (auto& i : it.Instances) i.Transform(i.Position, glm::vec3(i.Rotation.x, 90.0f - cameras[activeCamera].Yaw, i.Rotation.z), i.Scale);
			}
			it.Draw(view, projection, activeCamera);
		}
	}
}

void ServiceClass::InitApplication()
{
	// init OpenGL
	// - all programs (shaders), buffers, textures, ...
	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	LoadShaderPrograms();
	CHECK_GL_ERROR();

	cameras.push_back(Camera());  // Player
	cameras.back().Position = glm::vec3(0.0f, 2.0f, -2.0f);
	activeCamera = 0;
	cameras.push_back(Camera());  // Static 1
	cameras.back().Position = glm::vec3(10.0f, 5.0f, 10.0f);
	cameras.back().Yaw = 235.0f;
	cameras.back().Pitch = -12.0f;
	cameras.push_back(Camera());  // Static 2
	cameras.back().Position = glm::vec3(0.0f, 2.0f, -5.0f);
	cameras.push_back(Camera()); // Dynamic
	dynamicCamera = cameras.size() - 1;

	projection = glm::perspective(glm::radians(Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	// Lights
	// Point Light
	lights.push_back(Light());
	pointLightPos = lights.size() - 1;
	lights.back().Color = glm::vec4(1.0f, 0.7f, 0.6f, 1.0f);
	lights.back().Position = glm::vec3(0.0f, 2.7f, 0.0f);

	// Direct Light
	lights.push_back(Light());
	dirLightPos = lights.size() - 1;
	lights.back().Directon = glm::vec3(-10.0f, -8.0f, 15.0f);

	// Spot Light
	lights.push_back(Light());
	spotLightPos = lights.size() - 1;
	lights.back().Use = false;
	

	CHECK_GL_ERROR();
	ServiceClass::LoadModels();
	CHECK_GL_ERROR();


	ServiceClass::LoadConfig();
	CHECK_GL_ERROR();
	// init your Application
	// - setup the initial application state
}

void ServiceClass::FinalizeApplication(void)
{
	for (auto & i : objects)
	{
		glDeleteVertexArrays(1, &i.Vao.Index);
		glDeleteBuffers(1, &i.Ebo.Index);
		glDeleteBuffers(1, &i.Vbo.Index);
		if (i.Texture != 0) glDeleteTextures(1, &i.Texture);
	}

	lights.clear();
	objects.clear();
	cameras.clear();
	bf_vert.clear();
	bf_ind.clear();

	keysPressed.clear();
	specialKeysPressed.clear();
	mouseKeysPressed.clear();

	// delete shaders
	CleanupShaderPrograms();
}

void ServiceClass::LoadModels()
{
	objects.push_back(GameObject(&colorShaders, "Crosshair"));
	objects.back().NewModel(
		{ 0.0f,   0.0f,  0.0f,
				  -0.005f, -0.01f, 0.0f,
				   0.005f, -0.01f, 0.0f }, {},
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	objects.back().NewInstance(true);

	objects.push_back(GameObject(&commonShaders, "Revolver"));
	objects.back().LoadFile("data/revolver.obj");
	objects.back().NewInstance(true);
	objects.back().Instances.back().Transform(glm::vec3(0.5f, -0.8f, 0.4f), glm::vec3(0.0f, 264.0f, 7.0f), glm::vec3(1.5f, 1.5f, 1.5f));

	objects.push_back(GameObject(&commonShaders, "Barrel"));
	objects.back().ObjectMaterial.shininess = 512.0f;
	objects.back().LoadFile("data/barrel.obj");
	objects.back().SetCollision(1.0f);
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(8.0f, -0.5f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(1.0f, -0.5f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(2.0f, -0.5f, 6.3f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(0.3f, -0.5f, 6.3f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	objects.push_back(GameObject(&commonShaders, "Fence"));
	objects.back().LoadFile("data/Fence.obj");
	float fenceCount = 13.0f;
	float fenceDistance = 10.0f;
	for (float i = 0.0f; i < fenceCount; i += 1.0f)
	{
		objects.back().NewInstance();
		objects.back().Instances.back().Transform(glm::vec3(fenceDistance * sin(glm::radians(i / fenceCount * 360.0f)), -0.3f,
			fenceDistance * cos(glm::radians(i / fenceCount * 360.0f))),
			glm::vec3(0.0f, i / fenceCount * 360.0f, 0.0f),
			2.5f * glm::vec3(1.0f));
	}

	objects.push_back(GameObject(&commonShaders, "Grass"));
	objects.back().LoadFile("data/Grass.obj");
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 200.0f * glm::vec3(1.0f, 0.0f, 1.0f));

	objects.push_back(GameObject(&commonShaders, "Bench"));
	objects.back().ObjectMaterial.diffuse = glm::vec3(0.2f);
	objects.back().SetCollision(0.5f);
	objects.back().LoadFile("data/Bench.obj");
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(-8.5f, -0.55f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 2.3f * glm::vec3(1.0f));

	objects.push_back(GameObject(&commonShaders, "Lamp"));
	objects.back().SetCollision(0.3f);
	objects.back().LoadFile("data/Lamp.obj");
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(0.0f, 0.3f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 2.5f * glm::vec3(1.0f, 0.7f, 1.0f));
	for (int i = 0; i < objects.back().Instances.size(); i++)
		objects.back().Instances[i].StencilId = lightButtonId;

	objects.push_back(GameObject(&commonShaders, "Tree"));
	objects.back().LoadFile("data/Tree.obj");
	float treeCount = 40.0f;
	float treeDistance = 20.0f;
	for (int j = 0; j < 4; j++)  // Generated trees in 4 rows with slightly randomizied diension and positions
	{
		for (float i = 0.0f; i < treeCount; i += 1.0f)
		{
			float size_w = 2.3f + (float)rand() / RAND_MAX * 0.4f;
			float size_h = 2.3f + (float)rand() / RAND_MAX * 0.4f;
			float pos_offset = (float)rand() / RAND_MAX * 3.0f - 1.5f;
			float distance_offset = 0.95f + (float)rand() / RAND_MAX * 0.1f;
			objects.back().NewInstance();
			objects.back().Instances.back().Transform(glm::vec3((treeDistance + j * 5.0f) * sin(glm::radians(i / treeCount * 360.0f + pos_offset)) * distance_offset, 1.0f,
				(treeDistance + j * 5.0f) * cos(glm::radians(i / treeCount * 360.0f + pos_offset))) * distance_offset,
				glm::vec3(0.0f, i / treeCount * 360.0f, 0.0f),
				glm::vec3(size_w, size_h, size_w));
		}
	}

	objects.push_back(GameObject(&commonShaders, "Stand"));
	objects.back().LoadFile("data/Stand.obj");
	objects.back().BaseColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(0.0f, 1.2f, -12.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 2.7f, 3.0f));

	objects.push_back(GameObject(&colorShaders, "Skybox"));
	skyboxPosition = objects.size() - 1;
	objects.back().LoadFile("data/Skybox.obj");
	objects.back().BaseColor = glm::vec4(1.0f);
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 50.0f * glm::vec3(1.0f, 1.0f, 1.0f));

	objects.push_back(GameObject(&commonShaders, "Button"));
	objects.back().LoadFile("data/Button.obj");
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(1.8f, 1.1f, -9.8f), glm::vec3(0.0f, 0.0f, 0.0f), 0.2f * glm::vec3(1.0f, 1.0f, 1.0f));
	for (int i = 0; i < objects.back().Instances.size(); i++)
		objects.back().Instances[i].StencilId = resetButtonId;

	objects.push_back(GameObject(&commonShaders, "Target"));
	objects.back().ObjectMaterial.diffuse = glm::vec3(1.0f);
	objects.back().ObjectMaterial.specular = glm::vec3(1.0f);
	targetPosition = objects.size() - 1;
	objects.back().LoadFile("data/Target.obj");
	for (float i = -2.0f; i <= 2.0f; i += 0.8f)
	{
		objects.back().NewInstance();
		objects.back().Instances.back().Transform(glm::vec3(i, 1.5f, -12.5f), glm::vec3(0.0f, 0.0f, 0.0f), 0.5f * glm::vec3(1.0f, 1.0f, 1.0f));
	}
	for (int i = 0; i < objects.back().Instances.size(); i++)
		objects.back().Instances[i].StencilId = firstTargetId + i;

	objects.push_back(GameObject(&commonShaders, "GrassStems"));
	objects.back().ObjectMaterial.ambient = glm::vec3(0.7f);
	objects.back().LoadSprite("data/GrassStems.png", 4, 4);
	float grassCount = 10.0f;
	float grassDistance = 12.0f;
	for (int j = 3; j > 0; j--)  // generate 3 rows of grass stems with slighty randomizied values
	{
		for (float i = 0.0f; i < grassCount; i += 1.0f)
		{
			float size_w = 1.9f + (float)rand() / RAND_MAX * 0.2f;
			float size_h = 1.9f + (float)rand() / RAND_MAX * 0.2f;
			float pos_offset = 15.0f + (float)rand() / RAND_MAX * 330.0f / grassCount;
			float distance_offset = 0.95f + (float)rand() / RAND_MAX * 0.1f;
			objects.back().NewInstance(false, 250 + rand()%100);
			objects.back().Instances.back().Transform(
				glm::vec3((grassDistance + j * 1.0f) * sin(glm::radians(i / grassCount * 360.0f + pos_offset)) * distance_offset,
					      -0.5f,
				          (grassDistance + j * 1.0f) * cos(glm::radians(i / grassCount * 360.0f + pos_offset))) * distance_offset,
				glm::vec3(0.0f, i / grassCount * 360.0f, 0.0f),
				glm::vec3(size_w, size_h, size_w));
		}
	}

	objects.push_back(GameObject(&commonShaders, "Fire"));
	firePosition = objects.size() - 1;
	objects.back().ObjectMaterial.ambient = glm::vec3(1.0f);
	objects.back().ObjectMaterial.shininess = 512.0f;
	objects.back().LoadSprite("data/Fire.png", 9, 5);
	objects.back().NewInstance(false, 100);
	objects.back().Instances.back().Transform(glm::vec3(0.0f, 2.4f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f * glm::vec3(1.0f, 1.0f, 1.0f));

	objects.push_back(GameObject(&commonShaders, "Screen"));
	objects.back().LoadFile("data/Screen.obj");
	objects.back().NewInstance();
	objects.back().Instances.back().Transform(glm::vec3(0.0f, 0.4f, -9.3f), glm::vec3(0.0f), 2.0f * glm::vec3(1.3f, 1.0f, 1.0f));

	objects.push_back(GameObject(&commonShaders, "Banner"));
	objects.back().LoadSprite("data/Banner.png");
	objects.back().ObjectMaterial.ambient = glm::vec3(1.0f);
	objects.back().NewInstance(false, 100);
	objects.back().Instances.back().Transform(glm::vec3(0.0f, 0.4f, -9.3f), glm::vec3(0.0f), 1.0f * glm::vec3(5.0f, 1.0f, 1.0f));
	objects.back().Instances.back().ShiftSpeed = glm::vec2(-0.01f, 0.0f);

	objects.push_back(GameObject(&colorShaders, "Butterfly"));
	objects.back().NewModel(bf_vert, bf_ind, glm::vec4(0.7f, 0.7f, 1.0f, 1.0f), 4);
	butterflyPosition = objects.size() - 1;
	float butterflyCount = 6.0f;
	for (float i = 0.0f; i < butterflyCount; i += 1.0f)  // Generate few random butterflies
	{
		objects.back().NewInstance(false, 80+rand()%40);
		objects.back().Instances.back().Transform(glm::vec3(-10.0f+(float)(rand()%200)/10.0f, 0.5f+(float)(rand()%200)*0.01f, -10.0f + rand() % 200 / 10.0f),
												  glm::vec3(0.0f, (float)(rand()%360), 0.0f),
												  glm::vec3(1.0f, 1.0f, 1.0f) * 0.1f);
		objects.back().Instances.back().ChangeColor(glm::vec4(0.5f + (float)(rand() % 50) * 0.01f,
			                                                  0.5f + (float)(rand() % 50) * 0.01f,
			                                                  0.5f + (float)(rand() % 50) * 0.01f, 1.0f));
	}

	CHECK_GL_ERROR();
}

void ServiceClass::ProccessInput()
{
	// camera
	if (keysPressed['v'])
	{
		keysPressed['v'] = false;
		activeCamera++;
		if (activeCamera >= cameras.size() || specialKeysPressed[GLUT_KEY_SHIFT_L]) activeCamera = 0;
		if(activeCamera == 0)
		{
			objects[butterflyPosition].Instances[0].Draw = true;
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(windowWidthHalf, windowHeightHalf);
			glutPostRedisplay();
		}
		else
		{
			Zoom = ZoomedOut;

			// Unaim weapon
			for (auto& object : objects)
			{
				if (object.Name == "Revolver")
				{
					for (auto& weapon : object.Instances)
					{
						if (weapon.Ui) weapon.Transform(glm::vec3(0.5f, -0.8f, 0.4f), glm::vec3(0.0f, 264.0f, 7.0f), glm::vec3(1.5f, 1.5f, 1.5f));
					}
				}
			}

			lights[spotLightPos].Use = false;
			if (activeCamera == dynamicCamera) objects[butterflyPosition].Instances[0].Draw = false;
			else
			{
				objects[butterflyPosition].Instances[0].Draw = true;
				glutSetCursor(GLUT_CURSOR_INHERIT);
			}
		}
		projection = glm::perspective(glm::radians(Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
		std::cout << "Active camera: " << activeCamera << "\n";
	}

	// movement
	if (activeCamera == 0)
	{
		float movementSpeed;
		if (specialKeysPressed[GLUT_KEY_SHIFT_L]) movementSpeed = cameras[0].SpeedSprint;
		else movementSpeed = cameras[0].Speed;
		glm::vec3 newPos = cameras[0].Position;
		if (keysPressed['w'] || specialKeysPressed[GLUT_KEY_UP]) newPos += glm::normalize(glm::vec3(cameras[0].Front.x, 0.0f, cameras[0].Front.z)) * (movementSpeed * deltaTime);
		if (keysPressed['s'] || specialKeysPressed[GLUT_KEY_DOWN]) newPos -= glm::normalize(glm::vec3(cameras[0].Front.x, 0.0f, cameras[0].Front.z)) * (movementSpeed * deltaTime);
		if (keysPressed['a'] || specialKeysPressed[GLUT_KEY_LEFT]) newPos -= glm::normalize(glm::cross(glm::vec3(cameras[0].Front.x, 0.0f, cameras[0].Front.z), cameras[0].Up)) * (movementSpeed * deltaTime);
		if (keysPressed['d'] || specialKeysPressed[GLUT_KEY_RIGHT]) newPos += glm::normalize(glm::cross(glm::vec3(cameras[0].Front.x, 0.0f, cameras[0].Front.z), cameras[0].Up)) * (movementSpeed * deltaTime);
		
		// Collision
		if (activeCollisions)
		{
			bool collided = false;
			for (auto& it : objects)
			{
				if (!it.UseCollision) continue;
				if (it.GetCollision(newPos, 0.2f))
				{
					collided = true;
					break;
				}
			}
			if (glm::distance(glm::vec3(0.0f), newPos) >= sceneRadius) collided = true;
			if (!collided) cameras[0].Position = newPos;
		}
		else cameras[0].Position = newPos;
	}

	// Collision swap
	if (keysPressed['k'])
	{
		keysPressed['k'] = false;
		activeCollisions = !activeCollisions;
	}

	// Fog
	if (keysPressed['m'])
	{
		keysPressed['m'] = false;
		useFog = !useFog;
	}

	// Flashlight
	if (keysPressed['f'])
	{
		keysPressed['f'] = false;
		if(activeCamera == 0) lights[spotLightPos].Use = !lights[spotLightPos].Use;
	}
	
	// Reset
	if (keysPressed['r']) ServiceClass::RestartApplication();

	/*	FREE CAMERA MOVEMENT
	if (keysPressed['w']) cameras[0].Position += (movementSpeed * deltaTime) * cameras[0].Front;
	if (keysPressed['s']) cameras[0].Position -= (movementSpeed * deltaTime) * cameras[0].Front;
	if (keysPressed['a']) cameras[0].Position -= glm::normalize(glm::cross(cameras[0].Front, cameras[0].Up)) * (movementSpeed * deltaTime);
	if (keysPressed['d']) cameras[0].Position += glm::normalize(glm::cross(cameras[0].Front, cameras[0].Up)) * (movementSpeed * deltaTime);
	*/
}

void ServiceClass::ParseParameter(std::map<std::string, std::string>* inputParameters, int* variable, const std::string name, const int defaultVal)
{
	try
	{
		if (inputParameters->find(name) != inputParameters->end()) *variable = std::stoi((*inputParameters)[name]);
	}
	catch (std::exception& e)
	{
		std::cout << "Wrong value in configuration file for '" << name << "'. Setting default value (" << defaultVal << "). [" << e.what() << "]\n";
		*variable = defaultVal;
	}
}

void ServiceClass::ParseParameter(std::map<std::string, std::string>* inputParameters, float* variable, const std::string name, const float defaultVal)
{
	try
	{
		if (inputParameters->find(name) != inputParameters->end()) *variable = std::stof((*inputParameters)[name]);
	}
	catch (std::exception& e)
	{
		std::cout << "Wrong value in configuration file for '" << name << "'. Setting default value (" << defaultVal << "). [" << e.what() << "]\n";
		*variable = defaultVal;
	}
}

void ServiceClass::LoadConfig()
{
	
	std::map<std::string, std::string> inputParameters;

	std::fstream file;  // Load file
	file.open("config.ini", std::ios::in);
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (line[0] == '#' || std::count(line.begin(), line.end(), '=') != 1 ) continue;  // Skip non-parameter lines

			std::string temp = line;  // Remove whitespaces
			line = "";
			for (char c : temp)
			{
				if (!std::isspace(c)) line += c;
			}

			std::stringstream ss(line);  // Split left and right side
			std::string first;
			std::string second;
			std::getline(ss, first, '=');
			std::getline(ss, second, '=');
			inputParameters.insert(std::make_pair(first, second));
		}
		file.close();
	}
	glm::vec3 temp3f(0.0f);
	float temp1f = 0.0f;
	int temp1i = 0;
	
	// Resolution
	ServiceClass::ParseParameter(&inputParameters, &temp1i, "windowWidth", 800);
	windowWidth = GlobFunc::Clamp(temp1i, 256, 3840);
	ServiceClass::ParseParameter(&inputParameters, &temp1i, "windowHeight", 800);
	windowHeight = GlobFunc::Clamp(temp1i, 256, 2160);
	windowWidthHalf = windowWidth / 2;
	windowHeightHalf = windowHeight / 2;
	glutReshapeWindow(windowWidth, windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	// Fog
	ServiceClass::ParseParameter(&inputParameters, &temp3f.r, "fogColorR", 0.9f);
	ServiceClass::ParseParameter(&inputParameters, &temp3f.g, "fogColorG", 0.9f);
	ServiceClass::ParseParameter(&inputParameters, &temp3f.b, "fogColorB", 0.9f);
	fogColor = GlobFunc::Clamp(temp3f, 0.0f, 1.0f);
	ServiceClass::ParseParameter(&inputParameters, &temp1f, "fogDensity", 0.05f);
	fogDensity = GlobFunc::Clamp(temp1f, 0.0f, 1.0f);

	// Lights
	ServiceClass::ParseParameter(&inputParameters, &temp3f.r, "dirLightColorR", 1.0f);
	ServiceClass::ParseParameter(&inputParameters, &temp3f.g, "dirLightColorG", 1.0f);
	ServiceClass::ParseParameter(&inputParameters, &temp3f.b, "dirLightColorB", 1.0f);
	lights[dirLightPos].Color = GlobFunc::Clamp(temp3f, 0.0f, 1.0f);

	ServiceClass::ParseParameter(&inputParameters, &temp3f.r, "pointLightColorR", 1.0f);
	ServiceClass::ParseParameter(&inputParameters, &temp3f.g, "pointLightColorG", 1.0f);
	ServiceClass::ParseParameter(&inputParameters, &temp3f.b, "pointLightColorB", 1.0f);
	lights[pointLightPos].Color = GlobFunc::Clamp(temp3f, 0.0f, 1.0f);

	ServiceClass::ParseParameter(&inputParameters, &temp3f.r, "spotLightColorR", 1.0f);
	ServiceClass::ParseParameter(&inputParameters, &temp3f.g, "spotLightColorG", 1.0f);
	ServiceClass::ParseParameter(&inputParameters, &temp3f.b, "spotLightColorB", 1.0f);
	lights[spotLightPos].Color = GlobFunc::Clamp(temp3f, 0.0f, 1.0f);
	ServiceClass::ParseParameter(&inputParameters, &temp1f, "cutOff", 1.0f);
	lights[spotLightPos].CutOff = GlobFunc::Clamp(temp1f, 5.0f, 20.0f);
	
	inputParameters.clear();
}

void ServiceClass::RestartApplication()
{
	// Pressed keys
	for (auto& it : keysPressed) it.second = false;
	for (auto& it : specialKeysPressed) it.second = false;
	for (auto& it : mouseKeysPressed) it.second = false;

	// Camera
	activeCamera = 0;
	cameras[0].Position = glm::vec3(0.0f, 2.0f, -2.0f);
	cameras[0].Yaw = -90.0f;
	cameras[0].Pitch = 0.0f;
	glutWarpPointer(windowWidthHalf, windowHeightHalf);
	deltaX = 0;
	deltaY = 0;
	glutSetCursor(GLUT_CURSOR_NONE);

	// Draw everything
	for (auto& it : objects[targetPosition].Instances) it.Draw = true;
	for (auto& it : objects[firePosition].Instances) it.Draw = true;

	// Reset default light usage
	lights[pointLightPos].Use = true;
	lights[spotLightPos].Use = false;

	// Unaim weapon
	for (auto& object : objects)
	{
		if (object.Name == "Revolver")
		{
			for (auto& weapon : object.Instances)
			{
				if (weapon.Ui) weapon.Transform(glm::vec3(0.5f, -0.8f, 0.4f), glm::vec3(0.0f, 264.0f, 7.0f), glm::vec3(1.5f, 1.5f, 1.5f));
			}
		}
	}

	// Restart camera specific values
	objects[butterflyPosition].Instances[0].Draw = true;
	Zoom = ZoomedOut;
	projection = glm::perspective(glm::radians(Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	// Others
	activeCollisions = true;
	useFog = false;

	// Load config file values
	ServiceClass::LoadConfig();

	glutPostRedisplay();
	std::cout << "\nReloaded application\n";
}