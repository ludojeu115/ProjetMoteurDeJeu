#ifndef COMPONENT_H
#define COMPONENT_H
#include "common/Object/object.hpp"
#include <string>
class Object;
class Component
{
protected:
    Object* owner{};
    std::string name = "";
    bool loaded = false;
public:
    Component()= default;
    virtual ~Component() = default;
    virtual Component* clone();

    void setOwner(Object* newOwner);
    Object* getOwner() const;

    virtual void onInit();
    virtual void onLoad();
    virtual void onUnload();
    virtual void onStep(double delta);

    [[nodiscard]] std::string getName() const;


};

#endif //COMPONENT_H
