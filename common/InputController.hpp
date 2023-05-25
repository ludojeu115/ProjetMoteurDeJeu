#ifndef MOTEUR_DE_JEU_INPUTCONTROLLER_HPP
#define MOTEUR_DE_JEU_INPUTCONTROLLER_HPP

#include <map>
#include <functional>
#include "GLFW/glfw3.h"


class InputController {
protected:
    std::map<unsigned int, std::function<void(GLFWwindow*)>> callbacksOnPressed;
    std::map<unsigned int, std::function<void(GLFWwindow*)>> callbacksOnRelease;
    std::map<unsigned int, bool> isPressed;
    float scrollYAxis = 0;
    float scrollXAxis = 0;
    float scroll_deceleration = 2.0f; // must be above 0
    GLFWwindow *window;
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
public:

    void setCallbackKEYOnPressed(unsigned int KEY  ,std::function<void(GLFWwindow*)> callback);
    void setCallbackKEYOnRelease(unsigned int KEY  ,std::function<void(GLFWwindow*)> callback);
    bool isKEYPressed(unsigned int KEY);
    float getScrollXAxis();
    float getScrollYAxis();
    void update(float delta);
    bool isScrolling();
    explicit InputController(GLFWwindow *window);

/*    void setGame(Game *game);
    Game* getGame();*/


};



#endif //MOTEUR_DE_JEU_INPUTCONTROLLER_HPP
