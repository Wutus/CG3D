#pragma once

#include "glwDrawable.h"
#include "glwObject3D.h"
#include "glwShader.h"
#include "glwTexture2D.h"
#include "glwMaterial.h"

#include "glwBaseSerialization.hpp"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/access.hpp>

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

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & Position;
		ar & Normal;
		ar & TexCoords;
		ar & Tangent;
		ar & Bitangent;
	};
};

/*struct Texture 
{
	unsigned int id;
	std::string type;
	std::string path;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & id;
		ar & type;
		ar & path;
	};
};*/

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

	friend class boost::serialization::access;
	template<class Archive>
	void save(Archive & ar, const unsigned int version)
	{
		ar & vertices;
		ar & indices;
		ar & textures;
		ar & material;
		ar & useMaterial;
	};

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & vertices;
		ar & indices;
		ar & textures;
		ar & material;
		ar & useMaterial;
		setupMesh();
	};

	BOOST_SERIALIZATION_SPLIT_MEMBER();
};
