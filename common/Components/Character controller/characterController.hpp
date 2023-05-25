#ifndef MOTEUR_DE_JEU_CHARACTERCONTROLLER_HPP
#define MOTEUR_DE_JEU_CHARACTERCONTROLLER_HPP
#include "common/Components/Gravity/Gravity.hpp"
#include <glm/glm.hpp>
class CharacterController : public virtual Gravity{
private:
    glm::vec3 up = glm::vec3(0,1,0);
    double maxSpeed = 0.8;
    double speed = 5;
    double airSpeed = 0.1;
    double jumpForce = 40;
    glm::vec3 movingTo = glm::vec3(0,0,0);
    bool moving = false;


public:
    void move(glm::vec2 direction);
    void jump();


    virtual void onPhysicStep(double physic_delta);
    Component *clone() override;
    CharacterController();


};


#endif //MOTEUR_DE_JEU_CHARACTERCONTROLLER_HPP
