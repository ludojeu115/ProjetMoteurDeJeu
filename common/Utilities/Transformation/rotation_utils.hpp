#ifndef MOTEUR_DE_JEU_ROTATION_UTILS_HPP
#define MOTEUR_DE_JEU_ROTATION_UTILS_HPP

#include <glm/glm.hpp>

///brief convert a vector to longitude and latitude
///@param vector the direction vector
///@return a pair of floats, the first is the longitude, the second is the latitude
///Longitude in range -180 to 180, latitude in range -90 to 90 in radians
std::pair<float,float> cartesianToSpherical(glm::vec3 vector);

///brief convert longitude and latitude to a vector
///@param theta the longitude
///@param phi the latitude
///@return a vector (should be normalized)
std::vector<glm::vec3> sphericalToCartesian(float theta, float  phi);

std::pair<float,float> lookAt(const glm::vec3 & from, const glm::vec3 &target);

#endif //MOTEUR_DE_JEU_ROTATION_UTILS_HPP
