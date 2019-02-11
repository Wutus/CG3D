#include "glwMesh.h"

#include "glwTexture2D.h"

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

glwMesh::glwMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<shared_ptr<glwTexture2D>> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	useMaterial = false;

	// now that we have all the required data, set the vertex buffers and its attribute pointers.
	setupMesh();
}

glwMesh::glwMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, shared_ptr<glwMaterial> material)
{
	this->vertices = vertices;
	this->indices = indices;
	this->material = material;
	useMaterial = true;

	// now that we have all the required data, set the vertex buffers and its attribute pointers.
	setupMesh();
}

void glwMesh::Draw(glwShader & shader)
{
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	if (!useMaterial)
	{
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			string number;
			string name = textures[i]->GetType();
			if (name == "texture_diffuse")
			{
				number = std::to_string(diffuseNr++);
			}
			else if (name == "texture_specular")
			{
				number = std::to_string(specularNr++); // transfer unsigned int to stream
			}
			else if (name == "texture_normal")
			{
				number = std::to_string(normalNr++); // transfer unsigned int to stream
			}
			else if (name == "texture_height")
			{
				number = std::to_string(heightNr++); // transfer unsigned int to stream
			}
			// now set the sampler to the correct texture unit
			shader.setInt(name + number, i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, textures[i]->GetID());
		}
	}
	else
	{
		glActiveTexture(GL_TEXTURE0); // active proper texture unit before binding
		shader.setInt("material.diffuse", 0);
		glBindTexture(GL_TEXTURE_2D, material->getDiffuseTexture()->GetID());

		glActiveTexture(GL_TEXTURE1); // active proper texture unit before binding
		shader.setInt("material.specular", 1);
		glBindTexture(GL_TEXTURE_2D, material->getSpecularTexture()->GetID());

		shader.setFloat("material.shininess", material->shininess);
	}
	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

void glwMesh::setupMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}
