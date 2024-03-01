#pragma once;

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

#include "Tema2.h"


namespace elements
{
    Mesh* CreateRectangle(const std::string& name, float length, glm::vec3 color);
    Mesh* CreateParallelipiped(const std::string& name, float length, glm::vec3 color);
    Mesh* CreateCube(const std::string& name, float length, glm::vec3 color);
    Mesh* CreateRoad(const std::string& name, std::vector<VertexFormat> verticesInternExtern);
    std::vector<VertexFormat> GetVerticesInternExtern(std::vector<glm::vec3> vertices, glm::vec3 color);
    bool IsOnRoad(glm::vec3 point, std::vector<glm::vec3> vertices, float distance);
    void MoveOponentCar(std::vector<glm::vec3> vertices,
        float &translateX, float &translateZ, int &i, float &angle);
    std::vector<glm::vec3> GetOponentRoad(std::vector<glm::vec3> vertices, float dist);
    std::vector<glm::vec3> GetDenseVertices(std::vector<glm::vec3> vertices);
    bool IsHitCar(glm::vec3 point, std::vector<m1::Tema2::CarOponent> carsOponent, float minDistance);
}
