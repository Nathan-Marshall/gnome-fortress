/*
 *
 * A program that demonstrates the use of hierarchical transformations
 *
 * Copyright (c) 2018 Nathan Marshall <Nathagnome_fortress@cmail.carleton.ca>,
 * Oliver van Kaick <Oliver.vanKaick@carleton.ca>, David Mould <mould@scs.carleton.ca>
 *
 */

#include <iostream>
#include <stdexcept>
#include <string>
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

#include "gnome_fortress/game/Player.h"
#include "gnome_fortress/game/PrimitiveMeshes.h"
#include "gnome_fortress/game/Wall.h"
#include "gnome_fortress/game/Walls.h"
#include "gnome_fortress/game/Turret.h"
#include "gnome_fortress/camera/SceneNodeCamera.h"
#include "gnome_fortress/model/Mesh.h"
#include "gnome_fortress/renderer/Technique.h"
#include "gnome_fortress/shader/Shader.h"

namespace gnome_fortress {
namespace game {

// Globals that define the OpenGL window and viewport
const std::string window_title_g = "Gnome Fortress";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(0.0, 0.0, 0.0);

// Globals that define the OpenGL camera view and projection
camera::Camera main_camera_g(
    glm::lookAt(glm::vec3(0, 5, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))
);

camera::SceneNodeCamera scene_camera_first_g;
camera::SceneNodeCamera scene_camera_third_g;

camera::Camera *active_camera_g = &scene_camera_first_g;

game::Player *player;

Walls* walls;

#pragma region Shader_Source

// Source code of vertex shader
const char *source_vp =
"#version 130\n\
\n\
// Vertex buffer\n\
in vec3 vertex;\n\
in vec3 color;\n\
\n\
// Uniform (global) buffer\n\
uniform mat4 world_mat;\n\
uniform mat4 view_mat;\n\
uniform mat4 projection_mat;\n\
\n\
// Attributes forwarded to the fragment shader\n\
out vec4 color_interp;\n\
\n\
\n\
void main()\n\
{\n\
    gl_Position = projection_mat * view_mat * world_mat * vec4(vertex, 1.0);\n\
    color_interp = vec4(color, 1.0);\n\
}";


// Source code of fragment shader
const char *source_fp =
"#version 130\n\
\n\
// Attributes passed from the vertex shader\n\
in vec4 color_interp;\n\
\n\
\n\
void main()\n\
{\n\
    gl_FragColor = color_interp;\n\
}";

#pragma endregion

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

	//Adjust both cameras so that there won't be any shift when we toggle between the two
	
	//Rotate the first person camera
	scene_camera_first_g.getNode()->rotate(y_angle * 0.0005, glm::vec3(1.0, 0, 0));
	//Orbit the third person camera about the origin to keep the player centered on the screen
	scene_camera_third_g.getNode()->orbit(y_angle * 0.0005, glm::vec3(1.0, 0, 0), glm::vec3(0, 0, 0));
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


// Callback for when the window is resized
void ResizeCallback(GLFWwindow* window, int width, int height){
    // Set OpenGL viewport based on framebuffer width and height
    glViewport(0, 0, width, height);

    // Update projection matrix
    main_camera_g.setViewport(width, height);
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
        glfwSetFramebufferSizeCallback(window, ResizeCallback);

        // Set up z-buffer for rendering
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Set culling of back faces
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

        // Create geometry of the cube and cylinder
		model::Mesh *plane = CreatePlane();
        model::Mesh *cube = CreateCube();
        model::Mesh *cylinder = CreateCylinder();

        // Set up shaders
        GLuint program = shader::CreateShaderProgram(source_vp, source_fp);

        GLint view_uni_location = glGetUniformLocation(program, "view_mat");
        GLint projection_uni_location = glGetUniformLocation(program, "projection_mat");
        GLint world_uni_location = glGetUniformLocation(program, "world_mat");

        GLint vertex_attr_location = glGetAttribLocation(program, "vertex");
        GLint normal_attr_location = glGetAttribLocation(program, "normal");
        GLint color_attr_location = glGetAttribLocation(program, "color");

        renderer::BasicProjectionTechnique *technique = new renderer::BasicProjectionTechnique(program, projection_uni_location, view_uni_location, world_uni_location);
        technique->addVertexAttribute(renderer::VertexAttribute(vertex_attr_location, 3, GL_FLOAT, GL_FALSE));
        technique->addVertexAttribute(renderer::VertexAttribute(normal_attr_location, 3, GL_FLOAT, GL_FALSE));
        technique->addVertexAttribute(renderer::VertexAttribute(color_attr_location, 3, GL_FLOAT, GL_FALSE));

		// Create the walls
		walls = new Walls(cube, technique);

        player = new game::Player(cube, technique);
        player->setPosition(0, 0.5f, 0);

		//Create the third person camera
        model::SceneNode *cameraNodeThird = scene_camera_third_g.getNode();
        cameraNodeThird->setPosition(0, 1, 4);
		//cameraNodeThird->rotate(-glm::pi<float>() / 60, glm::vec3(1, 0, 0));

		//Create the first person camera
		model::SceneNode *cameraNodeFirst = scene_camera_first_g.getNode();
		cameraNodeFirst->setPosition(0, 0, -1);

        player->appendChild(cameraNodeThird);
		player->appendChild(cameraNodeFirst);

		model::SceneNode *stick = new model::BasicMeshNode(plane, technique);
		stick->setScale(50, 50, 50);
		stick->setPosition(0, 0, 0);

        double prev_time = glfwGetTime();
        // Run the main loop
        while (!glfwWindowShouldClose(window)){
            // calculate delta time
            double current_time = glfwGetTime();
            double delta_time = current_time - prev_time;
            prev_time = glfwGetTime();

            // Clear background
            glClearColor(viewport_background_color_g[0], 
                            viewport_background_color_g[1],
                            viewport_background_color_g[2], 0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            technique->setProjectionMatrix(active_camera_g->getProjection());
            technique->setViewMatrix(active_camera_g->getView());

            //turret->update(delta_time);
            //turret->draw(glm::mat4());

            player->update(delta_time);
			player->draw(glm::mat4());

			stick->draw(glm::mat4());

			// Draw the walls
			walls->draw();

            // Push buffer drawn in the background onto the display
            glfwSwapBuffers(window);

            // Update other events like input handling
            glfwPollEvents();
        }

        delete technique;
        //delete turret;
        delete player;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

}
}

int main(void) {
    return gnome_fortress::game::MainFunction();
}