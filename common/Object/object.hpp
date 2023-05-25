#ifndef OBJECT_H
#define OBJECT_H
#include "common/Components/component.hpp"
#include <vector>
#include <string>
#include <array>
#include <map>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Component;
class Game;
class Scene;
class Object
{
protected:
    std::string name = "";
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    Object *parent = nullptr;
    std::vector<Object*> children;
    std::map<std::string,Component*> components;
    glm::mat4 modelMatrix;
//    glm::mat4 viewMatrix, projectionMatrix;
    Game* game = nullptr;
    Scene* scene = nullptr;
    void setGame(Game* game);
    void setScene(Scene* scene);
public:
    Object();
    Object(const Object &other);
    ~Object();
    // Functions called by the game
    virtual void draw();
    virtual void update(double delta);
    virtual void physicUpdate(double delta);
    virtual void start();
    virtual void stop();

    // Functions that change the tree
    void setParent(Object *newParent);
    void removeParent();
    void addChild(Object *newChild);
    void removeChild(Object *child);
    bool hasParent();
    Object *changeName(std::string newName);
    void bind(Game* game, Scene* scene);
    void unbind();


    // Functions that change the components
    Object* addComponent(Component* component);
    void removeComponent(Component* component);

    // Functions that change the transform
    Object * setPosition(glm::vec3 newPosition);
    Object * setScale(glm::vec3 newScale);
    Object * setRotation(glm::vec3 newRotation);
    Object * setName(std::string newName);
/*    Object * setViewMatrix(const glm::mat4 &newViewMatrix);
    Object * setProjectionMatrix(const glm::mat4 &newProjectionMatrix);*/
    Object * translate(glm::vec3 vec3);
    Object * rotate(float yaw, float pitch, float roll);
    Object * resize(glm::vec3 vec3);
    void generateModelMatrix();

    //Getters
    glm::mat4 getModelMatrix();
    glm::vec3 getGlobalPosition();
    glm::vec3 getGlobalRotation() const;
    glm::vec3 getGlobalScale();
    glm::vec3 getLocalPosition();
    glm::vec3 getLocalRotation();
    glm::vec3 getLocalScale();
    std::string getName();
    std::array<glm::mat4*,3> getMVPMatrices();
    std::vector<Component*> getComponents();
    Component *getComponent(std::string name);
    std::vector<Object *> getChildren(bool recursive = false);
    Object * getObject(std::string name);
    std::vector<Object *> getObjects();
    Game* getGame();
    Scene* getScene();


};

#endif //OBJECT_H
