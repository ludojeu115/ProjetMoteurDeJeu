#ifndef MESH_HPP
#define MESH_HPP
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <utility>
#include "common/Texture/texture.hpp"
#include "common/Material/material.hpp"
class Mesh
{
private:
    // Model Data
    std::string name;
    std::vector<unsigned int> indices; // Triangles concaténés dans une liste
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec3> indexed_normals;
    std::vector<glm::vec2> uvs;
    // GL Data
    GLuint vertexBuffer{}, normalBuffer{}, UVBuffer{}, elementBuffer{};
    GLuint VAO{};

    // fonctions Setter
    void genBuffers();
    void delBuffers();

public:
    // variables publiques


    //////////////////////////
    // constructeurs
    Mesh();

    Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);;
    Mesh(std::string name, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);;
    //////////////////////////
    // destructeur
    ~Mesh()
    {
        delBuffers();
    };
    //////////////////////////
    // setters
    [[maybe_unused]] void setName(const std::string& newName) { this->name = newName; };
    [[maybe_unused]] void setIndices(std::vector<unsigned int> newIndices) { this->indices = std::move(newIndices); };
    [[maybe_unused]] void setVertices(std::vector<glm::vec3> vertices) { this->indexed_vertices = std::move(vertices); };
    void setUvs(std::vector<glm::vec2> newUVs) { this->uvs = std::move(newUVs); };
    void setNormals(std::vector<glm::vec3> newNormals) { this->indexed_normals = std::move(newNormals); };

    //////////////////////////
    // Utilitaires
    void applyHeightMap(const std::string& path = "images/heightmap-1024x1024.png", float scale = 1.0);
    //////////////////////////
    // OpenGL functions
    void bind();
    void draw();
};

[[maybe_unused]] Mesh* createPlane(unsigned int resolution, float size);
[[maybe_unused]] Mesh* createSphere(unsigned int resolution, float size);

#endif