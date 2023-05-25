#ifndef MOTEUR_DE_JEU_GAME_HPP
#define MOTEUR_DE_JEU_GAME_HPP
#include <map> // to make dictionaries for the scenes
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/Object/object.hpp"
#include "common/Scene/Scene.hpp"
#include "common/Material/material.hpp"
#include "common/Mesh/mesh.hpp"
#include "common/InputController.hpp"
class Game {
private:
    //use a map to store info to avoid multiple loading and easier access
    //map either with path or with name but unsafe
    std::map<std::string, Scene*> scenes;


    std::string currentSceneName = "";

    void FixedPhysicsUpdate();
    int createWindow();
    bool running = false;
    unsigned int SCR_WIDTH = 800;
    unsigned int SCR_HEIGHT = 600;

    double startTime = 0.0f;
    double lastTime = 0.0f;
    double deltaTime = 0.0f;

    GLFWwindow *window = nullptr;
    InputController *inputController = nullptr;
    ///@brief Override this function to add your own code to the game loop
    void mainLoop();
public:


    void addScene(std::string name, Scene *scene);
    void setScreenSize(unsigned int width, unsigned int height);

    Scene* findScene(std::string sceneName);
    Scene* getCurrentScene();
    unsigned int GetScreenWidth();
    unsigned int GetScreenHeight();
    GLFWwindow *GetWindow();
    double getDeltaTime();
    InputController *getInputController();

    Game();

    void start();
    void changeScene(std::string sceneName);

    bool isRunning();
};


#endif //MOTEUR_DE_JEU_GAME_HPP
