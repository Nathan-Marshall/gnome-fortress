cmake_minimum_required(VERSION 3.8)

# Name of project
project(Gnome_Fortress)

# Specify project header files
set(HDRS
    include/gnome_fortress/camera/Camera.h
    include/gnome_fortress/camera/SceneNodeCamera.h
    
    include/gnome_fortress/game/Player.h
    include/gnome_fortress/game/Enemies.h
    include/gnome_fortress/game/Enemy.h
    include/gnome_fortress/game/SiegeTurtle.h
    include/gnome_fortress/game/PrimitiveMeshes.h
	include/gnome_fortress/game/Projectile.h
    include/gnome_fortress/game/Turret.h
	include/gnome_fortress/game/Weapon.h
    include/gnome_fortress/game/Wall.h
    include/gnome_fortress/game/Walls.h
   
    include/gnome_fortress/model/BasicMeshNode.h
    include/gnome_fortress/model/Mesh.h
    include/gnome_fortress/model/OBJParser.h
    include/gnome_fortress/model/SceneNode.h
    include/gnome_fortress/model/Texture.h
    
    include/gnome_fortress/renderer/BasicMeshNodeTechnique.h
    include/gnome_fortress/renderer/BasicProjectionTechnique.h
    include/gnome_fortress/renderer/Technique.h
    include/gnome_fortress/renderer/Uniform.h
    include/gnome_fortress/renderer/VertexAttribute.h

    include/gnome_fortress/shader/Shader.h
)

# Specify project source files
set(SRCS
    src/gnome_fortress/camera/Camera.cpp
    src/gnome_fortress/camera/SceneNodeCamera.cpp

    src/gnome_fortress/game/Player.cpp
    src/gnome_fortress/game/Enemies.cpp
    src/gnome_fortress/game/Enemy.cpp
    src/gnome_fortress/game/SiegeTurtle.cpp
    src/gnome_fortress/game/PrimitiveMeshes.cpp
	src/gnome_fortress/game/Projectile.cpp
    src/gnome_fortress/game/main.cpp
    src/gnome_fortress/game/Turret.cpp
	src/gnome_fortress/game/Weapon.cpp
    src/gnome_fortress/game/Wall.cpp
    src/gnome_fortress/game/Walls.cpp

    src/gnome_fortress/model/BasicMeshNode.cpp
    src/gnome_fortress/model/Mesh.cpp
    src/gnome_fortress/model/OBJParser.cpp
    src/gnome_fortress/model/SceneNode.cpp
    src/gnome_fortress/model/Texture.cpp
    
    src/gnome_fortress/renderer/BasicMeshNodeTechnique.cpp
    src/gnome_fortress/renderer/BasicProjectionTechnique.cpp
    src/gnome_fortress/renderer/Technique.cpp
    src/gnome_fortress/renderer/Uniform.cpp
    src/gnome_fortress/renderer/VertexAttribute.cpp

    src/gnome_fortress/shader/Shader.cpp
)

# The following config header will be evaluated and added to "bin"
configure_file("resources_config.h.in" "resources_config.h")

# Add executable based on the source files, using the project name as the executable name
set(MAIN_EXECUTABLE ${PROJECT_NAME})
add_executable(${MAIN_EXECUTABLE} ${HDRS} ${SRCS})

# search for headers in the "include" directory, and also the "bin" directory, since that's where config headers will go
include_directories("include" "bin")

# Require OpenGL library
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${MAIN_EXECUTABLE} ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH "" CACHE PATH "Folder with GLEW, GLFW, GLM, and SOIL libraries")
include_directories(${LIBRARY_PATH}/include)
if(NOT WIN32)
    find_library(GLEW_LIBRARY GLEW)
    find_library(GLFW_LIBRARY glfw)
    find_library(SOIL_LIBRARY SOIL)
elseif(WIN32)
    find_library(GLEW_LIBRARY glew32s HINTS ${LIBRARY_PATH}/lib)
    find_library(GLFW_LIBRARY glfw3 HINTS ${LIBRARY_PATH}/lib)
    find_library(SOIL_LIBRARY SOIL HINTS ${LIBRARY_PATH}/lib)
endif(NOT WIN32)
target_link_libraries(${MAIN_EXECUTABLE} ${GLEW_LIBRARY})
target_link_libraries(${MAIN_EXECUTABLE} ${GLFW_LIBRARY})
target_link_libraries(${MAIN_EXECUTABLE} ${SOIL_LIBRARY})

# The rules here are specific to Windows Systems
if(WIN32)
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(${MAIN_EXECUTABLE} PROPERTIES DEBUG_POSTFIX _d)

    # Automatically generate source groups for Visual Studio
    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HDRS} ${SRCS})
endif(WIN32)
