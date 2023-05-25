#include "component.hpp"

void Component::setOwner(Object *newOwner) {
    owner = newOwner;
}


void Component::onLoad() {
    loaded = true;
}
void Component::onUnload() {
    loaded = false;
}

void Component::onInit() {

}

void Component::onStep(double delta) {

}

std::string Component::getName() const {
    return name;
}

Object *Component::getOwner() const {
    return owner;
}

Component *Component::clone() {
    Component *newComponent = new Component();
    newComponent->name = this->name;
    newComponent->loaded = this->loaded;
    newComponent->owner = this->owner;
    return newComponent;
}
