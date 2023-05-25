#include <iostream>
#include <glm/glm.hpp>

#ifndef MOTEUR_DE_JEU_STDUTILITIES_HPP
#define MOTEUR_DE_JEU_STDUTILITIES_HPP
//('ostream' (aka 'basic_ostream<char>') and 'const glm::vec3' (aka 'const tvec3<float, highp>'))

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec);

#endif //MOTEUR_DE_JEU_STDUTILITIES_HPP
