//
// Created by ludovic.lonlas@etu.umontpellier.fr on 18/04/23.
//
#include "common/Utilities/stdUtilities.hpp"
#include "camera.hpp"

glm::mat4 Camera::getViewMatrix() {
    return ViewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
    return ProjectionMatrix;
}

void Camera::computeAngle() {
    //TODO ajouter le roll de la camera


    float horizontalAngle = glm::radians(this->getGlobalRotation().y);
    float verticalAngle = glm::radians(this->getGlobalRotation().x);

    //direction
    direction = glm::vec3(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)

    );


    // Right vector
    right = glm::vec3(
            sin(horizontalAngle - glm::pi<float>() / 2.0f),
            0,
            cos(horizontalAngle - glm::pi<float>() / 2.0f)
    );
    // Up vector
    up = glm::cross(right, direction);
}

void Camera::lookAt(const Object * target) {
    glm::vec3 lookAtDir = glm::normalize(target->getGlobalRotation() - this->getGlobalPosition());
    std::pair<float, float> lookAt = cartesianToSpherical(lookAtDir);
    if (this->hasParent())
        this->setRotation(glm::vec3(lookAt.first, lookAt.second, 0) - this->parent->getGlobalRotation());
    else
        this->setRotation(glm::vec3(lookAt.first, lookAt.second, 0));
    //computeAngle();
}


void Camera::setCameraMode(CameraMode mode) {
    this->camMode = mode;
}

void Camera::update(double delta) {
    switch (this->camMode) {
        case CAMERA_MODE_FREE:
            if (constant_free_camera_movement != glm::vec3(0, 0, 0))
                moveCameraFree(0, 0, constant_free_camera_movement, (float) delta);
            break;
        case CAMERA_MODE_ORBIT:
            MoveCameraOrbit(constant_orbit_camera_movement.z, constant_orbit_camera_movement.y,
                            constant_orbit_camera_movement.x, delta);//0,constant_orbit_camera_movement,(float)delta);
            break;
        case CAMERA_45_DEGREE_ORBIT:
            position += right * ((float)delta * rotationSpeed);
            lookAt(camera_looking_at);
            computeAngle();
            break;


    }
    //std::cout << "Camera position : " << this->getGlobalPosition().x << " " << this->getGlobalPosition().y << " " << this->getGlobalPosition().z << std::endl;
}


void Camera::moveCameraFree(float verticalAngle, float horizontalAngle, glm::vec3 translate, float deltaTime) {
    float newVerticalAngle = 0;
    float newHorizontalAngle = 0;
    if (this->allowCameraMove) {
        newVerticalAngle = verticalAngle * this->rotationSpeed * deltaTime;
        newHorizontalAngle = horizontalAngle * this->rotationSpeed * deltaTime;
        //std::cout << "newVerticalAngle : " << newVerticalAngle << std::endl;
        //std::cout << "newHorizontalAngle : " << newHorizontalAngle << std::endl;
        this->translate(
                (this->direction * translate.z + this->up * translate.y + this->right * translate.x) * deltaTime *
                translationSpeed);

        this->rotate(newVerticalAngle, newHorizontalAngle, 0);
    }

    computeAngle();

}


void Camera::MoveCameraOrbit(float zoom, float up, float right, float deltaTime) {
    // Utilisé pour calculer la difference d'angles
    float diffLong = this->getGlobalRotation().y;
    float diffLat = this->getGlobalRotation().x;


    //on utilise lookAt pour déplacer la caméra pour orbiter autour de la position
    lookAt(camera_looking_at);
    diffLong = this->getGlobalRotation().y - diffLong;
    diffLat = this->getGlobalRotation().x - diffLat;

    if (this->allowCameraMove) {
        position += (right * this->right + up * this->up + zoom * this->direction) * deltaTime * translationSpeed;
    }


    //////////////////////////////////////////////////////////////
    //On ajoute la différence d'angles à la direction actuelle
    lookAt(camera_looking_at);
    this->rotate(diffLat, diffLong, 0);
/*    horizontalAngle += diffLong;
    verticalAngle += diffLat;*/

    //////////////////////////////////////////////////////////////
    //On recalcule la direction et le vecteur droit et le vecteur haut
    computeAngle();

}


void Camera::MoveCamera45Orbit(float zoom, float increaseSpeed, float deltaTime) {
// Look at simple
    lookAt(camera_looking_at);

    if (this->allowCameraMove) {
        this->rotationSpeed += 4 * deltaTime * increaseSpeed;
        position += (zoom * this->direction) * deltaTime * translationSpeed;

    }

}


Camera::Camera(GLFWwindow *window) {
    this->name = "Camera";
    this->window = window;
    this->ProjectionMatrix = glm::perspective(glm::radians(fieldOfView), 4.0f / 3.0f, 0.1f, 100.0f);
    this->computeAngle();
}
Camera::Camera(GLFWwindow *window, glm::vec3 position, float verticalAngle, float horizontalAngle) {
    this->name = "Camera";
    this->window = window;
    this->ProjectionMatrix = glm::perspective(glm::radians(fieldOfView), 4.0f / 3.0f, 0.1f, 100.0f);
    this->setPosition(position);
    this->setRotation(glm::vec3(verticalAngle, horizontalAngle, 0));
    this->computeAngle();
}




void Camera::moveCamera(glm::vec3 movement, float delta) {
    switch (this->camMode) {
        case CAMERA_MODE_FREE:
            this->moveCameraFree(0, 0, movement, delta);
            break;
        case CAMERA_MODE_ORBIT:
            MoveCameraOrbit(movement.z, movement.y, movement.x, delta);
            break;
        case CAMERA_45_DEGREE_ORBIT:

            break;
    }
}

void Camera::turnCamera(float horizontalAngle, float verticalAngle, float delta) {
    switch (this->camMode) {
        case CAMERA_MODE_FREE:
            moveCameraFree(verticalAngle, horizontalAngle, glm::vec3(0, 0, 0), delta);
            break;
        default:
            break;
    }

}

const glm::vec3 &Camera::getDirection() {
    return this->direction;
}


void Camera::changeTranslationSpeed(float speed) {
    this->translationSpeed = speed;
}

const float &Camera::getTranslationSpeed() const {
    return this->translationSpeed;
}

void Camera::changeRotationSpeed(float speed) {
    rotationSpeed = speed;
}

const float &Camera::getRotationSpeed() const {
    return rotationSpeed;
}

void Camera::setCameraLookingAt(Object *target) {
    this->camera_looking_at = target;
}

void Camera::computeMatricesFromInputs() {
    // Generate Projection Matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(glm::radians(fieldOfView), 4.0f / 3.0f, 0.1f, 100.0f);
    // Generate View Matrix
    ViewMatrix = glm::lookAt(
            this->getGlobalPosition(),           // Camera is here
            this->getGlobalPosition() + direction, // and looks here : at the same position, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 *Camera::getViewMatrixPtr() {
    return &ViewMatrix;
}

glm::mat4 *Camera::getProjectionMatrixPtr() {
    return &ProjectionMatrix;
}





