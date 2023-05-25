//
// Created by ludojeu115 on 24/05/2023.
//
#include "common/Game/Game.hpp"
#include "myCharacterController.hpp"


void myCharacterController::onStep(double delta) {
    CharacterController::onStep(delta);

    if(this->loaded != true)
        return;

    if (iC->isKEYPressed(GLFW_KEY_W))
        this->move({0,1});
    if (iC->isKEYPressed(GLFW_KEY_S))
        this->move({0,-1});
    if (iC->isKEYPressed(GLFW_KEY_A))
        this->move({1,0});
    if (iC->isKEYPressed(GLFW_KEY_D))
        this->move({-1,0});

}

void myCharacterController::onLoad() {

    iC = this->owner->getGame()->getInputController();

    iC->setCallbackKEYOnPressed(GLFW_KEY_SPACE,
                                [this](GLFWwindow*){

                                    this->jump();
    });

    Component::onLoad();
}
