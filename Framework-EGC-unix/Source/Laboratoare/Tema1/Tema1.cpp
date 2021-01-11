#include "Tema1.h"

#include <vector>
#include <iostream>
#include <math.h>
#include <cstdlib>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// create a mesh baloon 
	R1 = 35;
	R2 = 70;
	glm::vec3 color = glm::vec3(0.85f, 0.85f, 0.10f);
	Mesh* balloon = Object::CreateBalloon("balloon1", color, R1, R2);
	meshes["balloon1"] = balloon;
	Mesh* balloon2 = Object::CreateBalloon("balloon2", glm::vec3(0.89f, 0.47f, 0.20f), R1, R2);
	meshes["balloon2"] = balloon2;
	
	// create mesh bow
	Mesh* bow = Object::CreateBow("bow", glm::vec3(0.f, 0.f, 0.f), length);
	meshes["bow"] = bow;
			
	// create mesh arrow
	Mesh* arrow = Object::CreateArrow("arrow", glm::vec3(0.f, 0.f, 0.f), lengthArrow);
	meshes["arrow"] = arrow;
	
	// create shuricken
	Mesh* shuriken = Object::CreateShuriken("shuriken", glm::vec3(0.858824f, 0.439216f, 0.576471f), hTriangle);
	meshes["shuriken"] = shuriken;
		
	// create powerBar
	Mesh* powerBar = Object::CreatePowerbar("power", glm::vec3(0.419608f, 0.556863f, 0.137255f), lengthBar);
	meshes["power"] = powerBar;
		

	// initialize tx and ty (the translation steps)
	for (int i = 0; i < 10; i++) {
		transY.push_back(-i * 100);
		transX.push_back(rand() % 1000 + 300);
		scl.push_back(1);
	}
	tx = 700.f;
	ty = 150.f;

	// initialize sx and sy (the scale factors)
	scaleX = 1.f;
	scaleY = 1.f;
	
	// initialize angularStep
	angularStep = 0.f;
	
	moveArrowY = moveBowY = 150.f;
	moveArrowX = moveBowX = 10.f;
	
	resolutionX = 0;
	resolutionY = 0;
	
	moveArrow = false;
	
	arrowSpeed = 300;
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.22f, 0.69f, 0.87f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	// update steps for translation, rotation, scale, in order to create animations
	
	glm::ivec2 resolution = window->GetResolution();
	resolutionX = resolution.x;
	resolutionY = resolution.y;
	{
		for(int i = 0; i < 10; i++) {	
			float posX = moveArrowX + 100 * cos(angle2);
			float posY = moveArrowY + 100 * sin(angle2);
			if (glm::distance(glm::vec2(posX, posY), glm::vec2(transX[i], transY[i])) < R2) {
				scl[i] = 0.99f;
				if (i % 2 == 0) {
					score += 10;
				} else {
					score -= 10;
				}
				cout << "Am scorul " << score << endl;
			}
			if (scl[i] < 1) {
				scl[i] -= deltaTimeSeconds;
			}
			transY[i] += MOVE * deltaTimeSeconds * resolution.y;
			modelMatrix = Transform2D::Translate(transX[i], transY[i]);
			modelMatrix *= Transform2D::Scale(scl[i], scl[i]);
			if (transY[i] > resolution.y * 1.5f || scl[i] < 0) {
				transY[i] = -i * 100;
				transX[i] = rand() % 1000 + 300;
				scl[i] = 1;
			}
			if (i % 2 == 0) {
			RenderMesh2D(meshes["balloon2"], shaders["VertexColor"], modelMatrix);
			} else {
			RenderMesh2D(meshes["balloon1"], shaders["VertexColor"], modelMatrix);
			}
		}
	}
	
	
	{
		modelMatrix = Transform2D::Translate(moveBowX, moveBowY);
		modelMatrix *= Transform2D::Rotate(M_PI - angle);
		RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
	}
	
	{
		modelMatrix = Transform2D::Translate(moveArrowX, moveArrowY);
		if (moveArrow) {
			modelMatrix *= Transform2D::Rotate(M_PI - angle2);
			RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
			moveArrowX -= cos(angle2) * deltaTimeSeconds * arrowSpeed;
			moveArrowY += sin(angle2) * deltaTimeSeconds * arrowSpeed;
			modelMatrix = Transform2D::Translate(moveArrowX, moveArrowY);
			if (moveArrowX > resolution.x || moveArrowY > resolution.y) {
				moveArrow = false;
				arrowSpeed = 300.f;
			}
		} else {
			moveArrowY = moveBowY;
			moveArrowX = moveBowX;
			modelMatrix = Transform2D::Translate(moveArrowX, moveArrowY);
			modelMatrix *= Transform2D::Rotate(M_PI - angle);
			RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
		}
	}
	
	{
		float posX = moveArrowX + 100 * cos(angle2);
		float posY = moveArrowY + 100 * sin(angle2);
		if (glm::distance(glm::vec2(posX, posY), glm::vec2(tx, ty)) < lengthArrow / 2) {
			scaleShuriken = 0.99f;
		}
		if (scaleShuriken < 1) {
			scaleShuriken -= deltaTimeSeconds;
		}
		if (!ignoreShuriken 
			&& glm::distance(glm::vec2(moveBowX, moveBowY), glm::vec2(tx, ty)) < length / 2 + lengthArrow / 2) {
			ignoreShuriken = true;
			lives--;
			cout << "Mai am " << lives << " vieti" << endl;
			if (lives < 0) {
				exit(0);
			}
		}
		angularStep += deltaTimeSeconds;
				
		tx -= deltaTimeSeconds * 200;
		if (tx <= 0 || scaleShuriken < 0) {
			ignoreShuriken = false;
			tx = resolution.x + 100;
			ty = 100 + rand() % 500;
			scaleShuriken = 1.f;
		}
		modelMatrix = Transform2D::Translate(tx, ty);
		modelMatrix *= Transform2D::Rotate(angularStep);
		modelMatrix *= Transform2D::Scale(scaleShuriken, scaleShuriken);
		RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
	}
	{
		
		modelMatrix = Transform2D::Translate(150, 10);
		modelMatrix *= Transform2D::Scale(scaleX, scaleY);
		RenderMesh2D(meshes["power"], shaders["VertexColor"], modelMatrix);
	}
	
	
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (!moveArrow) {
		if(window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
			pressButton = true;
			if (scaleX < SCALE_LIMIT) {
				scaleX += deltaTime * 1.5f;
				arrowSpeed += deltaTime * 1000;
			}
		}
	}
	
	if (window->KeyHold(GLFW_KEY_W)) {
		moveBowY += 100 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		moveBowY -= 100 * deltaTime;
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	
	
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	int x, y;
	x = moveBowX - mouseX;
	y = mouseY + moveBowY -(resolutionY - moveBowY);
	angle = atan2(-y, x);
	
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
		moveArrow = true;
		angle2 = angle;
		pressButton = false;
		scaleX = 1.f;
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
