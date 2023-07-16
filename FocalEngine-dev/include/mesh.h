#pragma once
#include <iostream>
#include <vector>
#include <vendor/glad/glad.h>
#include <vendor/glm/glm.hpp>
#include <vendor/GLFW/glfw3.h>

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 TexCoord;
    glm::vec3 Normal;
};

class Mesh
{
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int IBO;
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    ~Mesh();
    void RenderMesh();
};