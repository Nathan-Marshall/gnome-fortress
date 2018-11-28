/*
 *
 * A program that demonstrates the use of hierarchical transformations
 *
 * Copyright (c) 2018 Nathan Marshall <NathanMarshall@cmail.carleton.ca>,
 * Oliver van Kaick <Oliver.vanKaick@carleton.ca>, David Mould <mould@scs.carleton.ca>
 *
 */

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


#include "gnome_fortress/game/Acorns.h"
#include "gnome_fortress/game/Enemies.h"
#include "gnome_fortress/game/MushroomGun.h"
#include "gnome_fortress/game/PeanutGun.h"
#include "gnome_fortress/game/PineconeGun.h"
#include "gnome_fortress/game/Player.h"
#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Walls.h"
#include "gnome_fortress/game/Wall.h"
#include "gnome_fortress/camera/SceneNodeCamera.h"
#include "gnome_fortress/model/Mesh.h"
#include "gnome_fortress/model/Skybox.h"
#include "gnome_fortress/resource/ResourceManager.h"

#include "resources_config.h"

namespace gnome_fortress {
namespace game {

// Globals that define the OpenGL window and viewport
const std::string window_title_g = "Gnome Fortress";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(0.5, 0.5, 0.5);

// Globals that define the OpenGL camera view and projection
camera::Camera debug_camera_g(
    glm::lookAt(glm::vec3(1.5f, 1, 3.0f), glm::vec3(0, 0.7f, 3.0f), glm::vec3(0, 1, 0))
);

//Camera globals
camera::SceneNodeCamera scene_camera_first_g;
camera::SceneNodeCamera scene_camera_third_g;
camera::Camera *active_camera_g = &scene_camera_first_g;;

//The root scene node
model::SceneNode *papaNode;

//References to the player, weapons, walls, and enemies
game::Player *player;
game::Weapon *peanutGun;
game::Weapon *mushroomGun;
game::Weapon *pineconeGun;
game::Walls* walls;
game::Enemies* enemies;
game::Projectiles* playerProjectiles;

game::Acorns *acorns;
//game::Acorn *acorn;

//A vector for swapping through weapons 
std::vector<Weapon*> weapons;

resource::ResourceManager resource_manager_g(RESOURCES_DIRECTORY);

//Cursor callback function, called whenever the cursor position is updated
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    //Get the halfway coordinated in the window to use to find our cursor offset
    double half_x = window_width_g / 2;
    double half_y = window_height_g / 2;

    //We get an angle to move for x and y
    float x_angle = half_x - xpos;
    float y_angle = half_y - ypos;

    //We want to set the cursor back to the middle each time
    glfwSetCursorPos(window, half_x, half_y);

    //Then we can rotate the camera based off of the calculated value
    //The offset from the middle will be larger based on how far they push the cursor to rotate
    player->rotate(x_angle * 0.001, glm::vec3(0, 1, 0));
    player->getArm()->orbit(y_angle * 0.0005, glm::vec3(1, 0, 0), glm::vec3(0, 0.49f, 0.02f));

    //Adjust both cameras so that there won't be any shift when we toggle between the two
    
    //Rotate the first person camera
    scene_camera_first_g.getNode()->rotate(y_angle * 0.0005, glm::vec3(1.0, 0, 0));
    //Orbit the third person camera about the origin to keep the player centered on the screen
    scene_camera_third_g.getNode()->orbit(y_angle * 0.0005, glm::vec3(1.0, 0, 0), glm::vec3(0, 0, 0));
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    // Fire gun when player left clicks
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        player->getCurrentWeapon()->setPressed(true);
    }
    else { 
        player->getCurrentWeapon()->setPressed(false);
    }
}

void SetScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
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
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // Quit the program when pressing 'q'
    if (key == GLFW_KEY_Q && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    // Toggle the camera (first/third person) when pressing 'c'
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        if (active_camera_g == &scene_camera_first_g) {
            active_camera_g = &scene_camera_third_g;
        } else {
            active_camera_g = &scene_camera_first_g;
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
        player->SetUpPressed(true);
    } else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
        player->SetUpPressed(false);
    }

    // Move the player down when pressing 'space'
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        player->SetDownPressed(true);
    } else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        player->SetDownPressed(false);
    }

    // Exit the program when pressing 'esc'
    if (key == GLFW_KEY_ESCAPE) {
        exit(0);
    }
}

void CreateAcornPile(resource::ResourceManager &resourceManager, renderer::BasicMeshNodeTechnique *technique) {
    //Acorns to be added to pile) 
    Acorn* acorn1 = new Acorn(resource_manager_g, technique);
    acorn1->setPosition(0, 0.3, 0);
    acorns->acorns.push_back(acorn1);
    acorns->appendChild(acorn1);

    Acorn* acorn2 = new Acorn(resource_manager_g, technique);
    acorn2->setPosition(.45, 0.3, 0.45); //.25, 0.3, .25
    acorns->acorns.push_back(acorn2);
    acorns->appendChild(acorn2);

    Acorn* acorn3 = new Acorn(resource_manager_g, technique);
    acorn3->setPosition(-.40, 0.3, 0.55);
    acorns->acorns.push_back(acorn3);
    acorns->appendChild(acorn3);

    Acorn* acorn4 = new Acorn(resource_manager_g, technique);
    acorn4->setPosition(-.40, 0.3, -0.55);
    acorns->acorns.push_back(acorn4);
    acorns->appendChild(acorn4);

    Acorn* acorn5 = new Acorn(resource_manager_g, technique);
    acorn5->setPosition(.43, 0.3, -0.63);
    acorns->acorns.push_back(acorn5);
    acorns->appendChild(acorn5);

    Acorn* acorn6 = new Acorn(resource_manager_g, technique);
    acorn6->setPosition(.87, 0.3, -0.10); //.45, .3, -.12
    acorns->acorns.push_back(acorn6);
    acorns->appendChild(acorn6);

    Acorn* acorn7 = new Acorn(resource_manager_g, technique);
    acorn7->setPosition(-.87, 0.3, 0);
    acorns->acorns.push_back(acorn7);
    acorns->appendChild(acorn7);

    Acorn* acorn8 = new Acorn(resource_manager_g, technique);
    acorn8->setPosition(-.48, 0.75, -0.025);
    acorns->acorns.push_back(acorn8);
    acorns->appendChild(acorn8);

    Acorn* acorn9 = new Acorn(resource_manager_g, technique);
    acorn9->setPosition(.48, 0.75, -0.025);
    acorns->acorns.push_back(acorn9);
    acorns->appendChild(acorn9);

    Acorn* acorn10 = new Acorn(resource_manager_g, technique);
    acorn10->setPosition(0, 0.75, 0.45);
    acorns->acorns.push_back(acorn10);
    acorns->appendChild(acorn10);

    Acorn* acorn11 = new Acorn(resource_manager_g, technique);
    acorn11->setPosition(0.1, 0.75, -0.55);
    acorns->acorns.push_back(acorn11);
    acorns->appendChild(acorn11);

    Acorn* acorn12 = new Acorn(resource_manager_g, technique);
    acorn12->setPosition(0, 1.15, 0);
    acorns->acorns.push_back(acorn12);
    acorns->appendChild(acorn12);
}

// Callback for when the window is resized
void ResizeCallback(GLFWwindow* window, int width, int height){
    // Set OpenGL viewport based on framebuffer width and height
    glViewport(0, 0, width, height);

    // Update projection matrix
    debug_camera_g.setViewport(width, height);
    scene_camera_first_g.setViewport(width, height);
    scene_camera_third_g.setViewport(width, height);
}

// Main function that builds and runs the game
int MainFunction(void){
    try {
        // Initialize the window management library (GLFW)
        if (!glfwInit()){
            throw(std::runtime_error(std::string("Could not initialize the GLFW library")));
        }

        // Create a window and its OpenGL context
        GLFWwindow* window;
        window = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), NULL, NULL);
        if (!window){
            glfwTerminate();
            throw(std::runtime_error(std::string("Could not create window")));
        }

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPos(window, window_width_g / 2, window_height_g / 2);

        // Make the window's OpenGL context the current one
        glfwMakeContextCurrent(window);

        // Initialize the GLEW library to access OpenGL extensions
        // Need to do it after initializing an OpenGL context
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK){
            throw(std::runtime_error(std::string("Could not initialize the GLEW library: ")+std::string((const char *) glewGetErrorString(err))));
        }

        // set initial window viewport and projection
        ResizeCallback(window, window_width_g, window_height_g);

        // Set event callbacks for the window
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetFramebufferSizeCallback(window, ResizeCallback);
        glfwSetScrollCallback(window, SetScrollCallback);

        // Create geometry of the cube and cylinder
        model::MeshGroup *plane = resource_manager_g.getOrLoadMeshGroup(resources::models::ground);

        // Set up shaders
        GLuint program = resource_manager_g.getOrLoadShaderProgram(resources::shaders::textured_material);
        auto technique = new renderer::BasicMeshNodeTechnique(program, "projection_mat", "view_mat", "world_mat", "normal_mat", "eye_pos", "diffuse_color", "specular_color", "specular_exponent", "diffuse_map", "diffuse_map_on", "gloss_map", "gloss_map_on");
        technique->addVertexAttribute(renderer::VertexAttribute(program, "vertex", 3, GL_FLOAT, GL_FALSE));
        technique->addVertexAttribute(renderer::VertexAttribute(program, "normal", 3, GL_FLOAT, GL_FALSE));
        technique->addVertexAttribute(renderer::VertexAttribute(program, "color", 3, GL_FLOAT, GL_FALSE));
        technique->addVertexAttribute(renderer::VertexAttribute(program, "uv", 2, GL_FLOAT, GL_FALSE));

        GLuint skyboxProgram = resource_manager_g.getOrLoadShaderProgram(resources::shaders::skybox);
        auto skyboxTechnique = new renderer::SkyboxTechnique(skyboxProgram, "projection_mat", "view_mat", "world_mat", "normal_mat", "eye_pos", "cube_map");
        skyboxTechnique->addVertexAttribute(renderer::VertexAttribute(skyboxProgram, "vertex", 3, GL_FLOAT, GL_FALSE));
        skyboxTechnique->addVertexAttribute(renderer::VertexAttribute(skyboxProgram, "normal", 3, GL_FLOAT, GL_FALSE));

        papaNode = new model::SceneNode();

        model::Skybox *skybox = new model::Skybox(resource_manager_g.getOrLoadSkyboxTexture(resources::skybox::noon_grass), skyboxTechnique);
        papaNode->appendChild(skybox);

        // Create the walls
        walls = new Walls(resource_manager_g, technique);
        papaNode->appendChild(walls);

        player = new game::Player(resource_manager_g, technique);
        player->setPosition(0, 0.7f, 3.0f);
        papaNode->appendChild(player);

        playerProjectiles = new Projectiles();
        papaNode->appendChild(playerProjectiles);

        //Create weapons
        peanutGun = new PeanutGun(resource_manager_g, technique, player, playerProjectiles);
        mushroomGun = new MushroomGun(resource_manager_g, technique, player, playerProjectiles);
        pineconeGun = new PineconeGun(resource_manager_g, technique, player, playerProjectiles);

        //setCurrentWeapon also appends as the gun as a child to player
        player->setCurrentWeapon(peanutGun);

        //Add weapons to vector
        weapons.push_back(peanutGun);
        weapons.push_back(mushroomGun);
        weapons.push_back(pineconeGun);

        //Create the enemies
        Enemies* enemies = new Enemies(walls);
        papaNode->appendChild(enemies);

        //Spawn some turtles
        SiegeTurtle* turt1 = new SiegeTurtle(resource_manager_g, technique);
        SiegeTurtle* turt2 = new SiegeTurtle(resource_manager_g, technique);

        enemies->turtles.push_back(turt1);
        enemies->appendChild(turt1);

        enemies->turtles.push_back(turt2);
        enemies->appendChild(turt2);

        //Spawn some spiders
        Spider* spi1 = new Spider(resource_manager_g, technique);
        Spider* spi2 = new Spider(resource_manager_g, technique);

        enemies->spiders.push_back(spi1);
        enemies->appendChild(spi1);

        enemies->spiders.push_back(spi2);
        enemies->appendChild(spi2);

        //Spawn some squirrels
        Squirrel* squir1 = new Squirrel(resource_manager_g, technique, enemies->walls);
        Squirrel* squir2 = new Squirrel(resource_manager_g, technique, enemies->walls);

        enemies->squirrels.push_back(squir1);
        enemies->appendChild(squir1);

        enemies->squirrels.push_back(squir2);
        enemies->appendChild(squir2);

        //Create the third person camera
        model::SceneNode *cameraNodeThird = scene_camera_third_g.getNode();
        cameraNodeThird->setPosition(0, 1, 4);

        //Create the first person camera
        model::SceneNode *cameraNodeFirst = scene_camera_first_g.getNode();
        cameraNodeFirst->setPosition(0, 0, -1);
        
        player->appendChild(cameraNodeThird);
        player->appendChild(cameraNodeFirst);

        model::SceneNode *ground = new model::BasicMeshNode(plane->meshes[0], technique);
        ground->setScale(100);
        ground->setPosition(0, 0, 0);
        papaNode->appendChild(ground);

        acorns = new Acorns();
        papaNode->appendChild(acorns);

        CreateAcornPile(resource_manager_g, technique);

        double spawnTime = glfwGetTime();
        double startTime = glfwGetTime();

        double prev_time = glfwGetTime();
        // Run the main loop
        while (!glfwWindowShouldClose(window)){
            // calculate delta time
            double current_time = glfwGetTime();
            double delta_time = current_time - prev_time;
            prev_time = glfwGetTime();

            if (current_time - spawnTime > 5.0 && current_time - startTime > 10.0) {
                int randEnemy = (rand() % 6) + 1;

                if (randEnemy == 1) {
                    //Spawn a turtle
                    SiegeTurtle* turt = new SiegeTurtle(resource_manager_g, technique);

                    enemies->turtles.push_back(turt);
                    enemies->appendChild(turt);
                }
                else if (randEnemy == 2) {
                    //Spawn a squirrel
                    Squirrel* squir = new Squirrel(resource_manager_g, technique, enemies->walls);

                    enemies->squirrels.push_back(squir);
                    enemies->appendChild(squir);
                }
                else if (randEnemy == 3) {
                    //Spawn a spider
                    Spider* spidey = new Spider(resource_manager_g, technique);

                    enemies->spiders.push_back(spidey);
                    enemies->appendChild(spidey);
                }

                spawnTime = glfwGetTime();
            }

            enemies->ProcessCollisions(playerProjectiles);

            acorns->ProcessEnemyCollisions(enemies);

            // Update the scene nodes
            papaNode->update(delta_time);


            // Clear background
            glClearColor(viewport_background_color_g[0], 
                            viewport_background_color_g[1],
                            viewport_background_color_g[2], 0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            technique->setProjectionMatrix(active_camera_g->getProjection());
            technique->setViewMatrix(active_camera_g->getView());

            skyboxTechnique->setProjectionMatrix(active_camera_g->getProjection());
            skyboxTechnique->setViewMatrix(active_camera_g->getView());

            //Draw the scene nodes
            papaNode->draw(glm::mat4());

            // Push buffer drawn in the background onto the display
            glfwSwapBuffers(window);

            // Update other events like input handling
            glfwPollEvents();
        }

        delete technique;
        delete skyboxTechnique;
        delete skybox;
        delete player;
        delete enemies;
        delete peanutGun;
        delete mushroomGun;
        delete pineconeGun;
        delete walls;
        delete acorns;

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

}
}

int main(void) {
    srand(time(0));
    return gnome_fortress::game::MainFunction();
}