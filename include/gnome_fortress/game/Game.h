#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <time.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <irrKlang.h>
using namespace irrklang;

#include "gnome_fortress/game/AcornMeter.h"
#include "gnome_fortress/game/Acorns.h"
#include "gnome_fortress/game/Enemies.h"
#include "gnome_fortress/game/MushroomGun.h"
#include "gnome_fortress/game/PeanutGun.h"
#include "gnome_fortress/game/PineconeGun.h"
#include "gnome_fortress/game/Player.h"
#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/RocketStream.h"
#include "gnome_fortress/game/PurpleRocketStream.h"
#include "gnome_fortress/game/ShotgunStream.h"
#include "gnome_fortress/game/RocketGround.h"
#include "gnome_fortress/game/SporeGround.h"
#include "gnome_fortress/game/TextNode.h"
#include "gnome_fortress/game/Walls.h"
#include "gnome_fortress/game/Wall.h"
#include "gnome_fortress/camera/SceneNodeCamera.h"
#include "gnome_fortress/model/Mesh.h"
#include "gnome_fortress/model/Skybox.h"
#include "gnome_fortress/resource/ResourceManager.h"
#include "gnome_fortress/ui/SpriteNode.h"

namespace gnome_fortress {
namespace game {

class Game {
public:
    // Constructor and destructor
    Game();

    enum Scene {
        NONE,
        TITLE,
        GAME
    };

    // Call Init() before calling any other method
    void Init();

    // Call Destroy() before after everything else
    void Destroy();

    // Run the game: keep the application active
    void MainLoop();

    // Cursor callback function, called whenever the cursor position is updated
    void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

    // Capture mouse button presses
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    // Capture mouse scroll events to change weapons
    void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    // Callback for when a key is pressed
    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // Callback for when the window is resized
    void ResizeCallback(GLFWwindow* window, int width, int height);

private:
    // Methods to initialize the game
    void InitWindow();

    // clean up the current scene and switch to the given scene
    void switchToScene(Scene newScene);

    // Set up the title screen
    void SetupTitle();

    // Set up the title screen
    void CleanupTitle();

    // Call every frame during the title
    void TitleLoop(float deltaTime);

    // Set up the game scene
    void SetupScene();

    // Clean up the game scene
    void CleanupScene();

    // Call every frame during the game
    void SceneLoop(float deltaTime);

    // Create a fence around the perimeter of the playing area
    void createOuterFences(std::vector<model::BasicMeshGroupNode *> &fences, renderer::BasicMeshNodeTechnique *technique);

    // Create a random tree around the edge of the scene
    model::BasicMeshGroupNode *createRandomTree(renderer::BasicMeshNodeTechnique *technique);

    // Distribute the trees around the outside of the scene
    void distributeTrees(const std::vector<model::BasicMeshGroupNode *> &trees, float minDist, float maxDist, float collisionRadius);

    void Game::spawnInitialEnemies();


    // GLFW window and viewport
    GLFWwindow *window;
    std::string windowTitle;
    float viewportWidth;
    float viewportHeight;
    glm::vec3 viewportBackgroundColor;

    // Geometry to use for all UI
    GLuint screenQuadVBO;

    // Current scene
    Scene currentScene;

    // game variables
    double startTime;
    double spawnTime;
    double difficultyTime;
    int score;

    // Cameras
    camera::Camera *debugCamera;
    camera::SceneNodeCamera *firstPersonCamera;
    camera::SceneNodeCamera *thirdPersonCamera;

    // this is not a camera instance but rather points to one of the other camera instances
    camera::Camera *activeCamera;
    float cameraAngle;

    // Our main sound engine
    ISoundEngine *soundEngine;

    // Resource manager
    resource::ResourceManager *resourceManager;

    // Rendering techniques
    renderer::BasicMeshNodeTechnique *mtlThreeTermTechnique;
    renderer::SkyboxTechnique *skyboxTechnique;
    game::RocketStreamTechnique *rocketStreamTechnique;
    game::PurpleRocketStreamTechnique *purpleRocketStreamTechnique;
    game::ShotgunStreamTechnique *shotgunStreamTechnique;
    game::SporeGroundTechnique *sporeGroundTechnique;
    game::RocketGroundTechnique *rocketGroundTechnique;
    renderer::SpriteTechnique *spriteTechnique;

    // plane geometry
    model::MeshGroup *plane;

    // The root scene node
    model::SceneNode *papaNode;
    // The root ui node
    ui::UINode *uiNode;

    // Nodes in the scene
    model::BasicMeshNode *ground;
    game::Player *player;
    game::Weapon *peanutGun;
    game::Weapon *mushroomGun;
    game::Weapon *pineconeGun;
    game::Walls *walls;
    game::Enemies *enemies;
    game::Projectiles *playerProjectiles;
    game::Acorns *acorns;
    model::Skybox *skybox;
    std::vector<model::BasicMeshGroupNode *> outerFences;
    std::vector<model::BasicMeshGroupNode *> trees;
    std::vector<Weapon*> weapons;

    // Nodes in the UI
    game::AcornMeter *acornMeter;
    ui::SpriteNode *crosshair;
    game::TextNode *scoreText;

    // Title screen UI nodes
    game::TextNode *titleText;
    game::TextNode *titleCreditsText;
    game::TextNode *titleCreditsText2;
    game::TextNode *titleSpaceToStartText;
    game::TextNode *titleControlsText;
    game::TextNode *titleControlsTextWASD;
    game::TextNode *titleControlsTextSpace;
    game::TextNode *titleControlsTextShift;
    game::TextNode *titleControlsTextClick;
    game::TextNode *titleControlsTextScroll;
    game::TextNode *titleControlsTextC;
    game::TextNode *titleControlsTextESC;
    game::TextNode *titleYourScoreText;
};

}
}