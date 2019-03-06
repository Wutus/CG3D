#pragma once

#include "glwDrawable.h"
#include "glwObject3D.h"
#include "glwShader.h"
#include "glwTexture2D.h"
#include "glwMaterial.h"

#include <string>
#include <vector>
#include <memory>

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture 
{
	unsigned int id;
	std::string type;
	std::string path;
};

class glwMesh
{
public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::shared_ptr<glwTexture2D>> textures;
	std::shared_ptr<glwMaterial> material;
	bool useMaterial;
	unsigned int VAO;

	/*  Functions  */
	// constructor
	glwMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<glwTexture2D>> textures);
	glwMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<glwMaterial> material);

	// render the mesh
	void Draw(glwShader & shader);

private:
	/*  Render data  */
	unsigned int VBO, EBO;
	/*  Functions    */
	// initializes all the buffer objects/arrays
	void setupMesh();
};
