#pragma once

#include <iostream>
#include "pgr.h"
#include "Shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "CommonShaders.h"
#include "GameObjectInstance.h"
#include "GlobFunc.h"

/**
 * \brief Struct used in GameObject. Encapsulates material information of the object.
 */
struct Material
{
	glm::vec3 ambient;  ///< Default light strenght
	glm::vec3 diffuse;  ///< Defines how light diffuses on object
	glm::vec3 specular;  ///< Defines reflectivness
	float shininess;  ///< Strenght of the reflection itself
};

/**
 * \brief Class that contains all needed information of each ingame object (one GameObject per one type of object).
 */
class GameObject
{
public:
	const std::string Name;
	glm::vec4 BaseColor;
	Material ObjectMaterial;
	GLuint Texture;
	CommonShaders* Shaders;  //< Pointer to shaders locations

	unsigned int NumVertices;  ///< Number of vertices
	unsigned int NumTriangles;  ///< Number of triangles
	unsigned int NumFrames;  ///< Number of frames for vertex geometry
	unsigned int NumImages;  ///< Number of individual images in 1 iamge texture
	unsigned int NumColumns;  ///< Number of columns of images in 1 iamge texture
	float Radius;  ///< Radius for collision detection

	// Buffers
	VBO Vbo;  //< Vertex buffer
	EBO Ebo;  //< Element buffer
	VAO Vao;  //< Vertex array buffer

	GLenum BlendFirst;  //< First param of glBlenFunc
	GLenum BlendSecond;  //< Second param of glBlendFunc
	bool UseBlend;  //< Use blending

	bool UseTexture;
	bool UseEBO;  //< Contains indicies?
	bool UseCollision;  //< Detect collision using Radius
	bool HaveNormals;
	bool Initialized;  //< Simple info, if object have everything setted up to be used

	std::vector<GameObjectInstance> Instances;  //< List of individual object instances.

	/**
	 * \brief Constructor
	 * 
	 * \param shaders pointer to shader locations
	 * \param name name of the object
	 */
	GameObject(CommonShaders* shaders, const std::string name);

	//! Destructor
	~GameObject();



	/**
	 * \brief Used for loading the file using Assimp
	 * 
	 * \param path contains path to file
	 * \param numFrames is how many animation vertex frame object contains
	 * 
	 * \return if file loading succeded
	 */
	bool LoadFile(const std::string path, unsigned int numFrames = 1);

	/**
	 * \brief Loads just a 2D texture and sets it on square (2 triangles)
	 * 
	 * \param path contains path to file
	 * \param numImages is how many individual images main texture contains (for texture animating)
	 * \param numColumns amount of columns of individual images in main texture
	 * 
	 * \return if texture loading succeded
	 */
	bool LoadSprite(const std::string path, unsigned int numImages = 1, unsigned int numColumns = 1);

	/**
	 * \brief Creates new object with specified vertices and creates EBO, if provided
	 * 
	 * \param vertices vector of vertices (3x float per vertex(XYZ))
	 * \param indices vector of indices (3x unsigned in per triangle)
	 * \param baseColor basic color for new object
	 * \param numFrames is how many animation vertex frame object contains
	 * 
	 * \return if model creation succeded
	 */
	bool NewModel(const std::vector<float>& vertices, const std::vector<unsigned int>& indices = {}, glm::vec4 baseColor = glm::vec4(1.0f), unsigned int numFrames = 1);  // Manually load vertices (and EBO)



	/**
	 * \brief Creates new instance of the object and sets it basic information
	 * 
	 * \param ui Will the object be rendered to UI (no World space information)?
	 * \param frameSpeed If animated, how often will it swap frame or image
	 */
	void NewInstance(bool ui = false, unsigned int frameSpeed = 1);

	/**
	 * \brief Sets collision, if collision testing is needed for the object
	 * 
	 * \param radius Size of the collider
	 */
	void SetCollision(float radius);



	/**
	 * \brief Prepares and draws all object instances, that should be drawn
	 * 
	 * \param viewMatrix Matrix to get position of the camera in virtual space
	 * \param projectionMatrix Matrix used to transfer 3D coordinates to 2D screen coordinates
	 * \param activeCamera Specify, which camera is currently active
	 */
	void Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const int activeCamera);

	/**
	 * \brief Update object information (current frame and image)
	 * 
	 * \param elapsedTime elapsed time of application
	 * \param deltaTime time from last scene draw
	 */
	void Update(const float elapsedTime, const float deltaTime);

	/**
	 * \brief Check if collision was made
	 * 
	 * \param position External object position, to check collision against it
	 * \param radius Radius of external object collider
	 * \return if objects collided
	 */
	bool GetCollision(glm::vec3 position, float radius);
};
