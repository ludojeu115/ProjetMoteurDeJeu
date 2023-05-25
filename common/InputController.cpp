#include <iostream>
#include "InputController.hpp"

#define NB_KEY_INPUT 400

void InputController::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    scrollXAxis = (float) xOffset;
    scrollYAxis = (float) yOffset;
}

void InputController::setCallbackKEYOnPressed(unsigned int KEY, std::function<void(GLFWwindow*)> callback) {
    this->callbacksOnPressed[KEY] = callback;
}

void InputController::setCallbackKEYOnRelease(unsigned int KEY, std::function<void(GLFWwindow*)> callback) {
    this->callbacksOnRelease[KEY] = callback;

}


bool InputController::isKEYPressed(unsigned int KEY) {
    return this->isPressed[KEY];
}

void InputController::update(float delta) {
    if (this->scrollXAxis < 0) {
        this->scrollXAxis = std::min(0.f, this->scrollXAxis + this->scroll_deceleration * delta);
    } else if (this->scrollXAxis > 0) {
        this->scrollXAxis = std::max(0.f, this->scrollXAxis - this->scroll_deceleration * delta);
    }
    if (this->scrollYAxis < 0) {
        this->scrollYAxis = std::min(0.f, this->scrollYAxis + this->scroll_deceleration * delta);
    } else if (this->scrollYAxis > 0) {
        this->scrollYAxis = std::max(0.f, this->scrollYAxis - this->scroll_deceleration * delta);
    }


}

void InputController::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (!isPressed[key] && action == GLFW_PRESS) {
        //std::cout << "key pressed : " << key << std::endl;
        isPressed[key] = true;
        if (this->callbacksOnPressed[key] != nullptr) {
            this->callbacksOnPressed[key](window);
        }
        return;
    }
    if (isPressed[key] && action == GLFW_RELEASE) {
        isPressed[key] = false;
        if (this->callbacksOnRelease[key] != nullptr) {
            this->callbacksOnRelease[key](window);
        }
        return;
    }
}

InputController::InputController(GLFWwindow *window) {
    this->window = window;
    glfwSetWindowUserPointer(window, this);

    //allow to call inside the class
    auto funcKEY = [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto *inputController = static_cast<InputController *>(glfwGetWindowUserPointer(window));
        inputController->key_callback(window, key, scancode, action, mods);
    };
    glfwSetKeyCallback(window, funcKEY);// funcKEY -> this->key_callback

    //allow to call inside the class
    auto funcScroll = [](GLFWwindow *window, double xoffset, double yoffset) {
        auto *inputController = static_cast<InputController *>(glfwGetWindowUserPointer(window));
        inputController->scrollCallback(window, xoffset, yoffset);
    };

    glfwSetScrollCallback(window, funcScroll);// funcSroll -> this->scrollCallback


    //create a map of all the key
    for (int i = 0; i < NB_KEY_INPUT; i++) {
        this->isPressed[i] = false;
        this->callbacksOnPressed[i] = nullptr;
        this->callbacksOnRelease[i] = nullptr;
    }


}

bool InputController::isScrolling() {
    return scrollXAxis != 0 || scrollYAxis != 0;
}

float InputController::getScrollXAxis() {
    return this->scrollXAxis;
}

float InputController::getScrollYAxis() {
    return this->scrollYAxis;
}

/*
void InputController::setGame(Game *game) {
    this->game = game;
}

Game *InputController::getGame() {
    return this->game;
}
*/

