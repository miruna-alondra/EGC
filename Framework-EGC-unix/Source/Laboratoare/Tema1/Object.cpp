#include "Object.h"

#include <Core/Engine.h>

Mesh* Object::CreateBalloon(std::string name, glm::vec3 color, int R1, int R2) {
		Mesh* baloon = new Mesh(name);
		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;
		GLfloat arg;
		vertices.emplace_back(glm::vec3(0, 0, 0), color);
		for (GLushort i = 0; i < N; i++) {
			arg = TWO_PI * i / N;
			vertices.emplace_back(glm::vec3(R1*cos(arg), R2*sin(arg), 0), color);
			indices.push_back(0);
			indices.push_back(i);
			if (i != N - 1) {
				indices.push_back(i + 1);
			}
		}
		indices.push_back(1);
		arg = TWO_PI * 3 / 4;
		float x = R1 * cos(arg);
		float y = R2 * sin(arg);
		vertices.emplace_back(glm::vec3(x, y, 0), glm::vec3(0.f, 0.f, 0.f));
		vertices.emplace_back(glm::vec3(x + 2, y, 0), glm::vec3(0.f, 0.f, 0.f));
		for (GLushort i = 1; i < 10; i++) {
			indices.push_back(N + i);
			indices.push_back(N + i + 1);
			if (i % 2 == 0) {
				vertices.emplace_back(glm::vec3(x + 12, y - 20 * i, 0), glm::vec3(0.f, 0.f, 0.f));
				vertices.emplace_back(glm::vec3(x + 14, y - 20 * i, 0), glm::vec3(0.f, 0.f, 0.f));
			} else {
				vertices.emplace_back(glm::vec3(x, y - 20 * i, 0), glm::vec3(0.f, 0.f, 0.f));
				vertices.emplace_back(glm::vec3(x + 2, y - 20 * i, 0), glm::vec3(0.f, 0.f, 0.f));
			}
			indices.push_back(N + i + 2);
			indices.push_back(N + i + 3);
		}
		baloon->InitFromData(vertices, indices);
		return baloon;
		
}

Mesh* Object::CreateBow(std::string name, glm::vec3 color, float length) {
		Mesh* bow = new Mesh(name);
		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;
		GLfloat arg;
		vertices.emplace_back(glm::vec3(0, 0, 0), color);
		
		for (GLushort i = 0; i <= N / 2; i++) {
			arg = TWO_PI * i / N;
			vertices.emplace_back(glm::vec3(length / 2 * sin(arg), length / 2 * cos(arg), 0), color);
			indices.push_back(i);
		}
		for (GLushort i = N / 2; i <= N; i++) {
			indices.push_back(i);
		}
		indices.push_back(1);
		indices.push_back(0);
		bow->InitFromData(vertices, indices);
		bow->SetDrawMode(GL_LINE_LOOP);
		return bow;
	
}

Mesh* Object::CreateArrow(std::string name, glm::vec3 color, float length) {
	Mesh* arrow = new Mesh(name);
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0, 0, 0) + glm::vec3(length, 0, 0), color),
		VertexFormat(glm::vec3(0, 0, 0) + glm::vec3(length / 2, -length / 4 , 0), color),
		VertexFormat(glm::vec3(0, 0, 0) + glm::vec3(length /2 + length / 4, 0, 0), color),
		VertexFormat(glm::vec3(0, 0, 0) + glm::vec3(length / 2 , length / 4, 0), color),
		VertexFormat(glm::vec3(0, 0, 0) + glm::vec3(length, 0, 0), color)
		
	};
		
		std::vector<unsigned short> indices = { 0, 1, 2, 3, 4};
		indices.push_back(1);
		arrow->InitFromData(vertices, indices);
		arrow->SetDrawMode(GL_LINE_LOOP);
		return arrow;
}

Mesh* Object::CreateShuriken(std::string name, glm::vec3 color, float height) {
		std::vector<unsigned short> indices;
		std::vector<VertexFormat> vertices;

		vertices.emplace_back(glm::vec3(0, 0, 0), color);
		indices.push_back(0);
		vertices.emplace_back(glm::vec3(-height / 2, height, 0), color);
		indices.push_back(1);
		vertices.emplace_back(glm::vec3(height / 2, height, 0), color);
		indices.push_back(2);
		indices.push_back(0);
		vertices.emplace_back(glm::vec3(height, height / 2, 0), color);
		indices.push_back(3);
		vertices.emplace_back(glm::vec3(height, -height / 2, 0), color);
		indices.push_back(4);
		indices.push_back(0);
		vertices.emplace_back(glm::vec3(height / 2, -height, 0), color);
		indices.push_back(5);
		vertices.emplace_back(glm::vec3(-height / 2, -height, 0), color);
		indices.push_back(6);
		indices.push_back(0);
		vertices.emplace_back(glm::vec3(-height, -height / 2, 0), color);
		vertices.emplace_back(glm::vec3(-height, height / 2, 0), color);
		indices.push_back(7);
		indices.push_back(8);
		indices.push_back(0);
		
		Mesh* shuriken = new Mesh(name);
		shuriken->InitFromData(vertices, indices);
		return shuriken;
}
Mesh* Object::CreatePowerbar(std::string name, glm::vec3 color, float length) {
	std::vector<unsigned short> indices;
	std::vector<VertexFormat> vertices;
	vertices.emplace_back(glm::vec3(0, 0, 0), color);
	indices.push_back(0);
	vertices.emplace_back(glm::vec3(0, length / 2, 0), color);
	indices.push_back(1);
	vertices.emplace_back(glm::vec3(length, length / 2, 0), color);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(0);
	vertices.emplace_back(glm::vec3(length, 0, 0), color);
	indices.push_back(3);
	
	Mesh* powerBar = new Mesh(name);
	powerBar->InitFromData(vertices, indices);
	return powerBar;
}	
