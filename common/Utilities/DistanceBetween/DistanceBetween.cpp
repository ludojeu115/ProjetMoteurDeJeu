//
// Created by ludojeu115 on 24/05/2023.
//

#include "DistanceBetween.hpp"
#include "glm/detail/func_geometric.hpp"

double distanceBetweenPointandLine(glm::vec3 point, glm::vec3 linePoint1, glm::vec3 linePoint2) {
    // C = point, A = linePoint1, B = linePoint2
    glm::vec3 AB = linePoint2 - linePoint1;
    glm::vec3 AC = point - linePoint1;
    glm::vec3 BC = point - linePoint2;


    if (glm::dot(AB, AC) < 0) { // if point is before linePoint1
        return glm::length(AC);
    } else if (glm::dot(AB, BC) > 0) { // if point is after linePoint2
        return glm::length(BC);
    } else {

        //create C2 the projection of C on AB
        glm::vec3 C2 = linePoint1 + glm::dot(AC, AB) / glm::dot(AB, AB) * AB;

        return glm::length(point - C2);
    }
}

double distanceBetweenLines(glm::vec3 line1Point1, glm::vec3 line1Point2, glm::vec3 line2Point1, glm::vec3 line2Point2) {

    return std::min(distanceBetweenPointandLine(line1Point1, line2Point1, line2Point2),
                    std::min(distanceBetweenPointandLine(line1Point2, line2Point1, line2Point2),
                             std::min(distanceBetweenPointandLine(line2Point1, line1Point1, line1Point2),
                                      distanceBetweenPointandLine(line2Point2, line1Point1, line1Point2))));
}

