//
// Created by ludovic.lonlas@etu.umontpellier.fr on 20/04/23.
//

#include "stdUtilities.hpp"

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec) {
    os << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
