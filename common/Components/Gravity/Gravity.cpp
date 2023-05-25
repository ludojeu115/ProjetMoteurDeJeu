//
// Created by ludojeu115 on 24/05/2023.
//

#include <iostream>
#include "Gravity.hpp"
#include "common/Components/ColliderComponent/Collider.hpp"

void Gravity::setGravity(float newGravity) {
    this->gravity = newGravity;
}

float Gravity::getGravity() const {
    return this->gravity;
}

void Gravity::onPhysicStep(double physic_delta) {
    this->computeGrounded();

    //std::cout << "velocity: " << this->velocity[0] << " " << this->velocity[1] << " " << this->velocity[2] << std::endl;

    //std::cout << "onGround: " << this->onGround << std::endl;


    //friction
    if(this->onGround) {
        this->velocity = glm::vec3(
                this->velocity[0] * std::max(0.0f, (1.0f - this->friction * (float) physic_delta)),
                this->velocity[1],
                this->velocity[2] * std::max(0.0f, (1.0f - this->friction * (float) physic_delta)));
        //this->getOwner()->translate(glm::vec3(0.0f, -lowestPoint, 0.0f));
        if(this->velocity[1] > -0.1f && this->velocity[1] < 0.1f) {
            this->velocity[1] = 0.0f;
        }
        if (this->velocity[1] < -0.1f)
            this->bounce(glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else this->addForce(glm::vec3(0.0f, -this->gravity*this->mass*physic_delta, 0.0f));

    //stop if velocity is too low
    if (this->velocity[0] < 0.01f && this->velocity[0] > -0.01f) this->velocity[0] = 0.0f;
    if (this->velocity[2] < 0.01f && this->velocity[2] > -0.01f) this->velocity[2] = 0.0f;


    PhysicsComponent::onPhysicStep(physic_delta);




}


void Gravity::computeGrounded() {
    Collider *collider = dynamic_cast<Collider*>(this->owner->getComponent("Collider"));
    double lowestPoint =  collider!= nullptr ? collider->getLowestPoint() : 0.0;

    if(lowestPoint <= 0.01f && this->velocity[1] <= 0.0f){
        if (!this->onGround) {
            this->onGrounded();
        }
        this->onGround = true;
    }
    else{
        this->onGround = false;

    }
}

bool Gravity::isGrounded() {
    return this->onGround;
}

void Gravity::onGrounded() {



    if (this->velocity[1] < 0.0f) {
        this->bounce(glm::vec3(0.0f, 1.0f, 0.0f));
    }
    //this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);

}

void Gravity::onLoad() {
    this->computeGrounded();
    Component::onLoad();
}

void Gravity::bounce(glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f)) {

    Collider *collider = dynamic_cast<Collider*>(this->owner->getComponent("Collider"));
    float lowestPoint =  collider!= nullptr ? collider->getLowestPoint() : 0.0;

    if(lowestPoint < 0.0f) {
        this->getOwner()->translate(glm::vec3(0.0f, -lowestPoint, 0.0f));

        float dot = glm::dot(this->velocity, normal);
        dot *= -1.0f * (1 + this->bouncyness);
        dot *= this->mass;
        this->addForce(dot * normal);
        this->onGround = false;
    }
}
