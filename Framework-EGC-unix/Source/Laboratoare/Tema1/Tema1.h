#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <vector>

#define MOVE	(0.25f)
#define LIMIT	(0.5f)
#define SCALE_LIMIT (3.f)


class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix = glm::mat3(1);
		float translateX, translateY, tx, ty, moveBowY, moveBowX;
		float moveArrowX, moveArrowY;
		float scaleX, scaleY, resolutionX, resolutionY;
		float angularStep, angle = 0.f;
		float angle2 = 0.f;
		int R1, R2;
		int arrowSpeed;
		std::vector<float> transY, transX, scl;
		int lives = 3;
		int score = 0;
		bool ignoreShuriken = false;
		float scaleShuriken = 1.f;
		float length = 150;
		float lengthArrow = 100;
		float hTriangle = 20;
		float lengthBar = 50;
		GLboolean moveArrow;
		GLboolean pressButton;
};
