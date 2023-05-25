//
// Created by ludojeu115 on 4/13/23.
//

#include "Scene.hpp"
#include <algorithm>
#include <execution>

void Scene::setRoot(Object *root) {
    if (this->root != nullptr && this->root != root) {
        this->root->unbind();
        this->root->stop();
    }

    this->root = root;
    root->bind(this->game, this);
}

Object *Scene::getRoot() {
    return this->root;
}

int Scene::load() {
    this->loaded = true;
    this->root->start();
    return 0;
}

int Scene::unload() {
    this->loaded = false;
    this->root->stop();
    return 0;
}

void Scene::update(double delta) {
    if (this->loaded) this->root->update(delta);
    for (auto &i: this->sceneComponents) {
        i->onStep(delta);
    }
    this->removeQueuedComponents();
}

void Scene::physicsUpdate(double delta) {
    if (this->loaded) this->root->physicUpdate(delta);

    for (auto &i: this->physicsComponents) {
        i->onPhysicStep(delta);
    }
}

void Scene::draw() {
    if (this->loaded) this->root->draw();

}

Scene::Scene() {//create empty object as source if none is provided
    this->root = (new Object())->changeName("root");
    root->bind(nullptr, this);

    root->start();
}

Scene::Scene(Object *root) {
    this->root = root;
    root->bind(this->game, this);
    root->start();
}

Object* Scene::addObject(Object *object) {
    if (object == nullptr) {
        throw std::invalid_argument("Object is null");
    }
    //if first camera set it as current camera
    if (this->currentCamera == nullptr && dynamic_cast<Camera *>(object) != nullptr) {
        this->currentCamera = dynamic_cast<Camera *>(object);
    }

    if (this->root == nullptr)
        this->root = object;
    else
        this->root->addChild(object);
    object->bind(this->game, this);
    object->start();
    return object;
}

void Scene::setCurrentCamera(Camera *camera) {
    if (camera == nullptr) {
        throw std::invalid_argument("Camera is null");
    }
    if (camera == this->currentCamera) {
        std::cout << "Camera already set as current camera" << std::endl;
        return;
    }
    this->currentCamera = camera;

}

void Scene::setGame(Game *game) {
    this->game = game;
    this->root->bind(game, nullptr);

}

Camera *Scene::getCurrentCamera() {
    return this->currentCamera;
}


void Scene::queueComponentToRemove(Component *component) {
    if (std::find(this->componentsToRemove.begin(), this->componentsToRemove.end(), component) !=
        this->componentsToRemove.end()) {
        std::cout << "Component already set to be deleted" << std::endl;
        return;
    }
    this->componentsToRemove.push_back(component);
}

void Scene::addComponentToScene(Component *component) {

    //add Component for physic update
    if (dynamic_cast<PhysicsComponent *>(component) != nullptr) {
        if (std::find(this->physicsComponents.begin(), this->physicsComponents.end(), component) !=
            this->physicsComponents.end()) {
            //std::cout << "PhysicsComponent already in the list" << std::endl;
            return;
        }
        this->physicsComponents.push_back(dynamic_cast<PhysicsComponent *>(component));
    }
    if(component->getName() == "Collider"){
        if (std::find(this->colliders.begin(), this->colliders.end(), component) !=
            this->colliders.end()) {
            //std::cout << "PhysicsComponent already in the list" << std::endl;
            return;
        }
        this->colliders.push_back(dynamic_cast<Collider *>(component));
    }








    //add Component for regular update
    if (std::find(this->sceneComponents.begin(), this->sceneComponents.end(), component) !=
        this->sceneComponents.end()) {
        //std::cout << "Component already in the list" << std::endl;
        return;
    }
    this->sceneComponents.push_back(component);
}

void Scene::removeQueuedComponents() {

    for (auto &i: this->componentsToRemove) {
        if (dynamic_cast<PhysicsComponent *>(i) != nullptr) {
            this->physicsComponents.erase(
                    std::remove(this->physicsComponents.begin(), this->physicsComponents.end(), i),
                    this->physicsComponents.end());
        }
        if(i->getName() == "Collider")
            this->colliders.erase(
                    std::remove(this->colliders.begin(), this->colliders.end(), i),
                    this->colliders.end());
        this->sceneComponents.erase(
                std::remove(this->sceneComponents.begin(), this->sceneComponents.end(), i),
                this->sceneComponents.end());
        i->onUnload();

    }


}

void Scene::processCollisions(float d) {
    //First find all object that can collide
    Collider* collider1;
    Collider* collider2;
    for (int i = 0; i < this->colliders.size(); i++)
        for (int j = i + 1; j < this->colliders.size(); j++) {
            collider1 = this->colliders[i];
            collider2 = this->colliders[j];
            if (collider1->isConstraint() && collider2->isConstraint())continue;
            //firstly find if collision is possible
            //TODO
            //secondly find if collision is happening
            collisionInfo info = collider1->testCollision(collider2);
            if(!info.isColliding) continue;

            if(collider1->isTrigger() ){
                collider1->onTrigger(collider2);
                if(collider2->isTrigger()){
                    collider2->onTrigger(collider1);
                    continue;
                }
            }
            if(collider2->isTrigger()){
                collider2->onTrigger(collider1);
                continue;
            }

            //std::cout << "Collision between " << collider1->getName() << " and " << collider2->getName() << std::endl;
            //TODO used last collider position to avoid behind pushed on the wrong side
            //thirdly move object to fix collision with normal and velocity

            if(collider1->isConstraint() || collider1->getOwner()->getComponent("PhysicsComponent") == nullptr)//don't move random object if they don't have a physics component
                collider2->getOwner()->translate(info.collisionNormal * info.penetration);
            else {
                if (collider2->isConstraint() || collider2->getOwner()->getComponent("PhysicsComponent") == nullptr)
                    collider1->getOwner()->translate(-info.collisionNormal * info.penetration);
                else // cas de deux objets non physique non contraint
                {
                    collider1->getOwner()->translate(-info.collisionNormal * info.penetration / 2.0f);
                    collider2->getOwner()->translate(info.collisionNormal * info.penetration / 2.0f);
                }
            }


            PhysicsComponent* physicsComponent1 = dynamic_cast<PhysicsComponent*>(collider1->getOwner()->getComponent("PhysicsComponent"));
            PhysicsComponent* physicsComponent2 = dynamic_cast<PhysicsComponent*>(collider2->getOwner()->getComponent("PhysicsComponent"));

            if(physicsComponent1 == nullptr && physicsComponent2 == nullptr) continue;
            if(physicsComponent1 == nullptr) {
                glm::vec3 applyForce =
                        glm::dot(-1.0f*physicsComponent2->getVelocity(), info.collisionNormal) * info.collisionNormal;
                physicsComponent2->addForce(-1.0f*applyForce * physicsComponent2->getMass() * -1.0f* (1+physicsComponent2->getBouncyness()));
                continue;
            }
            else if(physicsComponent2 == nullptr){
                glm::vec3 applyForce =
                        glm::dot(physicsComponent1->getVelocity(), info.collisionNormal) * info.collisionNormal;
                physicsComponent1->addForce(applyForce * physicsComponent1->getMass() * -1.0f * (1+physicsComponent1->getBouncyness()));
                continue;
            }
            // cas de deux objets non physique non contraint
            glm::vec3 vDef = physicsComponent1->getVelocity()-physicsComponent2->getVelocity() ;
            float dot = glm::dot(vDef,info.collisionNormal);
            float diviseur = 1.0f/physicsComponent1->getMass() + 1.0f/physicsComponent2->getMass();

            float jA = (-1*(1+physicsComponent1->getBouncyness())*dot)/diviseur;
            float jB = (-1*(1+physicsComponent2->getBouncyness())*dot)/diviseur;
            physicsComponent1->addForce(info.collisionNormal*jA);
            physicsComponent2->addForce(-1.0f*info.collisionNormal*jB);





    }


}
