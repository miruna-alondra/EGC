#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = SQUARE_SIDE;

	moveRight = false;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;
	
	// initialize tx and ty (the translation steps)
	translateX = 0.f;
	translateY = 0.f;

	// initialize sx and sy (the scale factors)
	scaleX = 1.f;
	scaleY = 1.f;
	
	// initialize angularStep
	angularStep = 0.f;
	posSunX = 300.f;
	posSunY = 450.f;
	
	

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);
	
	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations
	
	glm::ivec2 resolution = window->GetResolution();
	{
		modelMatrix = Transform2D::Translate(150, 250);

		if (moveRight) {
			translateX += MOVE * deltaTimeSeconds * resolution.x;
			modelMatrix *= Transform2D::Translate(translateX, translateY);
			if (translateX > resolution.x * LIMIT) {
				moveRight = false;
			}
		} else {
			translateX -= MOVE * deltaTimeSeconds * resolution.x;
			modelMatrix *= Transform2D::Translate(translateX, translateY);
			if (translateX <= 0) {
				moveRight = true;
			}
		}
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
	}
	{
		modelMatrix = Transform2D::Translate(400, 250);
		angularStep += deltaTimeSeconds;

		modelMatrix *= Transform2D::Translate(SQUARE_SIDE / 2.f, SQUARE_SIDE / 2.f);
		modelMatrix *= Transform2D::Rotate(angularStep);
		modelMatrix *= Transform2D::Translate(-SQUARE_SIDE / 2.f, -SQUARE_SIDE / 2.f);
		RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
	}
	{
		modelMatrix = Transform2D::Translate(650, 250);

		scaleX += SCALE_FACTOR_X * deltaTimeSeconds;
		scaleY += SCALE_FACTOR_Y * deltaTimeSeconds;

		modelMatrix *= Transform2D::Translate(SQUARE_SIDE / 2.f, SQUARE_SIDE / 2.f);
		modelMatrix *= Transform2D::Scale(sin(scaleX), sin(scaleY));
		modelMatrix *= Transform2D::Translate(-SQUARE_SIDE / 2.f, -SQUARE_SIDE / 2.f);

		RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

	}
	
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
