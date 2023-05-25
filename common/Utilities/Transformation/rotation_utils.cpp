#include <vector>
#include "rotation_utils.hpp"
#include <glm/gtc/matrix_transform.hpp>

std::pair<float, float> cartesianToSpherical(glm::vec3 vector) {//take a vec3 as input and return, long and lat
    auto theta = (float)atan2(vector.x, vector.z);
    auto phi = (float)atan2(vector.y, sqrt(vector.x * vector.x + vector.z * vector.z)); // this give a value between -pi/2 and pi/2

    return {theta, phi};
}

std::vector<glm::vec3> sphericalToCartesian(float theta, float  phi) {
    // Direction : Spherical coordinates to Cartesian coordinates conversion
    auto direction = glm::vec3(
            std::cos(phi) * std::sin(theta),
            std::sin(phi),
            std::cos(phi) * std::cos(theta)

    );
    // Right vector
    auto right = glm::vec3(
            std::sin(theta - glm::pi<float>() / 2.0f),
            0,
            std::cos(theta - glm::pi<float>() / 2.0f)
    );
    // Up vector
    auto up = glm::cross( right, direction );
    return {direction, right, up};
}

std::pair<float, float> lookAt(const glm::vec3 &from, const glm::vec3 &target) {
    glm::vec3 lookAtDir = glm::normalize(target - from);
    return cartesianToSpherical(lookAtDir);
}
