#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2
{

	Mesh* CreatePlatform(const char *name, glm::vec3 color, int length);
	Mesh* CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices, Mesh* cube);
	Mesh* CreateFuel(const char *name, glm::vec3 color, float length);
	float Min(float a, float b);
	float Max(float a, float b);

}

