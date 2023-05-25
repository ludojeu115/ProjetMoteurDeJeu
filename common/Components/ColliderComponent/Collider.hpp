#ifndef MOTEUR_DE_JEU_COLLIDER_HPP
#define MOTEUR_DE_JEU_COLLIDER_HPP

#include <functional>
#include "common/Components/physicsComponent.hpp"
enum ColliderType {
    TRIANGLE,
    PLANE,
    SPHERE,
    CAPSULE,
    VOXELS
};
class Collider;
class TriangleCollider;
class SphereCollider;
class CapsuleCollider;
class VoxelsCollider;
class PlaneCollider;



struct collisionInfo {
    bool isColliding = false;
    Collider * collider1;//the collider that compute the collision, normal is linked to it
    Collider * collider2;
    glm::vec3 collisionPoint;
    glm::vec3 collisionNormal;
    float penetration = 0.0f;//used to move the object out of the collision

    collisionInfo( bool isColliding,Collider * collider1, Collider * collider2, glm::vec3 collisionPoint, glm::vec3 collisionNormal, float penetration){
        this->isColliding = isColliding;
        this->collider1 = collider1;
        this->collider2 = collider2;
        this->collisionPoint = collisionPoint;
        this->collisionNormal = collisionNormal;
        this->penetration = penetration;
    }
    collisionInfo(){
        this->isColliding = false;
        this->collider1 = nullptr;
        this->collider2 = nullptr;
        this->collisionPoint = glm::vec3(0.0f);
        this->collisionNormal = glm::vec3(0.0f);
        this->penetration = 0.0f;
    }
};

class Collider : public virtual Component {
protected:
    ColliderType colliderType;
    bool constraint = false;
    bool triggerZone = false;
    virtual collisionInfo testCollisionTriangle(TriangleCollider * other) = 0;
    virtual collisionInfo testCollisionSphere(SphereCollider * other) = 0;
    virtual collisionInfo testCollisionCapsule(CapsuleCollider * other) = 0;
    virtual collisionInfo testCollisionVoxels(VoxelsCollider * other) = 0;
    virtual collisionInfo testCollisionPlane(PlaneCollider * other) = 0;
    glm::vec3 getGlobalPosition() const;
    std::function<void(Collider *)> onCollisionEnter = nullptr;
public:
    void setOnCollisionEnter(const std::function<void(Collider *)> &onCollisionEnter);

public:
    ColliderType getColliderType() const;
    Collider( bool isRigidBody = false, bool isTrigger = false);
    bool isConstraint() const;
    bool isTrigger() const;
    virtual float getLowestPoint() = 0;

    collisionInfo testCollision(Collider * other);


    void onTrigger(Collider *pCollider);
};


#endif //MOTEUR_DE_JEU_COLLIDER_HPP
