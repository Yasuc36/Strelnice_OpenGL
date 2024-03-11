#include "GameObject.h"

GameObject::GameObject(CommonShaders* shaders, const std::string name) : Name(name)
{
	BaseColor = glm::vec4(1.0f);
	ObjectMaterial.ambient = glm::vec3(0.5f);
	ObjectMaterial.diffuse = glm::vec3(0.5f);
	ObjectMaterial.specular = glm::vec3(0.5f);
	ObjectMaterial.shininess = 256.0f;

	Texture = 0;

	NumVertices = 0;
	NumTriangles = 0;
	NumFrames = 1;
	NumImages = 1;
	NumColumns = 1;

	Shaders = shaders;

	Vbo = VBO();
	Ebo = EBO();
	Vao = VAO();

	Radius = 0.0f;

	BlendFirst = GL_ONE;
	BlendSecond = GL_ONE;
	UseBlend = false;

	UseTexture = false;
	UseEBO = true;
	UseCollision = false;
	HaveNormals = false;
	Initialized = false;

	Instances.clear();
}

GameObject::~GameObject()
{
	Instances.clear();
}

bool GameObject::LoadFile(const std::string path, unsigned int numFrames)
{
	// INIT
	Assimp::Importer importer;

	// Unitize object in size (scale the model to fit into (-1..1)^3)
	importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);

	// Load asset from the file - you can play with various processing steps
	const aiScene* scn = importer.ReadFile(path.c_str(), 0
		| aiProcess_Triangulate             // Triangulate polygons (if any).
		| aiProcess_PreTransformVertices    // Transforms scene hierarchy into one root with geometry-leafs only. For more see Doc.
		| aiProcess_GenSmoothNormals        // Calculate normals per vertex.
		| aiProcess_JoinIdenticalVertices);
	
	// abort if the loader fails
	if (scn == NULL) {
		std::cerr << "assimp error: " << importer.GetErrorString() << std::endl;
		return false;
	}

	// some formats store whole scene (multiple meshes and materials, lights, cameras, ...) in one file, we cannot handle that in our simplified example
	if (scn->mNumMeshes != 1) {
		std::cerr << "this simplified loader can only process files with only one mesh" << std::endl;
		return false;
	}

	// in this phase we know we have one mesh in our loaded scene, we can directly copy its data to OpenGL ...
	const aiMesh* mesh = scn->mMeshes[0];
	NumVertices = mesh->mNumVertices;
	NumTriangles = mesh->mNumFaces;
	NumFrames = numFrames;


	// Buffers
	Vbo.LoadObject(mesh);
	Ebo.LoadObject(mesh);
	Vao.ConnectBuffers(Vbo.Index, Ebo.Index);
	UseEBO = true;


	// Material
	// copy the material info
	const aiMaterial* mat = scn->mMaterials[mesh->mMaterialIndex];
	aiColor4D color;
	aiString name;
	aiReturn retValue = AI_SUCCESS;

	mat->Get(AI_MATKEY_NAME, name);

	if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color)) != AI_SUCCESS) color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
	ObjectMaterial.diffuse = glm::vec3(color.r, color.g, color.b);

	if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &color)) != AI_SUCCESS) color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
	ObjectMaterial.ambient = glm::vec3(color.r, color.g, color.b);

	if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &color)) != AI_SUCCESS) color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
	ObjectMaterial.specular = glm::vec3(color.r, color.g, color.b);

	BaseColor = {color.r, color.g, color.b, color.a};

	ai_real shininess, strength;
	unsigned int max;
	max = 1;
	if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS, &shininess, &max)) != AI_SUCCESS)
		shininess = 1.0f;
	max = 1;
	if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS_STRENGTH, &strength, &max)) != AI_SUCCESS)
		strength = 1.0f;
	ObjectMaterial.shininess = shininess * strength;
	Texture = 0;


	// Texture
	// load texture image
	if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		UseTexture = true;
		// get texture name 
		aiString texturePath;

		aiReturn texFound = mat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
		std::string textureName = texturePath.data;

		size_t found = path.find_last_of("/\\");
		// insert correct texture file path 
		if (found != std::string::npos) { // not found
			textureName.insert(0, path.substr(0, found + 1));
		}
		std::cout << "Loading texture file: " << textureName << std::endl;
		Texture = pgr::createTexture(textureName);
	}
	else UseTexture = false;
	CHECK_GL_ERROR();


	// Shader
	glBindVertexArray(Vao.Index);
	glEnableVertexAttribArray(Shaders->Pos);
	glVertexAttribPointer(Shaders->Pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
	CHECK_GL_ERROR();

	HaveNormals = true;
	glEnableVertexAttribArray(Shaders->Normal);
	glVertexAttribPointer(Shaders->Normal, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3 * sizeof(float) * mesh->mNumVertices));
	CHECK_GL_ERROR();

	glDisableVertexAttribArray(Shaders->Color);
	// following line is problematic on AMD/ATI graphic cards
	// -> if you see black screen (no objects at all) than try to set color manually in vertex shader to see at least something
	glVertexAttrib4f(Shaders->Color, color.r, color.g, color.b, color.a);
	CHECK_GL_ERROR();

	glEnableVertexAttribArray(Shaders->TexCoord);
	glVertexAttribPointer(Shaders->TexCoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)(6 * sizeof(float) * mesh->mNumVertices));
	CHECK_GL_ERROR();

	glBindVertexArray(0);

	Initialized = true;
	return true;
}

bool GameObject::LoadSprite(const std::string path, unsigned int numImages, unsigned int numColumns)
{
	// SETUP PHASE	
	UseBlend = true;
	BlendFirst = GL_SRC_ALPHA;
	BlendSecond = GL_ONE_MINUS_SRC_ALPHA;
	NumImages = numImages;
	NumColumns = numColumns;
	std::vector<float> verticesUv = 
	{
		//  x	   y     z     u     v	
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
	};
	std::vector<unsigned int> indices =
	{
		0, 1, 2,
		1, 2, 3
	};
	NumVertices = verticesUv.size() / 5;
	NumTriangles = indices.size() / 3;

	// Texture
	Texture = pgr::createTexture(path);
	// abort if the loader fails
	if (Texture == 0)
	{
		std::cout << "Could'nt load texture " << path << ".\n";
		return false;
	}
	CHECK_GL_ERROR();

	// Buffers
	Vao.ConnectBuffers(Vbo.Index, Ebo.Index);
	Vbo.SetData(verticesUv);
	Ebo.SetData(indices);
	CHECK_GL_ERROR();

	// Shaders
	glBindVertexArray(Vao.Index);
	glEnableVertexAttribArray(Shaders->Pos);
	glVertexAttribPointer(Shaders->Pos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0); // Stride (xyzuv)
	glEnableVertexAttribArray(Shaders->TexCoord);
	glVertexAttribPointer(Shaders->TexCoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Stride (xyzuv) + offset (xyz)
	CHECK_GL_ERROR();

	// EXIT PHASE
	glBindVertexArray(0);
	UseTexture = true;
	Initialized = true;
	CHECK_GL_ERROR();
	return true;
}


bool GameObject::NewModel(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, glm::vec4 baseColor, unsigned int numFrames)
{
	// SETUP PHASE
	NumFrames = numFrames;
	if (vertices.empty()) return false;
	NumVertices = vertices.size() / 3;
	if (!indices.empty()) NumTriangles = indices.size() / 3;
	else NumTriangles = vertices.size() / 9;  // 3 vertices in 3D = 3 * 3 = 9
	BaseColor = baseColor;

	// BUFFERS
	if (!indices.empty())
	{
		Vao.ConnectBuffers(Vbo.Index, Ebo.Index);
		Vbo.SetData(vertices);
		Ebo.SetData(indices);
		UseEBO = true;
	}
	else
	{
		Vao.ConnectBuffers(Vbo.Index);
		Vbo.SetData(vertices);
		UseEBO = false;
	}
	glBindVertexArray(Vao.Index);
	CHECK_GL_ERROR();

	// SHADERS
	glEnableVertexAttribArray(Shaders->Pos);
	glVertexAttribPointer(Shaders->Pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDisableVertexAttribArray(Shaders->Color);
	glVertexAttrib4f(Shaders->Color, BaseColor.r, BaseColor.g, BaseColor.b, BaseColor.a);
	CHECK_GL_ERROR();

	// EXIT PHASE
	glBindVertexArray(0);
	UseTexture = false;
	Initialized = true;
	return true;

}

void GameObject::NewInstance(bool ui, unsigned int frameSpeed)
{
	GameObjectInstance temp(frameSpeed);
	temp.Ui = ui;
	Instances.push_back(temp);
}

void GameObject::SetCollision(float radius)
{
	Radius = radius;
	UseCollision = true;
}

void GameObject::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const int activeCamera)
{
	if (Initialized)
	{
		if (UseBlend)
		{
			glEnable(GL_BLEND);
			glBlendFunc(BlendFirst, BlendSecond);
		}
		for ( auto & it : Instances)  // For each instance:
		{
			glStencilFunc(GL_ALWAYS, it.StencilId, 0);
			if ((it.Ui && activeCamera != 0) || !it.Draw) continue;  // Skip UI for spectate cameras and object, that shouldn't be drawn
			glm::mat4 view;
			glm::mat4 projection;
			if (it.Ui) view = projection = glm::mat4(1.0f);  // Set different view projection matrix for UI objects
			else
			{
				view = viewMatrix;
				projection = projectionMatrix;
			}
			if (Shaders != nullptr)
			{
				// Set correct shader programs and locations
				glUseProgram(Shaders->Index);
				glUniformMatrix4fv(Shaders->ViewMat, 1, GL_FALSE, glm::value_ptr(view));
				glUniformMatrix4fv(Shaders->ProjectionMat, 1, GL_FALSE, glm::value_ptr(projection));
				glUniformMatrix4fv(Shaders->ModelMat, 1, GL_FALSE, glm::value_ptr(it.ModelMatrix));
				if(it.OwnColor) glVertexAttrib3f(Shaders->Color, it.BaseColor.r, it.BaseColor.g, it.BaseColor.b);
				else glVertexAttrib3f(Shaders->Color, BaseColor.r, BaseColor.g, BaseColor.b);
				glVertexAttrib3f(Shaders->Pos, it.Position.x, it.Position.y, it.Position.z);
										
				//material
				glUniform3f(Shaders->MaterialAmbient, ObjectMaterial.ambient.x, ObjectMaterial.ambient.y, ObjectMaterial.ambient.z);
				glUniform3f(Shaders->MaterialDiffuse, ObjectMaterial.diffuse.x, ObjectMaterial.diffuse.y, ObjectMaterial.diffuse.z);
				glUniform3f(Shaders->MaterialSpecular, ObjectMaterial.specular.x, ObjectMaterial.specular.y, ObjectMaterial.specular.z);
				glUniform1f(Shaders->MaterialShininess, ObjectMaterial.shininess);

				// textures
				glUniform1i(Shaders->IsUi, it.Ui);
				if(!HaveNormals) glVertexAttrib3f(Shaders->Normal, 0.0f, 0.0f, 0.0f);
				glUniform1i(Shaders->TexSampler, 0);
				glUniform1i(Shaders->UseTexture, UseTexture);
				glActiveTexture(GL_TEXTURE0 + 0);
				glBindTexture(GL_TEXTURE_2D, Texture);

				// texture animation
				glUniform1i(Shaders->NumImages, NumImages);
				glUniform1i(Shaders->NumColumns, NumColumns);
				glUniform1i(Shaders->CurrImage, it.CurrImage);

				// texture shift
				glUniform2f(Shaders->Shift, it.Shift.x, it.Shift.y);

				glBindVertexArray(Vao.Index);
				if (NumFrames > 1) glVertexAttribPointer(Shaders->Pos, 3, GL_FLOAT, GL_FALSE, 0, (void*)(it.CurrFrame * (NumVertices / NumFrames) * 3 * sizeof(float)));
				if (UseEBO) glDrawElements(GL_TRIANGLES, NumTriangles * 3, GL_UNSIGNED_INT, 0);
				else glDrawArrays(GL_TRIANGLES, 0, NumTriangles * 3);
				glBindVertexArray(0);
			}
		}
		if (UseBlend) glDisable(GL_BLEND);  // Disable blending, if it was used
	}
	else std::cout << "Can't draw Object: object not initialized properly!" << std::endl;
}


void GameObject::Update(const float elapsedTime, const float deltaTime)
{
	for (auto& it : Instances)
	{
		if (NumFrames > 1) it.CurrFrame = ((int)elapsedTime / it.FrameSpeed) % NumFrames;
		if (NumImages > 1) it.CurrImage = ((int)elapsedTime / it.FrameSpeed) % NumImages;
		it.Shift = GlobFunc::Modulo(it.Shift + it.ShiftSpeed * deltaTime/100.0f, -1.0f, 1.0f);
	}
}

bool GameObject::GetCollision(glm::vec3 position, float radius)
{
	for (int i = 0; i < Instances.size(); i++)
	{
		glm::vec3 thisPos = glm::vec3(Instances[i].Position.x, 0.0f, Instances[i].Position.z);
		glm::vec3 otherPos = glm::vec3(position.x, 0.0f, position.z);
		float distance = glm::distance(thisPos, otherPos);
		if (distance <= (Radius * Instances[i].Scale.x + radius) ||
			distance <= (Radius * Instances[i].Scale.y + radius) ||
			distance <= (Radius * Instances[i].Scale.z + radius)) return true;
	}
	return false;
}