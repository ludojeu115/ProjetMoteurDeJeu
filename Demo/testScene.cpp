#include "common/Shaders/shader.hpp"
#include "common/Game/Game.hpp"
#include "common/Material/Custom/custom.hpp"
#include "common/Object/MeshObject/meshObject.hpp"
#include "common/Material/User_Materials/HeightMap/heightmap.hpp"
#include "common/Components/Character controller/characterController.hpp"
#include "common/Components/ColliderComponent/SphereCollider/SphereCollider.hpp"


#include "ControllableCamera.hpp"
#include "myCharacterController.hpp"

int main(){
    Game game;

    game.addScene("testScene",new Scene());

    GLuint Unlit_Shader = LoadShaders("vertex_shader.glsl", "Unlit/fragment_shader.glsl");
    GLuint Debug_UV_Shader = LoadShaders("vertex_shader.glsl", "Debug/UV/fragment_shader.glsl");
    GLuint Debug_Normal_Shader = LoadShaders("vertex_shader.glsl", "Debug/Normal/fragment_shader.glsl");

    Scene* testScene = game.findScene("testScene");
    testScene->addObject(new ControllableCamera(game.GetWindow(), glm::vec3(0, 5, -10),-10,0));
    testScene->setCurrentCamera( dynamic_cast<Camera*>(testScene->getRoot()->getObjects()[0]));

    //Ajout de matériaux basique à la scene
    Custom_Material *unlitShader = new Custom_Material(),
    *debugUVShader = new Custom_Material(),
    *debugNormalShader = new Custom_Material();
    unlitShader->setShader(Unlit_Shader);
    debugUVShader->setShader(Debug_UV_Shader);
    debugNormalShader->setShader(Debug_Normal_Shader);

    //Ajout d'un material heightmap avec textures à la scene
    Texture grassTexture("TP/grass.png");
    Texture rockTexture("TP/rock.png");
    Texture snowTexture("TP/snowrocks.png");
    Texture heightMap("TP/heightmap-1024x1024.png");

    testScene->addObject(new MeshObject(createPlane(256, 10.0f),
                                        new Heightmap_Material(&heightMap, &grassTexture, &rockTexture, &snowTexture)))
        ->setName("plane with heightmap");



    testScene->addObject(new MeshObject(createSphere(16, 1.0f), debugNormalShader))
        ->setName("Player")
        ->translate({0, 1, 0})
        ->addComponent(new myCharacterController())
        ->addComponent(new SphereCollider(glm::vec3(), 1.0f));

    testScene->addObject(new MeshObject(createSphere(16,1.0f), unlitShader))
            ->setName("sphere2")
            ->translate({0, 1, 3})
                    //->addComponent(new Gravity())
            ->addComponent(new SphereCollider(glm::vec3(), 1.0f));

    //spawn 3 balls with physics on top of each other
    for (int i = 0; i < 3; ++i) {
        testScene->addObject(new MeshObject(createSphere(16, 1.0f), unlitShader))
                ->setName("sphere" + std::to_string(i))
                ->translate({-1, 1 + i * 2, 1})
                ->addComponent(new Gravity())
                ->addComponent(new SphereCollider(glm::vec3(), 1.0f));
    }


    game.start();
    return 0;

}