#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/cameraTema.h"

#define Z_FAR (200.f)
#define Z_NEAR (.01f)

#define RED glm::vec3(1, 0, 0)
#define DARK_GREEN glm::vec3(0, 0.502f, 0)
#define GREEN glm::vec3(0, 0.39f, 0)
#define BLACK glm::vec3(0, 0, 0)
#define BROWN glm::vec3(0.54f, 0.27f, 0.078f)

#define WHITE  glm::vec3(1, 1, 1)
#define GOLDEN glm::vec3(0.85f, 0.64f, 0.125f)
#define PINK glm::vec3(0.933f, 0.510f, 0.933f)
#define BLUE glm::vec3(0, 1, 1)
#define BLACK glm::vec3(0, 0, 0)
#define CHOCOLATE_BROWN glm::vec3(0.824, 0.412, 0.118)

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
         Tema2();
        ~Tema2();

        void Init() override;
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

        struct CarOponent
        {
            CarOponent() : translateX(0.0), translateZ(0.0), pointIndex((rand() % 200) * 2),
                verticesRoad(), dist((rand() % 3) * 0.25), angle(0.0), colorType(rand() % 4) {}
            float translateX;
            float translateZ;
            int pointIndex;
            std::vector<glm::vec3> verticesRoad;
            float dist;
            float angle;
            int colorType;
        };

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderScene();
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3 color) ;
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        implemented::CameraTema* camera;
        Shader* shader;
        bool renderCameraTarget;
        ViewportArea miniViewportArea;
        glm::mat4 projectionMatrix;
        GLenum polygonMode;
        float translateX = 0, translateY = 0.01, translateZ = 0;
        float cameraX = 0, cameraY = 0.4, cameraZ = 1.2;
        float speed = 2;

        float angle = 0;

        std::vector<CarOponent> carsOponent
        {
            CarOponent(),
            CarOponent(),
            CarOponent(),
            CarOponent(),
            CarOponent(),
            CarOponent()
        };


        std::vector<VertexFormat> verticesInternExtern;
        float y = 0.02;
        std::vector<glm::vec3> verticesDense;
        std::vector<glm::vec3> vertices =
        {
            glm::vec3(0, y, 0),
            glm::vec3(-0.378789, y, 0.553562),
            glm::vec3(-0.910257, y, 1.19132),
            glm::vec3(-1.33543, y, 1.75822),
            glm::vec3(-1.68974, y, 2.46685),
            glm::vec3(-2.00863, y, 3.17547),
            glm::vec3(-2.36294, y, 4.02582),
            glm::vec3(-2.75268, y, 4.80531),
            glm::vec3(-3.03613, y, 5.54936),
            glm::vec3(-3.17786, y, 6.39971),
            glm::vec3(-3.53217, y, 7.07291),
            glm::vec3(-4, y, 8),
            glm::vec3(-4.24079, y, 8.77361),
            glm::vec3(-4.45338, y, 9.62395),
            glm::vec3(-4.27622, y, 15.2575),
            glm::vec3(-4, y, 16),
            glm::vec3(-3.4613, y, 16.9582),
            glm::vec3(-3.03799, y, 17.7221),
            glm::vec3(-2.61207, y, 18.0948),
            glm::vec3(-1.94657, y, 18.6005),
            glm::vec3(-1.41417, y, 18.8934),
            glm::vec3(-0.881774, y, 19.0797),
            glm::vec3(0.502466, y, 19.4524),
            glm::vec3(1.08811, y, 19.5056),
            glm::vec3(2.12629, y, 19.1063),
            glm::vec3(2.49897, y, 18.8401),
            glm::vec3(3.77673, y, 17.7487),
            glm::vec3(4.95605, y, 16.4794),
            glm::vec3(5.10823, y, 16.2857),
            glm::vec3(5.42643, y, 15.8569),
            glm::vec3(6, y, 15),
            glm::vec3(6.13202, y, 14.7639),
            glm::vec3(7.13239, y, 13.0964),
            glm::vec3(7.94286, y, 11.6384),
            glm::vec3(8.21621, y, 11.0527),
            glm::vec3(8.82149, y, 9.86163),
            glm::vec3(9.13389, y, 9.2954),
            glm::vec3(9.85632, y, 7.67481),
            glm::vec3(10.1297, y, 7.05001),
            glm::vec3(10.403, y, 6.44473),
            glm::vec3(10.9888, y, 5.19512),
            glm::vec3(11.3793, y, 4.35554),
            glm::vec3(12.1798, y, 2.9302),
            glm::vec3(12.707, y, 2.26635),
            glm::vec3(13, y, 2),
            glm::vec3(13.2147, y, 1.56344),
            glm::vec3(13.6833, y, 0.938636),
            glm::vec3(14.0542, y, 0.391931),
            glm::vec3(14.8221, y, -1.62294),
            glm::vec3(15.2081, y, -2.97418),
            glm::vec3(15.324, y, -3.82353),
            glm::vec3(15.1309, y, -8.22472),
            glm::vec3(14.881, y, -9.74955),
            glm::vec3(13.7164, y, -12.498),
            glm::vec3(13.2971, y, -13.2433),
            glm::vec3(12.9245, y, -14.0818),
            glm::vec3(12.4586, y, -14.8271),
            glm::vec3(11.9462, y, -15.3861),
            glm::vec3(11.0611, y, -16.1314),
            glm::vec3(10.409, y, -16.9699),
            glm::vec3(9.80339, y, -17.6221),
            glm::vec3(9.10464, y, -18.0414),
            glm::vec3(8.03323, y, -18.6469),
            glm::vec3(7.38106, y, -19.0196),
            glm::vec3(6.12331, y, -19.4389),
            glm::vec3(5.19165, y, -19.6252),
            glm::vec3(4.25999, y, -19.7184),
            glm::vec3(3.00224, y, -19.532),
            glm::vec3(2.02399, y, -19.5786),
            glm::vec3(1.09233, y, -19.3923),
            glm::vec3(0.253829, y, -19.2059),
            glm::vec3(-0.584669, y, -19.1128),
            glm::vec3(-1.56292, y, -18.8799),
            glm::vec3(-2.68091, y, -18.6935),
            glm::vec3(-3.84549, y, -18.3674),
            glm::vec3(-4.77716, y, -18.0414),
            glm::vec3(-6.08149, y, -17.4358),
            glm::vec3(-6.68707, y, -16.9234),
            glm::vec3(-7.47899, y, -16.2246),
            glm::vec3(-8.22432, y, -15.4327),
            glm::vec3(-9.24915, y, -14.4545),
            glm::vec3(-10.1711, y, -13.5409),
            glm::vec3(-10.8459, y, -12.4724),
            glm::vec3(-11.7457, y, -11.4038),
            glm::vec3(-12.3643, y, -10.2791),
            glm::vec3(-13.3766, y, -9.04184),
            glm::vec3(-14.1639, y, -7.57966),
            glm::vec3(-14.8388, y, -6.39866),
            glm::vec3(-15.8511, y, -5.21767),
            glm::vec3(-16.4135, y, -3.98043),
            glm::vec3(-17.0321, y, -2.46201),
            glm::vec3(-17.7632, y, -0.437448),
            glm::vec3(-18.438, y, 1.53088),
            glm::vec3(-18.6067, y, 3.61168),
            glm::vec3(-18.7192, y, 5.86119),
            glm::vec3(-18.7754, y, 7.54833),
            glm::vec3(-18.4943, y, 11.5412),
            glm::vec3(-18.1568, y, 13.622),
            glm::vec3(-17.8756, y, 15.4779),
            glm::vec3(-16.301, y, 16.1527),
            glm::vec3(-14.9513, y, 15.7028),
            glm::vec3(-13.6016, y, 14.803),
            glm::vec3(-12.5893, y, 13.622),
            glm::vec3(-11.9707, y, 12.2723),
            glm::vec3(-10.9584, y, 10.5852),
            glm::vec3(-10.2835, y, 9.29171),
            glm::vec3(-9.43996, y, 7.942),
            glm::vec3(-8.70887, y, 6.47981),
            glm::vec3(-8.09025, y, 5.07386),
            glm::vec3(-7.69659, y, 3.89287),
            glm::vec3(-6.96549, y, 2.43068),
            glm::vec3(-6.34688, y, 1.36216),
            glm::vec3(-5.7845, y, 0.237406),
            glm::vec3(-5.27836, y, -0.6624),
            glm::vec3(-4.71598, y, -1.56221),
            glm::vec3(-3.98489, y, -2.7432),
            glm::vec3(-3.08508, y, -3.58677),
            glm::vec3(-1.90409, y, -3.9242),
            glm::vec3(-0.329425, y, -2.91192),
            glm::vec3(0.457906, y, -1.16854),
            glm::vec3(0, y, 0),
            glm::vec3(-0.378789, y, 0.553562)
        };

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
