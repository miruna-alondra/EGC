#include "Tema2.h"
#include "Object2.h"

#include <vector>
#include <math.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	
	z1 = -10 - rand() % 3;
	z2 =  -20 - rand() % 3;
	aux1 = -17 + rand() % 2;
	aux2 = aux1;
	posX = 0.f;
	posY = 0.5f;
	speed = 3.f;
	fuel = 300.f;
	platformLength = 1.2f;
	radius = 0.f;
	collision = false;
	redCollision = false;
	blueCollision = false;
	greenCollision = false;
	orangeCollision = false;
	yellowCollision = false;
	pressedC = false;
	timeSeconds = 50.f;
	scaleX = 0.75f;
	orangeDef  = 0;
	blueDef = whiteDef = 0;
	greenDef = yellowDef = redDef = 0;

	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	{
		glm::vec3 yellow = glm::vec3(0.85f, 0.85f, 0.10f);
		Mesh* cube1 = Object2::CreatePlatform("cube1", yellow, platformLength);
		meshes["cube1"] = cube1;
		
		glm::vec3 red = glm::vec3(1.f, 0.f, 0.10f);
		Mesh* cube2 = Object2::CreatePlatform("cube2", red, platformLength);
		meshes["cube2"] = cube2;
		
		glm::vec3 green = glm::vec3(0.f, 1.f, 0.f);
		Mesh* cube3 = Object2::CreatePlatform("cube3", green, platformLength);
		meshes["cube3"] = cube3;
		
		glm::vec3 blue = glm::vec3(0.f, 0.f, 1.f);
		Mesh* cube4 = Object2::CreatePlatform("cube4", blue, platformLength);
		meshes["cube4"] = cube4;
		
		glm::vec3 orange = glm::vec3(1.f, 0.5f, 0.f);
		Mesh* cube5 = Object2::CreatePlatform("cube5", orange, platformLength);
		meshes["cube5"] = cube5;
		
		glm::vec3 purple = glm::vec3(0.6f, 0.196078f, 0.8f);
		Mesh* cube6 = Object2::CreatePlatform("cube6", purple, platformLength);
		meshes["cube6"] = cube6;
		
		glm::vec3 white = glm::vec3(1.f, 1.f, 1.f);
		Mesh* cube7 = Object2::CreatePlatform("cube7", white, platformLength);
		meshes["cube7"] = cube7;
		
		Mesh* mesh2 = new Mesh("box");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh2->GetMeshID()] = mesh2;
		
		
		
			
	}
	{
		Mesh* black = new Mesh("box2");
		black->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[black->GetMeshID()] = black;
	}
	
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Shader *shader = new Shader("ShaderTema2");
		shader->AddShader("Resources/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Resources/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		Shader *shader2 = new Shader("ShaderCombustibil");
		shader2->AddShader("Resources/Shaders/CombustibilVS.glsl", GL_VERTEX_SHADER);
		shader2->AddShader("Resources/Shaders/CombustibilF.glsl", GL_FRAGMENT_SHADER);
		shader2->CreateAndLink();
		shaders[shader2->GetName()] = shader2;
	}
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	
	
}


void Tema2::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}
double Tema2::CheckColission(float platformX, float platformY, float platformZ, float ballX, float ballY, float ballZ, float length) {
	float minx, maxx, miny, maxy, minz, maxz, x, y, z;
	minx = platformX - length / 2;
	miny = platformY - length / 2;
	minz = platformZ - length / 2;
	maxx = platformX + length / 2;
	maxy = platformY + length / 2;
	maxz = platformZ + length / 2;
	x = Object2::Max(minx, Object2::Min(ballX, maxx));
	y = Object2::Max(miny, Object2::Min(ballY, maxy));
	z = Object2::Max(minz, Object2::Min(ballZ, maxz));
	double distance = sqrt((x - ballX)*(x-ballX) + (y - ballY)*(y-ballY) + (ballZ - z)*(ballZ - z));
	return distance;
	
}
void Tema2::Update(float deltaTimeSeconds)	
{
		if (pressedC) {
			camera->Set(glm::vec3(posX, posY + radius, 0.f), glm::vec3(posX, posY, -2.f), glm::vec3(0.f, 1.f, 0.f));
		} else {
			camera->Set(glm::vec3(0.f, 2.f, 3.5f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
		}
		if (timeSeconds == 0) {
			speed = 3.f;
			orangeCollision = false;
			timeSeconds = 50.f;
		}
		cout << "Combustibil " << fuel << endl;
		if (z1 >= 5.f) {
			z1 = aux1;
		}
			z1 += speed * deltaTimeSeconds;
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(-platformLength, 0, z1));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.025f, 5.0f));
				distance = CheckColission(-platformLength, 0.f, z1, posX, posY, radius, platformLength);
				if (distance <= radius) {
					collision = true;
					orangeCollision = true;
				} else {
					collision = false;
					
				}
					if (collision) {
						RenderMesh(meshes["cube6"], shaders["VertexNormal"], modelMatrix);
					} else {
			
						RenderMesh(meshes["cube5"], shaders["VertexNormal"], modelMatrix);
					}

			}
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, z1));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.025f, 4.0f));
				distance = CheckColission(0.f, 0.f, z1, posX, posY, radius, platformLength);
				if (distance <= radius) {
					collision = true;
					whiteCollision = true;
					whiteDef = 1;
				} else {
					collision = false;
					whiteCollision = false;
					whiteDef = 0;
				}
					if (collision) {
						RenderMesh(meshes["cube6"], shaders["VertexNormal"], modelMatrix);
					} else {
			
						RenderMesh(meshes["cube7"], shaders["VertexNormal"], modelMatrix);
					}
			}
			
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(platformLength, 0, z1));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.025f, 3.f));
				distance = CheckColission(platformLength, 0.f, z1, posX, posY, radius, platformLength);
				if (distance <= radius) {
					collision = true;
					greenCollision = true;
					greenDef = 1;
				} else {
					collision = false;
					greenCollision = false;
					greenDef = 0;
				}
					if (collision) {
						RenderMesh(meshes["cube6"], shaders["VertexNormal"], modelMatrix);
					} else {
			
						RenderMesh(meshes["cube3"], shaders["VertexNormal"], modelMatrix);
					}
			}
			
		if (z2 >= 5.f) {
			z2 = aux2;
		}
			z2 += speed * deltaTimeSeconds;
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(-platformLength, 0, z2));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.025f, 3.f));
				distance = CheckColission(-platformLength, 0.f, z2, posX, posY, radius, platformLength);
				if (distance <= radius) {
					collision = true;
					yellowCollision = true;
					yellowDef = 1;
				}else {
					collision = false;
					yellowCollision = false;
					yellowDef = 0;
				}
					if (collision) {
						RenderMesh(meshes["cube6"], shaders["VertexNormal"], modelMatrix);
					} else {
			
						RenderMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix);
					}
			}
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0, z2));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.025f, 4.0f));
				distance = CheckColission(0.f, 0.f, z2, posX, posY, radius, platformLength);
				if (distance <= radius) {
					collision = true;
					blueCollision = true;
					blueDef = 1;
				} else {
					collision = false;
					blueCollision = false;
					blueDef = 0;
				}
					if (collision) {
						RenderMesh(meshes["cube6"], shaders["VertexNormal"], modelMatrix);
					} else {
			
						RenderMesh(meshes["cube4"], shaders["VertexNormal"], modelMatrix);
					}
			}
			
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(platformLength, 0, z2));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.025f, 5.f));
				distance = CheckColission(platformLength, 0.f, z2, posX, posY, 0.5f, platformLength);
				if (distance <= 0.5f) {
					collision = true;
					redCollision = true;
					redDef = 1;
					
				} else {
					collision = false;
					redCollision = false;
					redDef = 0;
				}
					if (collision) {
						RenderMesh(meshes["cube6"], shaders["VertexNormal"], modelMatrix);
					} else {
			
						RenderMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix);
					}
			}
			
		
		{ 	
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(posX, posY, 0.5f));
			RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.f, 1.f, 1.f));
		}
		
		{	
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.15f, 1.f, 0.1f));
			RenderSimpleMesh(meshes["box2"], shaders["ShaderCombustibil"], modelMatrix, glm::vec3(1.f, 1.f, 1.f));
		}
		
		{	
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.f, 1.f, 0.f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleX, 1.f, 1.f));
			RenderSimpleMesh(meshes["box"], shaders["ShaderCombustibil"], modelMatrix, glm::vec3(0.f, 1.f, 0.f));
		}
		
		
		
		if (redCollision) {
			exit(0);
		}
		if (yellowCollision) {
			if (scaleX >= 0) {
				scaleX -= 0.25f * deltaTimeSeconds;
			}
			fuel -= 7.f;
		}
		if (orangeCollision) {
			orangeDef = 1;
			speed = 50.f;
			timeSeconds -= 1.f;
			
		} else {
			orangeDef = 0;
		}
		if (greenCollision) {
			if (scaleX < 0.3f) {
				scaleX += 0.25f * deltaTimeSeconds;
			}
			fuel += 7.f;
		}
		if (whiteCollision) {
			fuel = 300.f;
			scaleX = 0.75f;
			
		}
		if(fuel <= 0) {
			exit(0);
		}

		

}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem();
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}
void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
	{
		return;
	}

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);


	GLint locObject = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(locObject, 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	
	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	glUniform1i(glGetUniformLocation(shader->program, "orangeDef"), orangeDef);
	glUniform1f(glGetUniformLocation(shader->program, "timeSeconds"), timeSeconds);
	
	// Get shader location for "Time"
	GLint timeLocation = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1i(glGetUniformLocation(shader->program, "blueDef"), blueDef);
	glUniform1i(glGetUniformLocation(shader->program, "whiteDef"), whiteDef);
	glUniform1i(glGetUniformLocation(shader->program, "greenDef"), greenDef);
	glUniform1i(glGetUniformLocation(shader->program, "yellowDef"), yellowDef);
	glUniform1i(glGetUniformLocation(shader->program, "redDef"), redDef);
	// Set shader uniform "Time" to elapsed time
	glUniform1f(timeLocation, (GLfloat)Engine::GetElapsedTime());

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// add key press event
	if (window->KeyHold(GLFW_KEY_SPACE)) {
		if (posY < 2) {
			posY += 3.f * deltaTime;
		} else if (posY >= 2) {
			posY -= 2.f * deltaTime;
		}
	}
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			camera->TranslateForward(deltaTime * cameraSpeed);
			
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}
		
		
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}

	if (key == GLFW_KEY_O) {
		is_ortho = true;	
	}
	if (key == GLFW_KEY_P) {
		is_ortho = false;

	}
	if (key == GLFW_KEY_W && !orangeCollision) {
		if (speed <= 30) {
			speed += 3;
		}
	}
	if (key == GLFW_KEY_S && !orangeCollision) {
		if (speed >= 3) {
			speed -= 1;
		}
	}
	if (key == GLFW_KEY_A) {
		if (posX >= -1) {
			posX -= platformLength;
		}
	}
	
	if (key == GLFW_KEY_D) {
		if (posX <= 1) {
			posX += platformLength;
		}
	}
	if (key == GLFW_KEY_C) {
		pressedC = !pressedC;
		
	}
	
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_SPACE) {
		posY = 0.5f;
	}
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * deltaX);

		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * deltaX);
		}

	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
} 
