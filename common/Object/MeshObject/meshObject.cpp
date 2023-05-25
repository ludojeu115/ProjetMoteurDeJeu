#include "meshObject.hpp"

MeshObject::MeshObject(Mesh *newMesh, Material* newMaterial) {
    Component_MeshRenderer* meshRenderer = new Component_MeshRenderer(newMesh,newMaterial);
    this->addComponent(meshRenderer);

}
