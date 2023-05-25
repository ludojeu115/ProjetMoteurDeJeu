#ifndef MESH_OBJECT_HPP
#define MESH_OBJECT_HPP
#include "common/Object/object.hpp"
#include "common/Components/MeshRenderer/meshRenderer.hpp"
class MeshObject : public Object
{
public:
    MeshObject(Mesh *newMesh, Material* newMaterial);


};
#endif //MESH_OBJECT_HPP
