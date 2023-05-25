#include "meshRenderer.hpp"
void Component_MeshRenderer::setMesh(Mesh *newMesh) { this->mesh = newMesh; }

void Component_MeshRenderer::setMaterial(Material *newMaterial) { this->material = newMaterial; }

void Component_MeshRenderer::onDraw() {
    std::array<glm::mat4*,3> MVP = owner->getMVPMatrices();
    glm::mat4 *modelMatrix = MVP[0];
    glm::mat4 *viewMatrix = MVP[1];
    glm::mat4 *projectionMatrix = MVP[2];

    material->bindShader();
    GLuint shader = material->getShader();
    material->bindTextures();
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &(*modelMatrix)[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &(*viewMatrix)[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &(*projectionMatrix)[0][0]);
    mesh->draw();

}



void Component_MeshRenderer::onInit() {

}

void Component_MeshRenderer::onLoad() {

}

void Component_MeshRenderer::onStep(double delta) {

}

Component_MeshRenderer::~Component_MeshRenderer() = default;



Component_MeshRenderer::Component_MeshRenderer(Mesh *newMesh, Material *newMaterial) : mesh(newMesh), material(newMaterial){
    this->name = "MeshRenderer";
}

Component *Component_MeshRenderer::clone() {
    return new Component_MeshRenderer(mesh,material);
}


