#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#define TWO_PI	(6.28318530718f)
#define N	(50)

namespace Object
{

	Mesh* CreateBalloon(std::string name, glm::vec3 color, int R1, int R2);
	Mesh* CreateBow(std::string name, glm::vec3 color, float length);
	Mesh* CreateArrow(std::string name, glm::vec3 color, float length);
	Mesh* CreateShuriken(std::string name, glm::vec3 color, float height);
	Mesh* CreatePowerbar(std::string name, glm::vec3 color, float length);

}

