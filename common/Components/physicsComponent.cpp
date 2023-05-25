#include <iostream>
#include "physicsComponent.hpp"

void PhysicsComponent::computeAcceleration() {
    this->acceleration = this->force_to_apply / this->mass;
}

void PhysicsComponent::computeVelocity() {
    this->velocity += this->acceleration ;
}

void PhysicsComponent::computePosition(double physic_delta) {
    this->owner->translate(this->velocity * (float)physic_delta);
}

void PhysicsComponent::setMass(float newMass) {
    this->mass = newMass;
}

float PhysicsComponent::getMass() const {
    return this->mass;
}


void PhysicsComponent::onPhysicStep(double physic_delta) {



    this->computeAcceleration();
    this->computeVelocity();
    this->computePosition(physic_delta);

    this->force_to_apply = glm::vec3(0.0f, 0.0f, 0.0f);
    //gravity

}





void PhysicsComponent::addForce(glm::vec3 force) {
    this->force_to_apply += force;
}

PhysicsComponent::PhysicsComponent() {
    this->name = "PhysicsComponent";
}

float PhysicsComponent::getBouncyness() const {
    return bouncyness;
}

const glm::vec3 &PhysicsComponent::getVelocity() const {
    return velocity;
}

