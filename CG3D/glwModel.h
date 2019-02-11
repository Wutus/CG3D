#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "glwDrawableObject3D.h"
#include "glwMesh.h"
#include "glwShader.h"
#include "glwTexture2D.h"
#include <string>
#include <vector>
#include <memory>

class glwModel
{
public:
	/*  Model Data */
	std::vector<std::shared_ptr<glwTexture2D>> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<glwMesh> meshes;
	std::string directory;
	bool gammaCorrection;

	/*  Functions   */
	// constructor, expects a filepath to a 3D model.
	glwModel(std::string const &path, bool gamma = false);

	// draws the model, and thus all its meshes
	void Draw(glwShader & shader, mat4x4 model = mat4x4(1.0f));

private:
	/*  Functions   */
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(std::string const &path);

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode *node, const aiScene *scene);

	glwMesh processMesh(aiMesh *mesh, const aiScene *scene);

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	std::vector<std::shared_ptr<glwTexture2D>> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	std::shared_ptr<glwTexture2D> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName);
};

