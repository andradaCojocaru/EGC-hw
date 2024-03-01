#include "elements.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include "Tema2.h"

Mesh* elements::CreateRectangle(
    const std::string& name,
    float length,
    glm::vec3 color)
{
    float y = 0.1;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-length, y,  -length), color),
        VertexFormat(glm::vec3(length, y,  -length), color),
        VertexFormat(glm::vec3(-length, y,  length), color),
        VertexFormat(glm::vec3(length, y,  length), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 1, 2, 3 };

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* elements::CreateParallelipiped(
    const std::string& name,
    float length,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 0,  0), color),
        VertexFormat(glm::vec3(length / 2, 0,  0), color),
        VertexFormat(glm::vec3(length / 2, length / 2,  0), color),
        VertexFormat(glm::vec3(0, length / 2,  0), color),
        VertexFormat(glm::vec3(0, 0,  length), color),
        VertexFormat(glm::vec3(length / 2, 0,  length), color),
        VertexFormat(glm::vec3(length / 2, length / 2,  length), color),
        VertexFormat(glm::vec3(0, length / 2,  length), color)
    };

    Mesh* parallelipiped = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 5, 1,
        0, 4, 5,
        0, 7, 4,
        0, 3, 7,
        3, 6, 7,
        3, 2, 6,
        2, 5, 6,
        2, 1, 5,
        0, 1, 2,
        0, 2, 3,
        4, 6, 5,
        4, 7, 6 };

    parallelipiped->InitFromData(vertices, indices);
    return parallelipiped;
}

Mesh* elements::CreateCube(
    const std::string& name,
    float length,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 0,  0), color),
        VertexFormat(glm::vec3(length, 0,  0), color),
        VertexFormat(glm::vec3(length, length,  0), color),
        VertexFormat(glm::vec3(0, length,  0), color),
        VertexFormat(glm::vec3(0, 0,  length), color),
        VertexFormat(glm::vec3(length, 0,  length), color),
        VertexFormat(glm::vec3(length, length,  length), color),
        VertexFormat(glm::vec3(0, length,  length), color)
    };

    Mesh* cube = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 5, 1,
        0, 4, 5,
        0, 7, 4,
        0, 3, 7,
        3, 6, 7,
        3, 2, 6,
        2, 5, 6,
        2, 1, 5,
        0, 1, 2,
        0, 2, 3,
        4, 6, 5,
        4, 7, 6 };

    cube->InitFromData(vertices, indices);
    return cube;
}

std::vector<VertexFormat> elements::GetVerticesInternExtern(std::vector<glm::vec3> vertices, glm::vec3 color)
{
    glm::vec3 D, P, UP, R, A;
    float distExtern = 1;
    float distItern = 1;
    UP = glm::vec3(0, 1, 0);

    D = vertices[1] - vertices[0];
    P = glm::normalize(glm::cross(D, UP));
    R = vertices[0] + distItern * P;
    A = vertices[0] - distExtern * P;

    std::vector<VertexFormat> verticesInternExtern =
    {
        VertexFormat(R, color), // first point intern
        VertexFormat(A, color) // first point extern
    };

    for (int i = 1; i < vertices.size() - 1; i++) { // am 120 de puncte in multime
        D = vertices[i + 1] - vertices[i];
        P = glm::normalize(glm::cross(D, UP));
        R = vertices[i] + distItern * P;
        A = vertices[i] - distExtern * P;
        verticesInternExtern.push_back(VertexFormat(R, color));
        verticesInternExtern.push_back(VertexFormat(A, color));
        R = vertices[i + 1] + distItern * P;
        A = vertices[i + 1] - distExtern * P;
        verticesInternExtern.push_back(VertexFormat(R, color));
        verticesInternExtern.push_back(VertexFormat(A, color));
    }

    D = vertices[0] - vertices[vertices.size() - 1];
    P = glm::normalize(glm::cross(D, UP));
    R = vertices[vertices.size() - 1] + distItern * P;
    A = vertices[vertices.size() - 1] - distExtern * P;
    verticesInternExtern.push_back(VertexFormat(R, color));
    verticesInternExtern.push_back(VertexFormat(A, color));
    R = vertices[0] + distItern * P;
    A = vertices[0] - distExtern * P;
    verticesInternExtern.push_back(VertexFormat(R, color));
    verticesInternExtern.push_back(VertexFormat(A, color));

    return verticesInternExtern;
}

std::vector<glm::vec3> elements::GetDenseVertices(std::vector<glm::vec3> vertices)
{
    glm::vec3 D;

    std::vector<glm::vec3> verticesDense =
    {
        vertices[0]
    };

    for (int i = 0; i < vertices.size() - 1; i++) { 
        D = vertices[i + 1] - vertices[i];
        for (int j = 0; j < 100; j++) {
            verticesDense.push_back(vertices[i] + (float)(j / 100.0) * D);
        }
    }


    return verticesDense;
}

std::vector<glm::vec3> elements::GetOponentRoad(std::vector<glm::vec3> vertices, float dist)
{
    glm::vec3 D, P, UP, R, A;
    UP = glm::vec3(0, 1, 0);

    D = vertices[1] - vertices[0];
    P = glm::normalize(glm::cross(D, UP));
    R = vertices[0] + dist * P;

    std::vector<glm::vec3> verticesRoad =
    {
        glm::vec3(R), // first point intern
        glm::vec3(D)
    };

    for (int i = 1; i < vertices.size() - 1; i++) {
        D = vertices[i + 1] - vertices[i];
        P = glm::normalize(glm::cross(D, UP));
        R = vertices[i] + dist * P;
        verticesRoad.push_back(glm::vec3(R));
        verticesRoad.push_back(glm::vec3(D));

    }

    D = vertices[0] - vertices[vertices.size() - 1];
    P = glm::normalize(glm::cross(D, UP));
    R = vertices[vertices.size() - 1] + dist * P;
    verticesRoad.push_back(glm::vec3(R));
    verticesRoad.push_back(glm::vec3(D));
    return verticesRoad;
}

void elements::MoveOponentCar(std::vector<glm::vec3> vertices,
    float& translateX, float& translateZ, int& i, float& angle)
{
    if (i >= vertices.size() - 180) {
        i = 0;
    }
    angle = acos(glm::dot(glm::vec3(1, 0, 0), glm::normalize(vertices[i + 1])));
    if (vertices[i + 1].z > 0) {
        angle = 2 * M_PI - angle;
    }
    angle += M_PI_2;


    translateX = vertices[i].x;
    translateZ = vertices[i].z;
    i += 6;
}

Mesh* elements::CreateRoad(
    const std::string& name,
    std::vector<VertexFormat> verticesInternExtern)
{
    Mesh* road = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 1; i < verticesInternExtern.size() - 2; i += 2) {
        indices.push_back(i - 1); // r1
        indices.push_back(i + 2); // a2
        indices.push_back(i); // a1

        indices.push_back(i - 1); // r1
        indices.push_back(i + 1); // r2
        indices.push_back(i + 2); // a2
    }

    indices.push_back(verticesInternExtern.size() - 2); // r1
    indices.push_back(1); // a2
    indices.push_back(verticesInternExtern.size() - 1); // a1

    indices.push_back(verticesInternExtern.size() - 2); // r1
    indices.push_back(0); // r2
    indices.push_back(1); // a2

    road->InitFromData(verticesInternExtern, indices);
    return road;
}

bool elements::IsOnRoad(glm::vec3 point, std::vector<glm::vec3> vertices, float minDistance) {
    for (int i = 0; i < vertices.size(); i++) {
        float dist = glm::distance(vertices[i], point);
        if (dist < minDistance) {
            return true;
        }
    }
    return false;
}

bool elements::IsHitCar(glm::vec3 point, std::vector<m1::Tema2::CarOponent> carsOponent, float minDistance) {
    for (int i = 0; i < carsOponent.size(); i++) {
        float dist = glm::distance(glm::vec3(carsOponent[i].translateX, 0.01, carsOponent[i].translateZ), point);
        if (dist < minDistance) {
            return true;
        }
    }
    return false;
}



