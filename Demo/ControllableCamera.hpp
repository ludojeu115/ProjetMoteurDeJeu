//
// Created by ludojeu115 on 24/05/2023.
//

#ifndef MOTEUR_DE_JEU_CONTROLLABLECAMERA_HPP
#define MOTEUR_DE_JEU_CONTROLLABLECAMERA_HPP

#include "common/Material/User_Materials/HeightMap/heightmap.hpp"
#include "common/Object/MeshObject/meshObject.hpp"
#include "common/Material/Custom/custom.hpp"
#include "common/Object/Camera/camera.hpp"
#include "common/Game/Game.hpp"
#include "common/Shaders/shader.hpp"

class ControllableCamera : public Camera{
private:
    InputController* iC = nullptr;
public:
    ControllableCamera(GLFWwindow* window, glm::vec3 position, float pitch, float yaw) : Camera(window, position, pitch, yaw) {}
    void update(double delta) override;
};

#endif //MOTEUR_DE_JEU_CONTROLLABLECAMERA_HPP
