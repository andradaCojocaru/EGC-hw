#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/Tema2/elements.h"
#include "lab_m1/Tema2/transform3DTema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    camera = new implemented::CameraTema();
    
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    {
        Mesh* grass = new Mesh("grass");
        grass->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[grass->GetMeshID()] = grass;
    }

    Mesh* carPlayer = elements::CreateParallelipiped("carPlayer", 0.5f, RED);
    AddMeshToList(carPlayer);

    Mesh* trunk = elements::CreateParallelipiped("trunk", 0.5f, BROWN);
    AddMeshToList(trunk);

    Mesh* leaves = elements::CreateCube("leaves", 0.45f, DARK_GREEN);
    AddMeshToList(leaves);

    verticesDense = elements::GetDenseVertices(vertices);

    verticesInternExtern = elements::GetVerticesInternExtern(verticesDense, BLACK);

    Mesh* road = elements::CreateRoad("road", verticesInternExtern);
    AddMeshToList(road);

    for (int i = 0; i < carsOponent.size(); i++) {
        carsOponent[i].dist = (rand() % 3) * 0.25;
        carsOponent[i].verticesRoad = elements::GetOponentRoad(verticesDense, carsOponent[i].dist);
        carsOponent[i].colorType = rand() % 4;
        carsOponent[i].pointIndex = (rand() % 10000) * 2;
    }

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);


    // Create a shader program for drawing face polygon with the color of the normal
    {
        shader = new Shader("TemaShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}

// added color to my render mesh
void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3 color)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glm::mat4 mat = camera->GetViewMatrix();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // uniform for car position
    GLint PosCar = glGetUniformLocation(shader->GetProgramID(), "PosCar");
    glm::vec3 pos = glm::vec3(translateX, translateY, translateZ);
    glUniform3fv(PosCar, 1, glm::value_ptr(pos));

    // uniform for color
    GLint Color = glGetUniformLocation(shader->GetProgramID(), "Color");
    glUniform3fv(Color, 1, glm::value_ptr(color));

    mesh->Render();
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    // sky
   
    glClearColor(0, 0.749, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::RenderScene() {

    // for trees
    float centerX, centerY = 0.3f, centerZ;
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderMesh(meshes["road"], shaders["TemaShader"], modelMatrix, BLACK);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderMesh(meshes["grass"], shaders["TemaShader"], modelMatrix, GREEN);
    }

    // players car
    {
        glm::mat4 modelMatrix= glm::mat4(1);
        modelMatrix *= transform3DTema2::Translate(translateX, translateY, translateZ);
        modelMatrix *= transform3DTema2::RotateOY(angle);
        RenderMesh(meshes["carPlayer"], shaders["TemaShader"], modelMatrix, RED);
    }

    // set what color should the car oponent render
    for (int i = 0; i < carsOponent.size(); i++) {
        CarOponent carOponent = carsOponent[i];
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transform3DTema2::Translate(carOponent.translateX, translateY, carOponent.translateZ);
            modelMatrix *= transform3DTema2::RotateOY(carOponent.angle);
            glm::vec3 color;

            switch (carOponent.colorType) {
            case(0):
                color = WHITE;
                break;
            case(1):
                color = GOLDEN;
                break;
            case(2):
                color = PINK;
                break;
            case(3):
                color = CHOCOLATE_BROWN;
                break;
            default:
                color = CHOCOLATE_BROWN;
            }
            RenderMesh(meshes["carPlayer"], shaders["TemaShader"], modelMatrix, color);
        }
    }

    for (int i = 0; i < vertices.size(); i++) {
        
        centerZ = vertices[i].z;
        if (i % 2 == 0) {
            centerX = vertices[i].x - 2;
        }
        else {
            centerX = vertices[i].x + 2;
        }
        glm::vec3 newPoint = glm::vec3(centerX, centerY, centerZ);

        // if tree is on road try modify centerZ
        if (elements::IsOnRoad(newPoint, vertices, 1.5)) {
            centerX = vertices[i].x;
            if (i % 2 == 0) {
                centerZ = vertices[i].z - 2;
            }
            else {
                centerZ = vertices[i].z + 2;
            }
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transform3DTema2::Translate(centerX, centerY, centerZ);
            modelMatrix *= transform3DTema2::RotateOX(M_PI_2);
            RenderMesh(meshes["trunk"], shaders["TemaShader"], modelMatrix, BROWN);
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix *= transform3DTema2::Translate(centerX - 0.08f, centerY, centerZ - 0.08);
            RenderMesh(meshes["leaves"], shaders["TemaShader"], modelMatrix, DARK_GREEN);
        }
    }
}

void Tema2::Update(float deltaTimeSeconds)
{
    camera->Set(glm::vec3(cameraX, cameraY, cameraZ), glm::vec3(0, 0, 0), glm::vec3(0, 0.1, 0));

    // move camera along with the car
    camera->MoveForward(-translateZ);
    camera->TranslateRight(translateX);

    // rotate camera along with the car
    camera->MoveForward(cameraZ);
    camera->RotateFirstPerson_OY(angle);
    camera->MoveForward(-cameraZ);
    RenderScene();

    FrameEnd();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // set camera for viewport above
    camera->Set(glm::vec3(translateX, 7, translateZ), glm::vec3(translateX, 0, translateZ), glm::vec3(1, 0, 0));

    RenderScene();
}


void Tema2::FrameEnd()
{
    
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float oldAngle = angle;
    // move every oponent car
    for (int i = 0; i < carsOponent.size(); i++) {
        elements::MoveOponentCar(carsOponent[i].verticesRoad,
            carsOponent[i].translateX, carsOponent[i].translateZ, carsOponent[i].pointIndex, carsOponent[i].angle);
    }
    // move player car
    if (window->KeyHold(GLFW_KEY_W)) {
        translateZ -= speed * deltaTime * cos(angle);
        translateX -= speed * deltaTime * sin(angle);
        glm::vec3 point = glm::vec3(translateX, translateY, translateZ);
        if (window->KeyHold(GLFW_KEY_D)) {
            angle -= deltaTime;
        }
        else if (window->KeyHold(GLFW_KEY_A)) {
            angle += deltaTime;
        }

        // verify if is on road and hit be other car
        if (!elements::IsOnRoad(point, verticesDense, 1.0001) ||
            elements::IsHitCar(point, carsOponent, 0.35)) {
            translateZ += speed * deltaTime * cos(angle);
            translateX += speed * deltaTime * sin(angle);
            angle = oldAngle;
        }
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        translateZ += speed * deltaTime * cos(angle);
        translateX += speed * deltaTime * sin(angle);
        if (window->KeyHold(GLFW_KEY_D)) {
            angle += deltaTime;
        }
        else if (window->KeyHold(GLFW_KEY_A)) {
            angle -= deltaTime;
        }
        glm::vec3 point = glm::vec3(translateX + 0.1, translateY, translateZ);
        if (!elements::IsOnRoad(point, verticesDense, 1.0001) ||
            elements::IsHitCar(point, carsOponent, 0.35)) {
            translateZ -= speed * deltaTime * cos(angle);
            translateX -= speed * deltaTime * sin(angle);
            angle = oldAngle;
        }
    }
}


void Tema2::OnKeyPress(int key, int mods)
{

}

void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
