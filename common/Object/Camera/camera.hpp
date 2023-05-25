#ifndef MOTEUR_DE_JEU_CAMERA_HPP
#define MOTEUR_DE_JEU_CAMERA_HPP
#include "common/Object/object.hpp"
#include "glm/glm.hpp"
#include "common/Utilities/Transformation/rotation_utils.hpp"
#include <GLFW/glfw3.h>

enum CameraMode {
    CAMERA_MODE_ORBIT,
    CAMERA_MODE_FREE,
    CAMERA_45_DEGREE_ORBIT
};
class Camera : public Object {
private:
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
    CameraMode camMode = CAMERA_MODE_FREE;
    GLFWwindow* window;

    bool allowCameraMove = true;
    float fieldOfView = 45.0f;
    float DefaultTranslationSpeed = 3.0f; // speed to reset to when changing camera mode
    float DefaultRotationSpeed = 15.5f; // speed to reset to when changing camera mode
    float translationSpeed = DefaultTranslationSpeed;
    float rotationSpeed = DefaultRotationSpeed;



    glm::vec3 constant_free_camera_movement = glm::vec3(0,0,0);
    glm::vec3 constant_orbit_camera_movement = glm::vec3(0,0,0);
    Object * camera_looking_at = nullptr;

    glm::vec3 direction = glm::vec3(0,0,-1);
    glm::vec3 right = glm::vec3(1,0,0);
    glm::vec3 up = glm::vec3(0,1,0);

    void computeAngle();
    void moveCameraFree(float verticalAngle, float horizontalAngle, glm::vec3 translate, float deltaTime);
    void MoveCameraOrbit(float zoom, float up, float right, float deltaTime);
    void MoveCamera45Orbit(float zoom, float increaseSpeed, float deltaTime);

public:
    Camera(GLFWwindow* window);
    Camera(GLFWwindow* window, glm::vec3 position, float verticalAngle, float horizontalAngle);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::mat4* getViewMatrixPtr();
    glm::mat4* getProjectionMatrixPtr();
    void setCameraMode(CameraMode mode);
    void moveCamera(glm::vec3 movement, float delta);
    void turnCamera(float horizontalAngle, float verticalAngle, float delta);
    void changeTranslationSpeed(float speed);
    const float & getTranslationSpeed() const;
    void changeRotationSpeed(float speed);
    const float & getRotationSpeed() const;
    void lookAt(const Object * target);
    const glm::vec3 & getDirection();

    void computeMatricesFromInputs();
    void setCameraLookingAt(Object * target);


    void update(double delta);//N'a pas besoin d'utiliser updatePhysic car la caméra n'a pas de physique, aussi mieux si liéer au fps
};


#endif //MOTEUR_DE_JEU_CAMERA_HPP
