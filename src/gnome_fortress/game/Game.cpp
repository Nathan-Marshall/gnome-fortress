/*
 * Copyright (c) 2018 Nathan Marshall <NathanMarshall@cmail.carleton.ca>, Mitchell Blanchard <MiitchellBlanchard@cmail.carleton.ca>, Megan Perera <MeganPerera@cmail.carleton.ca>,
 * Oliver van Kaick <Oliver.vanKaick@carleton.ca>, David Mould <mould@scs.carleton.ca>
 *
 */

#include "gnome_fortress/game/Game.h"

#include "resources_config.h"

namespace gnome_fortress {
namespace game {

Game::Game() {

}

void Game::Init() {
    srand(time(0));

    InitWindow();

    // set up screen quad vbo for UI
    glGenBuffers(1, &screenQuadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
    // POSITION (2)
    GLfloat screenQuadData[] = {
        -1, -1,
         1, -1,
         1,  1,
        -1,  1,
    };
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), &screenQuadData, GL_STATIC_DRAW);

    // initialize IrrKlang sound engine
    soundEngine = createIrrKlangDevice();

    // initialize resource manager to the resource directory defined in resources_config.h
    resourceManager = new resource::ResourceManager(RESOURCES_DIRECTORY);
}

void Game::Destroy() {
    glDeleteBuffers(1, &screenQuadVBO);
    delete resourceManager;
}

void Game::InitWindow() {
    windowTitle = "Gnome Fortress";
    viewportWidth = 800;
    viewportHeight = 600;
    viewportBackgroundColor = glm::vec3(0.5, 0.5, 0.5);

    // Initialize the window management library (GLFW)
    if (!glfwInit()) {
        throw(std::runtime_error(std::string("Could not initialize the GLFW library")));
    }

    // Create a window and its OpenGL context
    window = glfwCreateWindow(viewportWidth, viewportHeight, windowTitle.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw(std::runtime_error(std::string("Could not create window")));
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, viewportWidth / 2, viewportHeight / 2);

    // Make the window's OpenGL context the current one
    glfwMakeContextCurrent(window);

    // Initialize the GLEW library to access OpenGL extensions
    // Need to do it after initializing an OpenGL context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw(std::runtime_error(std::string("Could not initialize the GLEW library: ") + std::string((const char *)glewGetErrorString(err))));
    }

    // set initial window viewport and projection
    ResizeCallback(window, viewportWidth, viewportHeight);

    // set the GLFW window user pointer to access Game's functions
    glfwSetWindowUserPointer(window, this);

    // set input event callbacks
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        static_cast<Game*>(glfwGetWindowUserPointer(window))->KeyCallback(window, key, scancode, action, mods);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        static_cast<Game*>(glfwGetWindowUserPointer(window))->CursorPosCallback(window, xpos, ypos);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        static_cast<Game*>(glfwGetWindowUserPointer(window))->MouseButtonCallback(window, button, action, mods);
    });
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        static_cast<Game*>(glfwGetWindowUserPointer(window))->ResizeCallback(window, width, height);
    });
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        static_cast<Game*>(glfwGetWindowUserPointer(window))->ScrollCallback(window, xoffset, yoffset);
    });
}

void Game::SetupScene() {
    score = 0;

    soundEngine->setSoundVolume(0.1);

    // Set up shaders and techniques
    GLuint mtlThreeTermProgram = resourceManager->getOrLoadShaderProgram(resources::shaders::textured_material);
    mtlThreeTermTechnique = new renderer::BasicMeshNodeTechnique(mtlThreeTermProgram);
    mtlThreeTermTechnique->setEnvMap(resourceManager->getOrLoadSkyboxTexture(resources::textures::noon_grass));

    GLuint skyboxProgram = resourceManager->getOrLoadShaderProgram(resources::shaders::skybox);
    skyboxTechnique = new renderer::SkyboxTechnique(skyboxProgram);

    GLuint rocketStreamProgram = resourceManager->getOrLoadShaderProgram(resources::shaders::rocket_stream);
    rocketStreamTechnique = new RocketStreamTechnique(rocketStreamProgram);

    GLuint purpleRocketStreamProgram = resourceManager->getOrLoadShaderProgram(resources::shaders::rocket_stream_purple);
    purpleRocketStreamTechnique = new PurpleRocketStreamTechnique(purpleRocketStreamProgram);

    GLuint shotgunStreamProgram = resourceManager->getOrLoadShaderProgram(resources::shaders::shotgun_stream);
    shotgunStreamTechnique = new ShotgunStreamTechnique(shotgunStreamProgram);

    GLuint sporeGroundProgram = resourceManager->getOrLoadShaderProgram(resources::shaders::spore_ground);
    sporeGroundTechnique = new SporeGroundTechnique(sporeGroundProgram);

    GLuint rocketGroundProgram = resourceManager->getOrLoadShaderProgram(resources::shaders::rocket_ground);
    rocketGroundTechnique = new RocketGroundTechnique(rocketGroundProgram);

    // Play the background track
    irrklang::ISound *backgroundTrack = soundEngine->play2D(resourceManager->getOrLoadAudioClip(resources::audioClips::bit_builders), GL_TRUE);

    // Create the root scene node for the game
    papaNode = new model::SceneNode();

    // Create our skybox and append it to the root node
    skybox = new model::Skybox(resourceManager->getOrLoadSkyboxTexture(resources::textures::noon_grass), skyboxTechnique);
    papaNode->appendChild(skybox);

    // Create the walls and append to the root node
    walls = new Walls(*resourceManager, mtlThreeTermTechnique);
    papaNode->appendChild(walls);

    // Create our player, set initial position, and append to the root node
    player = new game::Player(*resourceManager, mtlThreeTermTechnique, rocketStreamTechnique);
    player->setPosition(0, 0.7f, 3.0f);
    papaNode->appendChild(player);

    // Create the player projectiles collection node and append to the root node
    playerProjectiles = new Projectiles(resourceManager, sporeGroundTechnique, rocketGroundTechnique, rocketStreamTechnique, purpleRocketStreamTechnique, shotgunStreamTechnique);
    papaNode->appendChild(playerProjectiles);

    // Create weapons
    peanutGun = new PeanutGun(*resourceManager, mtlThreeTermTechnique, player, playerProjectiles, soundEngine);
    mushroomGun = new MushroomGun(*resourceManager, mtlThreeTermTechnique, player, playerProjectiles, soundEngine);
    pineconeGun = new PineconeGun(*resourceManager, mtlThreeTermTechnique, player, playerProjectiles, soundEngine);

    // setCurrentWeapon also appends as the gun as a child to player
    player->setCurrentWeapon(peanutGun);

    // Add weapons to vector
    weapons.push_back(peanutGun);
    weapons.push_back(mushroomGun);
    weapons.push_back(pineconeGun);

    // Create the enemies
    enemies = new Enemies(walls, [this](int change) {
        score += change;
    }, soundEngine);
    papaNode->appendChild(enemies);

    spawnInitialEnemies();

    // create and position the cameras
    debugCamera = new camera::Camera(
        glm::lookAt(glm::vec3(1.5f, 1, 3.0f), glm::vec3(0, 0.7f, 3.0f), glm::vec3(0, 1, 0))
    );
    firstPersonCamera = new camera::SceneNodeCamera();
    thirdPersonCamera = new camera::SceneNodeCamera();
    activeCamera = thirdPersonCamera;

    thirdPersonCamera->getNode()->setPosition(0, 1.2f, 3);
    firstPersonCamera->getNode()->setPosition(0.1, 0.4, -1);

    cameraAngle = 0.0f;

    // Append our cameras to the root node
    player->appendChild(firstPersonCamera->getNode());
    player->appendChild(thirdPersonCamera->getNode());

    // Create the plane and attach to the root node
    ground = new model::BasicMeshNode(resourceManager->getOrLoadMeshGroup(resources::models::ground)->meshes[0], mtlThreeTermTechnique);
    ground->setScale(1000);
    ground->setPosition(0, 0, 0);
    papaNode->appendChild(ground);

    // Create the outer fences
    outerFences.clear();
    createOuterFences(outerFences, mtlThreeTermTechnique);

    // Randomly create and distribute trees (randomly selected model, rotation, scale, position)
    trees.clear();
    int numTrees = 100;
    for (int i = 0; i < numTrees; i++) {
        trees.push_back(createRandomTree(mtlThreeTermTechnique));
    }
    distributeTrees(trees, player->XBOUND_POS + 10, player->XBOUND_POS + 30, 2.0f);

    // Create our acorns collection structure and append to the root node
    acorns = new Acorns(*resourceManager, mtlThreeTermTechnique);
    papaNode->appendChild(acorns);

    // set up 2D UI shaders and techniques
    GLuint spriteShader = resourceManager->getOrLoadShaderProgram(resources::shaders::ui_sprite);
    spriteTechnique = new renderer::SpriteTechnique(spriteShader, screenQuadVBO);

    // create UI
    uiNode = new ui::UINode();

    // create UI acorns
    acornMeter = new AcornMeter(acorns, *resourceManager, spriteTechnique);
    uiNode->appendChild(acornMeter);

    // create UI score text
    scoreText = new TextNode(*resourceManager, spriteTechnique);
    scoreText->setPosition(0.99f, 0.925f);
    scoreText->setScale(0.05f);
    scoreText->setAlignment(TextNode::Alignment::RIGHT);
    uiNode->appendChild(scoreText);

    // create crosshair
    crosshair = new ui::SpriteNode(resourceManager->getOrLoadTexture(resources::textures::ui_crosshair), spriteTechnique);
    crosshair->setScale(0.08f, 0.1f);
    uiNode->appendChild(crosshair);
}

void Game::CleanupScene() {
    // delete techniques
    delete mtlThreeTermTechnique;
    delete skyboxTechnique;
    delete rocketStreamTechnique;
    delete purpleRocketStreamTechnique;
    delete shotgunStreamTechnique;
    delete sporeGroundTechnique;
    delete rocketGroundTechnique;
    delete spriteTechnique;

    // delete cameras
    delete debugCamera;
    delete firstPersonCamera;
    delete thirdPersonCamera;

    // delete scene nodes
    delete papaNode;
    delete ground;
    delete player;
    delete enemies;
    delete peanutGun;
    delete mushroomGun;
    delete pineconeGun;
    delete walls;
    delete acorns;
    delete skybox;
    for each (auto fence in outerFences) {
        delete fence;
    }
    outerFences.clear();
    for each (auto tree in trees) {
        delete tree;
    }
    trees.clear();

    // delete UI nodes
    delete uiNode;
    delete acornMeter;
    delete crosshair;
    delete scoreText;
}

void Game::MainLoop(void) {
    double spawnTime = glfwGetTime();
    double startTime = glfwGetTime();

    double prev_time = glfwGetTime();

    double difficultyTime = 5.0;

    // Run the main loop
    while (!glfwWindowShouldClose(window)) {
        // calculate delta time
        double current_time = glfwGetTime();
        double delta_time = current_time - prev_time;
        prev_time = glfwGetTime();

        //Get the player position, look at and up vectors
        glm::vec3 playerPos = player->getPosition();
        glm::vec3 lookAt = thirdPersonCamera->getNode()->getRotation() * glm::vec3(0, 0, -1);
        glm::vec3 upVec = thirdPersonCamera->getNode()->getRotation() * glm::vec3(0, 1, 0);

        //Update the listener position of the player every frame
        soundEngine->setListenerPosition(irrklang::vec3df(playerPos.x, playerPos.y, playerPos.z), irrklang::vec3df(lookAt.x, lookAt.y, lookAt.z));

        if (current_time - spawnTime > difficultyTime && current_time - startTime > 10.0) {
            int randEnemy = (rand() % 6) + 1;

            if (randEnemy == 1) {
                //Spawn a turtle
                SiegeTurtle* turt = new SiegeTurtle(*resourceManager, mtlThreeTermTechnique, soundEngine);

                enemies->turtles.push_back(turt);
                enemies->appendChild(turt);
            } else if (randEnemy == 2) {
                //Spawn a squirrel
                Squirrel* squir = new Squirrel(*resourceManager, mtlThreeTermTechnique, enemies->walls, soundEngine);

                enemies->squirrels.push_back(squir);
                enemies->appendChild(squir);
            } else if (randEnemy == 3) {
                //Spawn a spider
                Spider* spidey = new Spider(*resourceManager, mtlThreeTermTechnique, soundEngine);

                enemies->spiders.push_back(spidey);
                enemies->appendChild(spidey);
            }

            spawnTime = glfwGetTime();

            if (difficultyTime > 1.2) {
                difficultyTime -= 0.1;
            }
        }

        //Process collisions with enemies
        enemies->ProcessCollisions(playerProjectiles, delta_time);

        //Process player collisions
        player->ProcessCollisions(walls, enemies);

        //Process projectile collisions
        playerProjectiles->ProcessCollisions(walls);

        //Process acorn collisions
        acorns->ProcessEnemyCollisions(enemies, delta_time);

        scoreText->setText(std::to_string(score));

        // Update the scene
        papaNode->update(delta_time);
        // Update the UI
        uiNode->update(delta_time);

        // Clear background
        glClearColor(viewportBackgroundColor[0], viewportBackgroundColor[1], viewportBackgroundColor[2], 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update projection matrix
        debugCamera->setViewport(viewportWidth, viewportHeight);
        firstPersonCamera->setViewport(viewportWidth, viewportHeight);
        thirdPersonCamera->setViewport(viewportWidth, viewportHeight);

        //Set the projection and view matrices for the techniques
        mtlThreeTermTechnique->setProjectionMatrix(activeCamera->getProjection());
        mtlThreeTermTechnique->setViewMatrix(activeCamera->getView());

        skyboxTechnique->setProjectionMatrix(activeCamera->getProjection());
        skyboxTechnique->setViewMatrix(activeCamera->getView());

        rocketStreamTechnique->setProjectionMatrix(activeCamera->getProjection());
        rocketStreamTechnique->setViewMatrix(activeCamera->getView());
        rocketStreamTechnique->setTimer(current_time);

        purpleRocketStreamTechnique->setProjectionMatrix(activeCamera->getProjection());
        purpleRocketStreamTechnique->setViewMatrix(activeCamera->getView());
        purpleRocketStreamTechnique->setTimer(current_time);

        shotgunStreamTechnique->setProjectionMatrix(activeCamera->getProjection());
        shotgunStreamTechnique->setViewMatrix(activeCamera->getView());
        shotgunStreamTechnique->setTimer(current_time);

        sporeGroundTechnique->setProjectionMatrix(activeCamera->getProjection());
        sporeGroundTechnique->setViewMatrix(activeCamera->getView());

        rocketGroundTechnique->setProjectionMatrix(activeCamera->getProjection());
        rocketGroundTechnique->setViewMatrix(activeCamera->getView());

        // Draw the scene nodes (first pass)
        papaNode->draw(glm::mat4(), 0);
        // Second pass (usually for blending)
        papaNode->draw(glm::mat4(), 1);

        // Render UI / HUD
        uiNode->draw(glm::mat3(), 0);

        // Push buffer drawn in the background onto the display
        glfwSwapBuffers(window);

        // Update other events like input handling
        glfwPollEvents();
    }
}

//Cursor callback function, called whenever the cursor position is updated
void Game::CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    //Get the halfway coordinated in the window to use to find our cursor offset
    double half_x = viewportWidth / 2;
    double half_y = viewportHeight / 2;

    //We get an angle to move for x and y
    float x_angle = half_x - xpos;
    float y_angle = half_y - ypos;

    //We want to set the cursor back to the middle each time
    glfwSetCursorPos(window, half_x, half_y);

    cameraAngle += y_angle * 0.0005;

    if (cameraAngle > glm::pi<float>() / 2 || cameraAngle < -glm::pi<float>() / 2) {
        cameraAngle -= y_angle * 0.0005;
        y_angle = 0.0f;
    }

    //Then we can rotate the camera based off of the calculated value
    //The offset from the middle will be larger based on how far they push the cursor to rotate
    player->rotate(x_angle * 0.001, glm::vec3(0, 1, 0));
    player->getArm()->orbit(y_angle * 0.0005, glm::vec3(1, 0, 0), glm::vec3(0, 0.49f, 0.02f));

    //Adjust both cameras so that there won't be any shift when we toggle between the two
    //Rotate the first person camera
    firstPersonCamera->getNode()->rotate(y_angle * 0.0005, glm::vec3(1.0, 0, 0));
    //Orbit the third person camera about the origin to keep the player centered on the screen
    thirdPersonCamera->getNode()->orbit(y_angle * 0.0005, glm::vec3(1.0, 0, 0), glm::vec3(0, 0, 0));
}

//Capture mouse button presses
void Game::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    // Fire gun when player left clicks
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        player->getCurrentWeapon()->setPressed(true);
    }
    else { 
        player->getCurrentWeapon()->setPressed(false);
    }
}

//Capture mouse scroll events to change weapons
void Game::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    //If scrolling up
    if (yoffset > 0) {
        if (player->getWeaponIndex() < 2) {
            player->incrementWeaponIndex();
        }
        else if (player->getWeaponIndex() == 2) {
            player->setWeaponIndex(0);
        }
        player->getCurrentWeapon()->setPressed(false);
        player->setCurrentWeapon(weapons.at(player->getWeaponIndex()));
    }
    //If scrolling down
    if (yoffset < 0) {
        if (player->getWeaponIndex() > 0) {
            player->decrementWeaponIndex();
        }
        else if (player->getWeaponIndex() == 0) {
            player->setWeaponIndex(2);
        }
        player->getCurrentWeapon()->setPressed(false);
        player->setCurrentWeapon(weapons.at(player->getWeaponIndex()));
    }
}

// Callback for when a key is pressed
void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // Toggle the camera (first/third person) when pressing 'c'
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        if (activeCamera == firstPersonCamera) {
            activeCamera = thirdPersonCamera;
        } else {
            activeCamera = firstPersonCamera;
        }
    }

    // Move the player forward when pressing 'w'
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        player->SetForwardPressed(true);
    } else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
        player->SetForwardPressed(false);
    }

    // Move the player backwards when pressing 's'
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        player->SetBackPressed(true);
    } else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
        player->SetBackPressed(false);
    }

    // Move the player left when pressing 'a'
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        player->SetLeftPressed(true);
    } else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
        player->SetLeftPressed(false);
    }

    // Move the player right when pressing 'd'
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        player->SetRightPressed(true);
    } else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
        player->SetRightPressed(false);
    }

    // Move the player up when pressing 'left shift'
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
        player->SetDownPressed(true);
    } else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
        player->SetDownPressed(false);
    }

    // Move the player down when pressing 'space'
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        player->SetUpPressed(true);
    } else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        player->SetUpPressed(false);
    }

    // Exit the program when pressing 'esc'
    if (key == GLFW_KEY_ESCAPE) {
        exit(0);
    }
}

// Callback for when the window is resized
void Game::ResizeCallback(GLFWwindow* window, int width, int height) {
    // Set OpenGL viewport based on framebuffer width and height
    glViewport(0, 0, width, height);

    viewportWidth = width;
    viewportHeight = height;
}

void Game::createOuterFences(std::vector<model::BasicMeshGroupNode *> &fences, renderer::BasicMeshNodeTechnique *technique) {
    int fencesPerSide = 14;
    float sideLength = 70.0f;
    float fenceLength = sideLength / fencesPerSide;

    /*
    for (int side = 0; side < 4; side++) {
        for (int i = 0; i < fencesPerSide; i++) {
            model::BasicMeshGroupNode *fence = new model::BasicMeshGroupNode(resourceManager.getOrLoadMeshGroup(resources::models::flat_fence), technique);

            // scale, position, rotation
            fence->setScale(fenceLength * 1.08f);
            glm::vec3 position = glm::vec3(-sideLength / 2 + i * fenceLength + fenceLength / 2 + 0.08f, 0, sideLength / 2);
            float rotation = glm::pi<float>() / 2 * side;
            fence->setOrbit(rotation, glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), position);

            auto meshNode = dynamic_cast<model::BasicMeshNode *>(fence->getChild(0));
            if (meshNode) {
                meshNode->setBackCulling(false);
                meshNode->setAmbientFactor(0.8f);
            }

            // add to scene
            papaNode->appendChild(fence);

            // add to array
            fences.push_back(fence);
        }
    }
    */

    /* Because we are not batching right now, having individual fences segments causes many draw calls which slows down rendering.
     * To work around this for now, we have created a single model with all fences in fixed positions. */

    model::BasicMeshGroupNode *fence = new model::BasicMeshGroupNode(resourceManager->getOrLoadMeshGroup(resources::models::full_flat_fence), technique);
    fence->setScale(sideLength);
    auto meshNode = dynamic_cast<model::BasicMeshNode *>(fence->getChild(1));
    if (meshNode) {
        meshNode->setBackCulling(false);
        meshNode->setAmbientFactor(0.8f);
    }
    papaNode->appendChild(fence);
    fences.push_back(fence);
}

//Create a random tree around the edge of the scene
model::BasicMeshGroupNode *Game::createRandomTree(renderer::BasicMeshNodeTechnique *technique) {
    int treeModelIndex = rand() % 5;

    std::string treeModel = "";

    if (treeModelIndex == 0) {
        treeModel = resources::models::tree_conifer;
    } else if (treeModelIndex == 1) {
        treeModel = resources::models::tree2;
    } else if (treeModelIndex == 2) {
        treeModel = resources::models::tree3;
    } else if (treeModelIndex == 3) {
        treeModel = resources::models::tree4;
    } else if (treeModelIndex == 4) {
        treeModel = resources::models::tree5;
    }

    model::BasicMeshGroupNode *tree = new model::BasicMeshGroupNode(resourceManager->getOrLoadMeshGroup(treeModel), technique);
    // search for leaf meshes in the mesh group by checking the materials they use
    tree->forEachChild([](model::SceneNode *child) {
        auto meshNode = dynamic_cast<model::BasicMeshNode *>(child);
        if (!meshNode || !meshNode->getMesh() || !meshNode->getMesh()->material) {
            return;
        }
        const std::string &matName = meshNode->getMesh()->material->name;
        if (matName == "Leaf" || matName == "Leaves" || matName == "Leaves1") {
            // turn off back face culling and add extra ambient light for leaves
            meshNode->setBackCulling(false);
            meshNode->setAmbientFactor(0.7);
        }
    });

    // scale, rotation
    float randomScale = 14 + 11.5f * (rand() / (float)RAND_MAX);
    tree->setScale(randomScale);
    float randomRotation = 2 * glm::pi<float>() * (rand() / (float)RAND_MAX);
    tree->setRotation(randomRotation, glm::vec3(0, 1, 0));

    // add to scene
    papaNode->appendChild(tree);

    return tree;
}

//Distribute the trees around the outside of the scene
void Game::distributeTrees(const std::vector<model::BasicMeshGroupNode *> &trees, float minDist, float maxDist, float collisionRadius) {
    float collisionRadSq = collisionRadius * collisionRadius;
    float maxMinDiff = (maxDist - minDist);

    std::vector<glm::vec3> treePositions;

    for each (auto tree in trees) {
        glm::vec3 pos;

        bool collision = true;
        while (collision) {
            // get x and z coordinates from -1 to 1
            float randX = -1 + 2 * (rand() / (float)RAND_MAX);
            float randZ = -1 + 2 * (rand() / (float)RAND_MAX);

            // set the position so that it lies on the edge of a square with side length 2 (XZ plane, centered at the origin)
            pos = glm::vec3(randX, 0 , randZ) * minDist;
            pos /= glm::sqrt(randX*randX + randZ*randZ);

            // adjust the position so that it lies outside the square with side length (2*minDist) and inside the square with side length (2*maxDist)
            pos.x += randX * maxMinDiff;
            pos.z += randZ * maxMinDiff;

            // find a new position if the tree is too close to another tree
            collision = false;
            for each (auto &otherPos in treePositions) {
                glm::vec3 diff = pos - otherPos;
                if (glm::abs(diff.x * diff.z) < collisionRadSq) {
                    collision = true;
                    break;
                }
            }
        }

        tree->setPosition(pos);
        treePositions.push_back(pos);
    }
}

void Game::spawnInitialEnemies() {
    // Spawn some turtles
    SiegeTurtle* turt1 = new SiegeTurtle(*resourceManager, mtlThreeTermTechnique, soundEngine);
    SiegeTurtle* turt2 = new SiegeTurtle(*resourceManager, mtlThreeTermTechnique, soundEngine);

    // Add the turtles to our enemies
    enemies->turtles.push_back(turt1);
    enemies->appendChild(turt1);

    enemies->turtles.push_back(turt2);
    enemies->appendChild(turt2);

    // Spawn some spiders
    Spider* spi1 = new Spider(*resourceManager, mtlThreeTermTechnique, soundEngine);
    Spider* spi2 = new Spider(*resourceManager, mtlThreeTermTechnique, soundEngine);

    // Add the spiders to our enemies
    enemies->spiders.push_back(spi1);
    enemies->appendChild(spi1);

    enemies->spiders.push_back(spi2);
    enemies->appendChild(spi2);

    // Spawn some squirrels
    Squirrel* squir1 = new Squirrel(*resourceManager, mtlThreeTermTechnique, enemies->walls, soundEngine);
    Squirrel* squir2 = new Squirrel(*resourceManager, mtlThreeTermTechnique, enemies->walls, soundEngine);

    // Add the squirrels to our enemies
    enemies->squirrels.push_back(squir1);
    enemies->appendChild(squir1);

    enemies->squirrels.push_back(squir2);
    enemies->appendChild(squir2);
}

}
}