#include "characterController.hpp"
#include <iostream>
void CharacterController::jump() {
    if(this->isGrounded()){
        this->addForce({0, this->jumpForce, 0});
    }
}




Component *CharacterController::clone() {
    return new CharacterController();
}

void CharacterController::onPhysicStep(double physic_delta) {
    Gravity::onPhysicStep(physic_delta);
    if(this->moving){

        glm::normalize(this->movingTo);
        if(this->isGrounded()) this->addForce(this->movingTo*(float)this->speed); else this->addForce(this->movingTo*(float)this->speed*(float)this->airSpeed);
    }
    this->moving = false;
    this->movingTo = glm::vec3(0,0,0);
}

void CharacterController::move(glm::vec2 direction) {
    this->movingTo += glm::vec3 (direction[0],0,direction[1]);
    this->moving = true;
}

CharacterController::CharacterController() {
    this->gravity = 9.8f;
}
