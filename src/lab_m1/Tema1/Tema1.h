#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"

#define RED glm::vec3(1, 0, 0)
#define GREY glm::vec3(0.412f, 0.412f, 0.412f)
#define PINK glm::vec3(0.933f, 0.510f, 0.933f)
#define BLACK glm::vec3(0, 0, 0)
#define WHITE  glm::vec3(1, 1, 1)
#define GREEN glm::vec3(0, 0.39f, 0)
#define BROWN glm::vec3(0.54f, 0.27f, 0.078f)
#define GOLDEN glm::vec3(0.85f, 0.64f, 0.125f)
namespace m1
{
    class Tema1 : public gfxc::SimpleScene
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
        void RenderGame();
        void CreateDuck();

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        int moveUp = 1;
        float speed = 150;
        float speed_Initial = 150;
        float ratioScale = 1.2;
        float square = 100;

        int up = 1;
        int change = 0;
        bool isDuckFirstRendered = 0;
        int lifes = 3;
        int bullets = 3;
        float time = 0;
        float timeOutside = 0;
        bool escape = 0;
        bool dead = 0;
        int centerX = 200 + rand() % 900;
        int centerY = 10;
        int isHit = 0;


        bool start = 0;
        int number_Ducks = 1;
        int score = 0;
        float angle = M_PI_4;
        int randomDirection;

        int clickX;
        int clickY;

        int height;
        int width;
        int level = 1;

        bool isGameOver = 0;

        glm::vec3 hitBoxLow = glm::vec3(0, 0, 1);
        gfxc::TextRenderer* tr;


    };
}   // namespace m1
