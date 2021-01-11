#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "Camera.h"
#define Z_NEAR (0.1f)
#define Z_FAR (200.f)


class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;

		

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color);
		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		double CheckColission(float platformX, float platformY, float platformZ, float ballX, float ballY, float ballZ, float length);
		
	protected:
		Laborator::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		bool is_ortho = false;

		GLfloat fov = 60;
		GLfloat right = 7.f;
		GLfloat left = -7.f;
		GLfloat bottom = -7.f;
		GLfloat top = 7.f;
		float z1, z2, aux1, aux2;
		float posX, posY;
		float speed;
		double distance;
		float platformLength, radius;
		bool collision, redCollision, blueCollision, greenCollision, orangeCollision, yellowCollision, whiteCollision;
		float fuel, timeSeconds;
		float scaleX;
		float x, y, z;
		bool pressedC;
		int orangeDef, blueDef, whiteDef, greenDef, yellowDef, redDef;
};
