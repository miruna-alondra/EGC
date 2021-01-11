#include "Object2.h"

#include <Core/Engine.h>

float Object2::Min(float a, float b) {
	if (a <= b) 
		return a;
	return b;
}

float Object2::Max(float a, float b) {
	if (a >= b) 
		return a;
	return b;
}

Mesh* Object2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices, Mesh* cube) {
	unsigned int VAO = 0;
	// Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// Set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// Set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// Set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// Set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	
	// OBSERVATION: after interchanging the colour and normal pipes, the colours appear altered
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	cube->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	cube->vertices = vertices;
	cube->indices = indices;
	return cube;
}

Mesh* Object2::CreatePlatform(const char *name, glm::vec3 color, int length) {
	Mesh* aux = new Mesh(name);
	Mesh* platform = new Mesh(name);
	
	std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-length, -length,  length), glm::vec3(0, 1, 1), color),
			VertexFormat(glm::vec3( length, -length,  length), glm::vec3(1, 0, 1), color),
			VertexFormat(glm::vec3(-length,  length,  length), glm::vec3(1, 0, 0), color),
			VertexFormat(glm::vec3( length,  length,  length), glm::vec3(0, 1, 0), color),
			VertexFormat(glm::vec3(-length, -length, -length), glm::vec3(1, 1, 1), color),
			VertexFormat(glm::vec3( length, -length, -length), glm::vec3(0, 1, 1), color),
			VertexFormat(glm::vec3(-length,  length, -length), glm::vec3(1, 1, 0), color),
			VertexFormat(glm::vec3( length,  length, -length), glm::vec3(0, 0, 1), color),
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		platform = CreateMesh(name, vertices, indices, aux);
		return platform;
}


