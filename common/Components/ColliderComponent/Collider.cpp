//
// Created by ludojeu115 on 24/05/2023.
//

#include "Collider.hpp"

ColliderType Collider::getColliderType() const {
    return colliderType;
}

Collider::Collider(bool isRigidBody, bool isTrigger) {
    this->name = "Collider";
    this->constraint = isRigidBody;
    this->triggerZone = isTrigger;
}

bool Collider::isConstraint() const {
    return this->constraint;
}

bool Collider::isTrigger() const {
    return this->triggerZone;
}

collisionInfo Collider::testCollision(Collider *other) {
    switch (other->getColliderType()) {
        case ColliderType::TRIANGLE:
            return this->testCollisionTriangle((TriangleCollider *) other);
        case ColliderType::SPHERE:
            return this->testCollisionSphere((SphereCollider *) other);
        case ColliderType::CAPSULE:
            return this->testCollisionCapsule((CapsuleCollider *) other);
        case ColliderType::VOXELS:
            return this->testCollisionVoxels((VoxelsCollider *) other);
        case ColliderType::PLANE:
            return this->testCollisionPlane((PlaneCollider *) other);
        default:
            return {};
    }
}


glm::vec3 Collider::getGlobalPosition() const {
    if (this->owner != nullptr) {
        return this->owner->getGlobalPosition();
    } else {
        return glm::vec3(0.0f);
    }
}

void Collider::onTrigger(Collider *pCollider) {
    if (this->onCollisionEnter != nullptr) {
        this->onCollisionEnter(pCollider);
    }
}

void Collider::setOnCollisionEnter(const std::function<void(Collider *)> &onCollisionEnter) {
    Collider::onCollisionEnter = onCollisionEnter;
}
