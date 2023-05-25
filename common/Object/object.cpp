
#include "object.hpp"
#include "common/Game/Game.hpp"
#include "common/Components/drawableComponent.hpp"
#include "common/Components/Character controller/characterController.hpp"
#include "common/Utilities/stdUtilities.hpp"
#include "common/Scene/scene.hpp"

///@brief Ajoute un composant à l'objet
///@param component Composant à ajouter
Object* Object::addComponent(Component* component) {
    component->setOwner(this);
    //if key not already in map add component
    if (this->components.find(component->getName()) == this->components.end())
        this->components[component->getName()] = component;
    else{
        std::cout << "Component " << component->getName() << " already exists in object " << this->getName() << std::endl;
        return this;
    }

    if (scene != nullptr)
        scene->addComponentToScene(component);
    component->onInit();
    if (this->game != nullptr && this->game->isRunning())
        component->onLoad();
    return this;
}

///@brief Met à jour l'objet et ses composants (appelé par le moteur)
void Object::update(double delta) {

/*    for (int i = 0; i < this->components.size(); i++) {
        this->components[i]->onStep(delta);
    }*/
//a bit useless now
    for ( Object * child : this->children) {
        child->update(delta);
    }
}

///@brief Appelé quand l'objet est ajouté à une scène chargée ou quand la scène est chargée
void Object::start() {
    for (auto & component : this->components) {
        component.second->onLoad();
    }
    for ( Object * child : this->children) {
        child->start();
    }
}
///@brief Appelé quand l'objet est retiré d'une scène chargée ou quand la scène est déchargée
void Object::stop(){
    for (auto & component : this->components) {
        component.second->onUnload();
    }
    for ( Object * child : this->children) {
        child->stop();
    }

}



///@brief Affiche l'objet
void Object::draw() {
    for(auto & component : this->components){
        if( dynamic_cast<DrawableComponent*>(component.second) != nullptr  ) {
            dynamic_cast<DrawableComponent*>(component.second)->onDraw();
        }
    }


    for ( Object * child : this->children) {
        child->draw();
    }
}
///@brief Constructeur par défaut
Object::Object() {

}

///@brief destructeur par défaut
Object::~Object() {

}
///@brief Applique une position à l'objet
///@param newPosition Nouvelle position
///@return the object itself for chaining
Object* Object::setPosition(glm::vec3 newPosition) {
    if (this->position != newPosition) {
        this->position = newPosition;
        generateModelMatrix();
    }
    return this;
}
///@brief Applique une taille à l'objet
///@param newScale Nouvelle taille
Object* Object::setScale(glm::vec3 newScale) {
    if (this->scale != newScale) {
        this->scale = newScale;
        generateModelMatrix();
    }
    return this;
}
///@brief Applique une rotation à l'objet
///@param newRotation Nouvelle rotation
Object* Object::setRotation(glm::vec3 newRotation) {
    if (this->rotation != newRotation) {
        this->rotation = newRotation;
        generateModelMatrix();
    }
    return this;
}
///@brief Renvoie la position globale de l'objet
///@return position globale de l'objet
glm::vec3 Object::getGlobalPosition() {
    //Si pas d'owner, on le considère comme root
    return (this->parent != nullptr) ? glm::vec3(this->parent->getModelMatrix() * glm::vec4(this->position,1)) : this->position;
}
///@brief Renvoie la rotation globale de l'objet
///@return rotation globale de l'objet
glm::vec3 Object::getGlobalRotation() const {
    return (this->parent != nullptr) ? this->parent->getGlobalRotation() + this->rotation : this->rotation;
}
///@brief Renvoie la taille globale de l'objet
///@return taille globale de l'objet
glm::vec3 Object::getGlobalScale() {
    return (this->parent != nullptr) ? this->parent->getGlobalScale() * this->scale : this->scale;
}
///@brief Renvoie la position locale de l'objet
///@return position locale de l'objet
glm::vec3 Object::getLocalPosition() {
    return this->position;
}
///@brief Renvoie la rotation locale de l'objet
///@return rotation locale de l'objet
glm::vec3 Object::getLocalRotation() {
    return this->rotation;
}
///@brief Renvoie la rotation locale de l'objet
///@return rotation locale de l'objet
glm::vec3 Object::getLocalScale() {
    return this->scale;
}
///@brief Renvoie la matrice de transformation de l'objet.
///Elle doit être recalculée à chaque fois que l'objet ou la caméra sont modifié
///@return matrice de transformation de l'objet
std::array<glm::mat4*,3> Object::getMVPMatrices() {
    if (this->scene && this->scene->getCurrentCamera() != nullptr)
    return { &modelMatrix,
             this->scene->getCurrentCamera()->getViewMatrixPtr(),
             this->scene->getCurrentCamera()->getProjectionMatrixPtr()
            };
    else
        return { &modelMatrix, new glm::mat4(), new glm::mat4()};
}
///@brief Donne un nom à l'objet
///@param newName Nouveau nom
///@return the object itself for chaining
Object* Object::setName(std::string newName) {
    name = newName;
    return this;
}
///@brief Renvoie le nom de l'objet
std::string Object::getName() {
    return name;
}
///@brief Renvoie le premier composant de nom donné
///@param name Nom du composant à chercher
///@return Le composant trouvé, nullptr sinon
/// LA fonction fue créer avant que j'utilise map
Component *Object::getComponent(std::string name) {
    if (this->components.find(name) != this->components.end())
        return this->components[name];

    return nullptr;
}
///@brief Met à jour this->modelMatrix et les modelMatrix des enfants
void Object::generateModelMatrix() {
    glm::vec3 globalRotation = this->getGlobalRotation();
    //vraiment pas opti, il serait préférable de créer la matrice en une itération
    glm::mat4 newModelMatrix = glm::translate(glm::mat4(1.0f), this->getGlobalPosition());
    newModelMatrix = glm::rotate(newModelMatrix, glm::radians(globalRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    newModelMatrix = glm::rotate(newModelMatrix, glm::radians(globalRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    newModelMatrix = glm::rotate(newModelMatrix, glm::radians(globalRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    newModelMatrix = glm::scale(newModelMatrix, this->getGlobalScale());
    this->modelMatrix = newModelMatrix;
    for (Object * child : this->children) {
        child->generateModelMatrix();
    }
}


glm::mat4 Object::getModelMatrix() {
    return this->modelMatrix;
}

///@brief change le parent de l'objet
///@param newParent le nouveau parent de l'objet
void Object::setParent(Object *newParent) {
    if( this->parent != nullptr )// s'enlever de l'ancien parent
        this->parent->removeChild(this);
    if (newParent != this) // TODO Vérifier qu'il n'y a pas de boucle
    { // s'ajouter au nouveau parent et le met en parent
        this->parent = newParent;
        this->parent->children.push_back(this);
        this->bind(this->parent->getGame(), this->parent->getScene());

        //this->parent->addChild(this); //Risque de boucle infinie
    }


}

void Object::addChild(Object *newChild) {
    children.push_back(newChild);
    newChild->parent = this;
    newChild->bind(this->getGame(), this->getScene());
    //newChild->setParent(this); //Risque de boucle infinie
}

void Object::removeParent() {
    if(this->parent != nullptr) {
        Object *oldParent = this->parent;
        this->parent = nullptr;
        oldParent->removeChild(this);
        this->unbind();
        this->stop();
    }
}

void Object::removeChild(Object *child) {
    unsigned int i = 0;
    for( Object* iterChild : this->children ) {
        if( iterChild == child ) {
            this->children.erase(this->children.begin()+i);
            iterChild->parent = nullptr;
            iterChild->unbind();
            iterChild->stop();
            return;
        }
        i++;
    }
}


Object::Object(const Object &other) {
    this->name = other.name;
    this->position = other.position;
    this->rotation = other.rotation;
    this->scale = other.scale;
    //do not copy parent and children
    this->parent = nullptr;
    this->children.clear();
    //copy all components
    this->components.clear();
    Component* comp;
    this->game = other.game;
    this->scene = other.scene;
    for( auto component : other.components ) {
        comp = component.second->clone();
        comp->setOwner(this); //prend le contrôle des composants

        this->addComponent(comp);
    }
}

Object* Object::translate(glm::vec3 translation) {
    this->setPosition(this->position+translation);
    return this;
}

void Object::physicUpdate(double delta) {
        for ( Object * child : this->children) {
            child->physicUpdate(delta);
        }
}

bool Object::hasParent() {
    return this->parent != nullptr;
}

Object* Object::rotate(float yaw, float pitch, float roll) {
/*    this->rotation.x += yaw;
    this->rotation.y += pitch;
    this->rotation.z += roll;*/
    this->setRotation(this->rotation+glm::vec3(yaw,pitch,roll));
    return this;
}

Object *Object::changeName(std::string newName) {
    this->name = newName;
    return this;
}

Object *Object::getObject(std::string name) {
    for (Object * child : this->children) {
        if (child->getName() == name) {
            return child;
        }
    }
    return nullptr;
}

std::vector<Object *> Object::getObjects() {
    return this->children;
}

Game *Object::getGame() {
    return game;
}

void Object::setGame(Game *game) {
    if (game == nullptr) return;

    this->game = game;
    for (Object * child : this->children) {
        child->setGame(game);
    }
}

void Object::setScene(Scene *scene) {
    if (scene == nullptr) return;

    this->scene = scene;
    for (Object * child : this->children) {
        child->setScene(scene);
    }
}

Scene *Object::getScene() {
    return this->scene;
}

std::vector<Object *> Object::getChildren(bool recursive) {
    if (recursive) {
        std::vector<Object *> children_to_return = this->children;
        for (Object * child : this->children) {
            std::vector<Object *> children = child->getChildren(true);
            children_to_return.insert(this->children.end(), children.begin(), children.end());
        }
    }
    return this->children;
}

std::vector<Component *> Object::getComponents() {
    std::vector<Component *> componentsList;
    for (const auto& component : this->components) { // c'est bête qu'il n'y ait pas de méthode pour récupérer les valeurs d'un unordered_map
        componentsList.push_back(component.second);
    }
return componentsList;
}

void Object::bind(Game *game = nullptr, Scene *scene = nullptr) {

    if (game!= nullptr)this->setGame(game);
    if (scene != nullptr) {
        this->setScene(scene);

        for (Component *component: this->getComponents()) {
            scene->addComponentToScene(component);
        }
    }

    for (Object * child : this->children) {
        child->bind(game, scene);
    }
}

void Object::unbind() {
    this->setGame(nullptr);
    if (this->scene != nullptr)
        for (Component *component: this->getComponents()) {
            this->scene->queueComponentToRemove(component);
        }
    this->setScene(nullptr);

    for (Object * child : this->children) {
        child->unbind();
    }
}

void Object::removeComponent(Component *component) {

    //remove component from scene but does not delete it
    if (this->scene != nullptr)
        this->scene->queueComponentToRemove(component);
    //remove pointer from components vector

}

Object *Object::resize(glm::vec3 scale) {
    this->setScale(this->scale+scale);
    return this;
}



