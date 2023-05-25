#include "ControllableCamera.hpp"

void ControllableCamera::update(double delta) {
    Camera::update(delta);
    if (this->game == nullptr) return;

    iC = this->game->getInputController();

    if (iC == nullptr) return;

    //Move the camera
    if (iC->isKEYPressed(GLFW_KEY_UP))
        moveCamera({0, 1, 0}, delta);
    if (iC->isKEYPressed(GLFW_KEY_DOWN))
        moveCamera({0,-1,0},delta);
    if (iC->isKEYPressed(GLFW_KEY_LEFT))
        moveCamera({-1,0,0},delta);
    if (iC->isKEYPressed(GLFW_KEY_RIGHT))
        moveCamera({1,0,0},delta);

    //Rotate the camera
    if (iC->isKEYPressed(GLFW_KEY_I))
        turnCamera(0,1,delta);
    if (iC->isKEYPressed(GLFW_KEY_K))
        turnCamera(0,-1,delta);
    if (iC->isKEYPressed(GLFW_KEY_J))
        turnCamera(1,0,delta);
    if (iC->isKEYPressed(GLFW_KEY_L))
        turnCamera(-1,0,delta);

    //"Zoom" the camera
    if (iC->getScrollYAxis() != 0){
        moveCamera({0,0,iC->getScrollYAxis()*10},delta);
    }


}
