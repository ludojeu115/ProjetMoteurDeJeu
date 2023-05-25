#ifndef MOTEUR_DE_JEU_SCENE_HPP
#define MOTEUR_DE_JEU_SCENE_HPP
#include "common/Material/material.hpp"
#include "common/Mesh/mesh.hpp"
#include "common/Object/Camera/camera.hpp"
#include "common/Components/physicsComponent.hpp"
#include "common/Components/ColliderComponent/Collider.hpp"
#include <map>
class Game;
class Object;
class Scene {
private:
    Object * root = nullptr;
    bool loaded = false;
    Camera * currentCamera = nullptr;
    Game * game = nullptr;
    std::vector<PhysicsComponent*> physicsComponents;
    std::vector<Collider*> colliders;
    std::vector<Component*> sceneComponents;
    std::vector<Component*> componentsToRemove;
    void removeQueuedComponents();
public:
    void setRoot(Object * root);
    Object * getRoot();
    int load();
    int unload();

    void update(double delta); // Update every time we can, if fixed we have a max fps then wait until delta is minimum 1/fps
    void physicsUpdate(double delta);// Must be called at a fixed rate, ex : 20Hz
    void draw();

    void setCurrentCamera(Camera * camera);
    ///@brief Add an object to the root or as root if none is present
    ///@param object Object to add
    ///@return the object added
    Object* addObject(Object* object); //Add an object to the root
    void setGame(Game * game);
    void addComponentToScene(Component * component);
    void queueComponentToRemove(Component * component);

    Camera* getCurrentCamera();



    Scene();
    Scene(Object * root);


    void loadSceneFromJson(std::string sceneName);//TODO
    void saveSceneToJson(std::string sceneName);//TODO

    void processCollisions(float d);
};


#endif //MOTEUR_DE_JEU_SCENE_HPP
