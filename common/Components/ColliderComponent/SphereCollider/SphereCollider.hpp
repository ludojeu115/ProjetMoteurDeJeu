//
// Created by ludojeu115 on 24/05/2023.
//

#ifndef MOTEUR_DE_JEU_SPHERECOLLIDER_HPP
#define MOTEUR_DE_JEU_SPHERECOLLIDER_HPP


#include "common/Components/ColliderComponent/Collider.hpp"

class SphereCollider : public Collider{
protected:
    glm::vec3 center;
    double size;
    glm::vec3 getGlobalPosition() const;

    collisionInfo testCollisionSphere(SphereCollider *other) override;

    collisionInfo testCollisionTriangle(TriangleCollider *other) override;

    collisionInfo testCollisionCapsule(CapsuleCollider *other) override;

    collisionInfo testCollisionVoxels(VoxelsCollider *other) override;

    collisionInfo testCollisionPlane(PlaneCollider *other) override;

public:
    SphereCollider();
    SphereCollider(glm::vec3 center, double size);

    float getLowestPoint() override;
};


#endif //MOTEUR_DE_JEU_SPHERECOLLIDER_HPP
