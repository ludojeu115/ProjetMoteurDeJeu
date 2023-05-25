#ifndef MOTEUR_DE_JEU_MYCHARACTERCONTROLLER_HPP
#define MOTEUR_DE_JEU_MYCHARACTERCONTROLLER_HPP

#include "common/Components/Character controller/characterController.hpp"
#include "common/InputController.hpp"

class myCharacterController : public CharacterController{
protected:
    InputController* iC = nullptr;
public:
    void onStep(double delta) override;
    void onLoad() override;

};


#endif //MOTEUR_DE_JEU_MYCHARACTERCONTROLLER_HPP
