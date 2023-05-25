#include "common/Components/ColliderComponent/Collider.hpp"
#ifndef MOTEUR_DE_JEU_PLANECOLLIDER_H
#define MOTEUR_DE_JEU_PLANECOLLIDER_H


class PlaneCollider : public Collider{

public:
    PlaneCollider();
    PlaneCollider(const PlaneCollider& other);

};


#endif //MOTEUR_DE_JEU_PLANECOLLIDER_H
