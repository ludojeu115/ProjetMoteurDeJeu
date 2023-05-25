#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#include "common/Mesh/mesh.hpp"
#include "common/Components/drawableComponent.hpp"
class Component_MeshRenderer : public DrawableComponent
{
private:
    Material *material{};
    Mesh *mesh{};
public:
    ~Component_MeshRenderer() override;

    void onInit() override;

    Component *clone() override;

    void onLoad() override;

    void onStep(double delta) override;

    void onDraw() override;

    void setMesh(Mesh *newMesh);
    void setMaterial(Material *newMaterial);
    Component_MeshRenderer(Mesh *newMesh, Material *newMaterial);
};
#endif //MESHRENDERER_H
