#include "mesh.hpp"

[[maybe_unused]] Mesh* createPlane(const unsigned int resolution = 16, const float size = 1.0f)
{
    std::vector<unsigned int> indices;
    std::vector<std::vector<unsigned int>> triangles;
    std::vector<glm::vec3> indexed_vertices, indexed_normals;
    std::vector<glm::vec2> uvs;
    //créer les sommets
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j < resolution; j++) {
            indexed_vertices.emplace_back(((float) j / (float) (resolution - 1) - 0.5f) * size,
                                          0.0f,
                                          ((float) i / (float) (resolution - 1) - 0.5f) * size);
            indexed_normals.emplace_back(0, 1, 0);
            uvs.emplace_back((float) j / (float) (resolution - 1), (float) i / (float) (resolution - 1));
        }
    }
    // créer les triangles
    for (size_t i = 0; i < resolution - 1; i++) {
        for (size_t j = 0; j < resolution - 1; j++) {
            indices.push_back(i * resolution + j);
            indices.push_back(i * resolution + j + 1);
            indices.push_back((i + 1) * resolution + j);

            indices.push_back(i * resolution + j + 1);
            indices.push_back((i + 1) * resolution + j + 1);
            indices.push_back((i + 1) * resolution + j);
        }
    }
    Mesh* plane = new Mesh("plane", indexed_vertices, indices);
    plane->setNormals(indexed_normals);
    plane->setUvs(uvs);
    plane->bind();
    return plane;
}
[[maybe_unused]] Mesh* createSphere(const unsigned int resolution = 16, const float radius = 1.0f)
{
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> indexed_vertices, indexed_normals;
    std::vector<glm::vec2> uvs;
    const float pi = glm::pi<float>();
    const float twicePi = 2.0f * pi;
    const float deltaPhi = pi / resolution;
    const float deltaTheta = twicePi / resolution;
    // créer les sommets
    for (unsigned int i = 0; i <= resolution; i++) {
        const float phi = i * deltaPhi;
        const float sinPhi = std::sin(phi);
        const float cosPhi = std::cos(phi);
        for (unsigned int j = 0; j <= resolution; j++) {
            const float theta = j * deltaTheta;
            const float sinTheta = std::sin(theta);
            const float cosTheta = std::cos(theta);
            const glm::vec3 vertex(radius * sinPhi * cosTheta,
                                   radius * sinPhi * sinTheta,
                                   radius * cosPhi);
            indexed_vertices.push_back(vertex);
            const glm::vec3 normal = glm::normalize(vertex);
            indexed_normals.push_back(normal);
            uvs.push_back(glm::vec2(static_cast<float>(j) / resolution, static_cast<float>(i) / resolution));
        }
    }
    // créer les triangles
    for (unsigned int i = 0; i < resolution; i++) {
        for (unsigned int j = 0; j < resolution; j++) {
            const unsigned int a = i * (resolution + 1) + j;
            const unsigned int b = a + 1;
            const unsigned int c = (i + 1) * (resolution + 1) + j;
            const unsigned int d = c + 1;
            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(d);
            indices.push_back(a);
            indices.push_back(d);
            indices.push_back(c);
        }
    }
    Mesh* sphere = new Mesh("sphere", indexed_vertices, indices);
    sphere->setNormals(indexed_normals);
    sphere->setUvs(uvs);
    sphere->bind();
    return sphere;
}


void Mesh::draw()
{


    // Draw the triangles !
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

    glDrawElements(
            GL_TRIANGLES,      // mode
            indices.size(),    // count
            GL_UNSIGNED_INT, // type
            (void *)nullptr          // element array buffer offset
    );

    glBindVertexArray(0);

}

void Mesh::bind()
{
    glBindVertexArray(VAO);
//    std::cout<< "Vertex Buffer: "<< vertexBuffer << " Element Buffer: " << elementBuffer << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

    // 1rst attribute buffer : vertices

    glVertexAttribPointer(
            0,        // attribute
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)nullptr // array buffer offset
    );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);


    glVertexAttribPointer(
            1,        // attribute
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)nullptr // array buffer offset
    );
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, UVBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    // Index buffer
    // 2nd attribute buffer : UVs

    glVertexAttribPointer(
            2,        // attribute
            2,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)nullptr // array buffer offset
    );
    glEnableVertexAttribArray(2);

    // Generate a buffer for the indices as well

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glBindVertexArray(0);


}

void Mesh::delBuffers() {
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &normalBuffer);
    glDeleteBuffers(1, &UVBuffer);
    glDeleteBuffers(1, &elementBuffer);
    vertexBuffer = 0;
    normalBuffer = 0;
    UVBuffer = 0;
    elementBuffer = 0;
    VAO = 0;
}

void Mesh::genBuffers() {
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &normalBuffer);
    glGenBuffers(1, &UVBuffer);
    glGenBuffers(1, &elementBuffer);

}

Mesh::Mesh() : name("default"){
    genBuffers();
}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices) : name("default")
{
    this->indices = std::move(indices);
    this->indexed_vertices = std::move(vertices);
    genBuffers();
}

Mesh::Mesh(std::string name, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices) : name(std::move(name))
{
    this->indices = std::move(indices);
    this->indexed_vertices = std::move(vertices);
    genBuffers();
}

void Mesh::applyHeightMap(const std::string& path, float scale) {
    Texture tex(path);
    for (size_t i = 0; i < indexed_vertices.size(); i++)
        indexed_vertices[i] += scale * tex.getPixel((int)(uvs[i].x * (float)tex.getWidth()),
                                                    (int)(uvs[i].y * (float)tex.getHeight()) ).r * indexed_normals[i];
    this->bind();
}
