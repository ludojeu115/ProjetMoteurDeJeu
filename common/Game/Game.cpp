//
// Created by ludojeu115 on 4/13/23.
//

#include "Game.hpp"
#include "thread"

#define FIXEDPHYSICSTIMEMS 16

void Game::changeScene(std::string sceneName) {
    //We allow reloading scene for now
    //if (sceneName == this->currentSceneName) return; // Prevents from reloading the same scene

    // Only allow changing to a scene that exists
    if (sceneName == "" || this->findScene(sceneName) == nullptr) {
        throw std::invalid_argument("Scene not found or wrong argument");
    }

    Scene* currentScene = this->findScene(this->currentSceneName);
    int returnCode = 0;

    if (currentScene != nullptr) {// unload current scene
        returnCode = currentScene->unload();
    }
    if (returnCode != 0) throw std::runtime_error("Error while unloading scene");

    if (this->isRunning())
        returnCode = this->findScene(sceneName)->load();// load new scene
    if (returnCode != 0) throw std::runtime_error("Error while loading scene");

    this->currentSceneName = sceneName;

}

void Game::addScene(std::string name, Scene* scene) {
    if (scenes.find(name) == scenes.end()) {
        scenes.insert(std::pair<std::string, Scene*>(name, scene));
        if(scenes.size() == 1) this->changeScene(name); // if it's the first scene, we load it
        scene->setGame(this);

    } else {
        throw std::invalid_argument("Scene already present");
    }
}


Scene* Game::findScene(std::string sceneName) {
    return scenes.find(sceneName) != scenes.end() ? scenes[sceneName] : nullptr;
}


Scene* Game::getCurrentScene() {
    return findScene(currentSceneName);
}



void Game::FixedPhysicsUpdate(){
    while(this->running){

        //std::cout << "Physics update" << std::endl;
        getCurrentScene()->physicsUpdate(FIXEDPHYSICSTIMEMS/1000.0f);
        //wait 1/20th of a second
        std::this_thread::sleep_for(std::chrono::milliseconds(FIXEDPHYSICSTIMEMS));

        //process collisions
        this->getCurrentScene()->processCollisions(FIXEDPHYSICSTIMEMS/1000.0f);
    }

}

void Game::setScreenSize(unsigned int width, unsigned int height) {
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    //TODO resize content
}

unsigned int Game::GetScreenWidth() {
    return SCR_WIDTH;
}

unsigned int Game::GetScreenHeight() {
    return SCR_HEIGHT;
}

GLFWwindow *Game::GetWindow() {
    return window;
}

int Game::createWindow() { // une partie est copié du squelette de base
    GLenum error = glGetError();
    // Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow((int)SCR_WIDTH, (int)SCR_HEIGHT, "TP1 - GLFW", nullptr, nullptr);
    if (window == nullptr) {
        fprintf(stderr,
                "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::string errorString = reinterpret_cast<const char *>(glewGetErrorString(error));
        throw std::runtime_error("Error generating OpenGL: " + errorString);
    }
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    error = glGetError();
    if (error != GL_NO_ERROR && error != 1280) {
        std::string errorString = reinterpret_cast<const char *>(glewGetErrorString(error));
        throw std::runtime_error("Error generating OpenGL: " + errorString);
    }
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, this->SCR_WIDTH / 2, this->SCR_HEIGHT / 2);

    // Dark blue background
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    return 0;
}

void Game::start() {
    int errorCode = 0;
    if(!window)errorCode = this->createWindow();
    if (errorCode != 0) throw std::runtime_error("Error while creating window");



    this->inputController = new InputController(this->window);


    if (this->currentSceneName == "") throw std::runtime_error("No scene");
    if (this->running) throw std::runtime_error("Game already running");
    this->running = true;



    Scene * currentScene = this->getCurrentScene();
    currentScene->load();

    this->lastTime = glfwGetTime();
    std::thread physicsThread(&Game::FixedPhysicsUpdate, this);

    while(glfwWindowShouldClose(window) == 0){//belle boucle

        //Calcul le delta time
        this->deltaTime = glfwGetTime() - this->lastTime;
        this->lastTime = glfwGetTime();

        //Obtiens les derniers inputs dans l'ordre, TODO separer les inputs des updates pour de meilleurs performances
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {// Failsafe TODO remove
            glfwSetWindowShouldClose(window, true);
        }

        if(this->inputController) this->inputController->update(this->deltaTime);//Update input controller, mainly for sroll smoothing

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Update Scene
        if((currentScene = getCurrentScene()) != nullptr) {
            if(currentScene->getCurrentCamera() != nullptr) {
                //Update camera
                currentScene->getCurrentCamera()->computeMatricesFromInputs();
            }
            this->mainLoop();
            //Update objects
            getCurrentScene()->update(this->deltaTime);
            //Update scenes
            getCurrentScene()->draw();
        }
        //send the image to the screen
        glfwSwapBuffers(window);

    }
    this->running = false;
    glfwTerminate();
}

double Game::getDeltaTime() {
    return this->deltaTime;
}

///@brief Sert principalement à créer le context OpenGL et GlfwWindow
Game::Game() {
    this->createWindow();
    this->startTime = glfwGetTime();

}

InputController *Game::getInputController() {
    return this->inputController;
}

void Game::mainLoop() {

}

bool Game::isRunning() {
    return this->running;
}
