//
// Created by ludojeu115 on 24/05/2023.
//

#include "SphereCollider.hpp"



glm::vec3 SphereCollider::getGlobalPosition() const {
        return Collider::getGlobalPosition() + this->center;
}

collisionInfo SphereCollider::testCollisionSphere(SphereCollider *other) {
    glm::vec3 C1 = this->getGlobalPosition();
    glm::vec3 C2 = other->getGlobalPosition();
    float R1 = this->size;
    float R2 = other->size;
    if (glm::length(C1 - C2) < R1 + R2) {
        return {
                true,
                this,
                other,
                C1 + glm::normalize(C2 - C1) * R1,
                glm::normalize(C1 - C2),
                glm::length(C1 - C2) - R1 - R2
        };
    }
    return {};
}

float SphereCollider::getLowestPoint() {
    return this->getGlobalPosition().y - this->size;
}


SphereCollider::SphereCollider() : Collider() {
    this->colliderType = ColliderType::SPHERE;


}

SphereCollider::SphereCollider(glm::vec3 center, double size) : SphereCollider() {
    this->center = center;
    this->size = size;

}

collisionInfo SphereCollider::testCollisionTriangle(TriangleCollider *other) {
    return {};
}

collisionInfo SphereCollider::testCollisionCapsule(CapsuleCollider *other) {
    return {};
}

collisionInfo SphereCollider::testCollisionVoxels(VoxelsCollider *other) {
    return {};
}

collisionInfo SphereCollider::testCollisionPlane(PlaneCollider *other) {
    return {};
}
