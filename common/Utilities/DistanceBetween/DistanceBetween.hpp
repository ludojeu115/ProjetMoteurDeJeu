#ifndef MOTEUR_DE_JEU_DISTANCEBETWEEN_HPP
#define MOTEUR_DE_JEU_DISTANCEBETWEEN_HPP


#include "glm/vec3.hpp"

double distanceBetweenPointandLine(glm::vec3 point, glm::vec3 linePoint1, glm::vec3 linePoint2);
double distanceBetweenLines(glm::vec3 line1Point1, glm::vec3 line1Point2, glm::vec3 line2Point1, glm::vec3 line2Point2);



#endif //MOTEUR_DE_JEU_DISTANCEBETWEEN_HPP
