

#ifndef MOTEUR_DE_JEU_GRAVITY_HPP
#define MOTEUR_DE_JEU_GRAVITY_HPP


#include "common/Components/physicsComponent.hpp"

class Gravity : public virtual PhysicsComponent {
protected:
    bool onGround = true;
    float gravity = 9.81f;
    void computeGrounded();
    void bounce(glm::vec3 normal);
public:
    virtual void onGrounded();
    bool isGrounded();
    virtual void onPhysicStep(double physic_delta);
    void onLoad() override;
    void setGravity(float newGravity);
    float getGravity() const;

};


#endif //MOTEUR_DE_JEU_GRAVITY_HPP
