#pragma once

#include <include/glm.h>

namespace Transform3D
{
	// Translate matrix
	inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
	{
		// TODO implement translate matrix
		return glm::transpose(
			glm::mat4(1.f, 0.f, 0.f, translateX,
			0.f, 1.f, 0.f, translateY,
			0.f, 0.f, 1.f, translateZ,
			0.f, 0.f, 0.f, 1.f)
		);
	}

	// Scale matrix
	inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
	{
		// TODO implement scale matrix
		return glm::mat4(
		scaleX, 0.f, 0.f, 0.f,
		0.f, scaleY, 0.f, 0.f,
		0.f, 0.f, scaleZ, 0.f,
		0.f, 0.f, 0.f, 1.f);
	}

	// Rotate matrix relative to the OZ axis
	inline glm::mat4 RotateOZ(float radians)
	{
		// TODO implement rotate matrix
		return glm::mat4(
		cos(radians), sin(radians), 0.f, 0.f,
		-sin(radians), cos(radians), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
	}

	// Rotate matrix relative to the OY axis
	inline glm::mat4 RotateOY(float radians)
	{
		// TODO implement rotate matrix
		return glm::mat4(
			cos(radians), 0.f, -sin(radians), 0.f,
			0.f, 1.f, 0.f, 0.f,
			sin(radians), 0.f, cos(radians), 0.f,
			0.f, 0.f, 0.f, 1.f);
	}

	// Rotate matrix relative to the OX axis
	inline glm::mat4 RotateOX(float radians)
	{
		// TODO implement rotate matrix
		return glm::mat4(
			1.f, 0.f, 0.f, 0.f,
			0.f, cos(radians), sin(radians), 0.f,
			0.f, -sin(radians), cos(radians), 0.f,
			0.f, 0.f, 0.f, 1.f);
	}
}
