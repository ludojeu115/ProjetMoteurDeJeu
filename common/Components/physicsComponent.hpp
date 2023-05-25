#ifndef MOTEUR_DE_JEU_PHYSICSCOMPONENT_HPP
#define MOTEUR_DE_JEU_PHYSICSCOMPONENT_HPP
#include "common/Components/component.hpp"
class PhysicsComponent : public virtual Component {
protected :


    float mass = 10.0f;

    float bouncyness = 0.5f;
public:
    float getBouncyness() const;

protected:
    float friction = 2.4f;


    glm::vec3 force_to_apply = glm::vec3(0.0f);
    glm::vec3 velocity = glm::vec3(0.0f);
public:
    const glm::vec3 &getVelocity() const;

protected:
    glm::vec3 acceleration = glm::vec3(0.0f);
    void computeAcceleration();
    void computeVelocity();
    void computePosition(double physic_delta);


public:
    void setMass(float newMass);
    float getMass() const;

    virtual void onPhysicStep(double physic_delta);
    void addForce(glm::vec3 force);
    PhysicsComponent();

};
#endif //MOTEUR_DE_JEU_PHYSICSCOMPONENT_HPP
