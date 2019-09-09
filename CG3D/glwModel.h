#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "glwDrawable.h"
#include "glwObject3D.h"
#include "glwMesh.h"
#include "glwShader.h"
#include "glwTexture2D.h"
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/access.hpp>
#include <string>
#include <vector>
#include <memory>

class glwModel
{
public:
	bool gammaCorrection;

	glwModel(std::string const &path, bool gamma = false);

	void Draw(glwShader & shader, mat4x4 model = mat4x4(1.0f));
	std::string GetModelPath() const;
private:
	std::vector<std::shared_ptr<glwTexture2D>> textures_loaded;
	std::vector<glwMesh> meshes;
	std::string directory;
	std::string path;

	void loadModel(std::string const &path);

	void processNode(aiNode *node, const aiScene *scene);

	glwMesh processMesh(aiMesh *mesh, const aiScene *scene);

	std::vector<std::shared_ptr<glwTexture2D>> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	std::shared_ptr<glwTexture2D> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName);

	friend class boost::serialization::access;
	template<class Archive>
	void save(Archive & ar, const unsigned int version)
	{
		ar & gammaCorrection;
		ar & path;
	};

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & gammaCorrection;
		ar & path;
		loadModel(path);
	};

	BOOST_SERIALIZATION_SPLIT_MEMBER();
};

