cmake_minimum_required(VERSION 3.8)

# Name of project
project(Gnome_Fortress)

# Specify project header files
set(HDRS
    include/gnome_fortress/camera/Camera.h
    include/gnome_fortress/camera/SceneNodeCamera.h
    
    include/gnome_fortress/game/Player.h
    include/gnome_fortress/game/Acorn.h
    include/gnome_fortress/game/Acorns.h
    include/gnome_fortress/game/Enemies.h
    include/gnome_fortress/game/Enemy.h
    include/gnome_fortress/game/MushroomGun.h
    include/gnome_fortress/game/SiegeTurtle.h
    include/gnome_fortress/game/Squirrel.h
    include/gnome_fortress/game/Spider.h
    include/gnome_fortress/game/PeanutGun.h
    include/gnome_fortress/game/PineconeGun.h
    include/gnome_fortress/game/Projectile.h
    include/gnome_fortress/game/Projectiles.h
    include/gnome_fortress/game/Resources.h
    include/gnome_fortress/game/Rock.h
    include/gnome_fortress/game/Rocket.h
    include/gnome_fortress/game/RocketStream.h
    include/gnome_fortress/game/RocketStreamTechnique.h
    include/gnome_fortress/game/SporeGround.h
    include/gnome_fortress/game/SporeGroundTechnique.h
    include/gnome_fortress/game/RocketGround.h
    include/gnome_fortress/game/RocketGroundTechnique.h
    include/gnome_fortress/game/Spore.h
    include/gnome_fortress/game/Weapon.h
    include/gnome_fortress/game/Wall.h
    include/gnome_fortress/game/Walls.h
   
    include/gnome_fortress/model/BasicMeshGroupNode.h
    include/gnome_fortress/model/BasicMeshNode.h
    include/gnome_fortress/model/Material.h
    include/gnome_fortress/model/Mesh.h
    include/gnome_fortress/model/MeshGroup.h
    include/gnome_fortress/model/PointSet.h
    include/gnome_fortress/model/SceneNode.h
    include/gnome_fortress/model/Skybox.h
    include/gnome_fortress/model/Texture.h
    
    include/gnome_fortress/renderer/BasicMeshNodeTechnique.h
    include/gnome_fortress/renderer/BasicProjectionTechnique.h
    include/gnome_fortress/renderer/SkyboxTechnique.h
    include/gnome_fortress/renderer/Technique.h
    include/gnome_fortress/renderer/Uniform.h
    include/gnome_fortress/renderer/VertexAttribute.h

    include/gnome_fortress/resource/FileReader.h
    include/gnome_fortress/resource/MeshGroupLoader.h
    include/gnome_fortress/resource/ResourceManager.h
    include/gnome_fortress/resource/ShaderProgramLoader.h
    include/gnome_fortress/resource/TextureLoader.h

    include/objl/OBJ_Loader.h
)

# Specify project source files
set(SRCS
    src/gnome_fortress/camera/Camera.cpp
    src/gnome_fortress/camera/SceneNodeCamera.cpp

    src/gnome_fortress/game/Player.cpp
    src/gnome_fortress/game/Acorn.cpp
    src/gnome_fortress/game/Acorns.cpp
    src/gnome_fortress/game/Enemies.cpp
    src/gnome_fortress/game/Enemy.cpp
    src/gnome_fortress/game/MushroomGun.cpp
    src/gnome_fortress/game/SiegeTurtle.cpp
    src/gnome_fortress/game/Squirrel.cpp
    src/gnome_fortress/game/Spider.cpp
    src/gnome_fortress/game/PeanutGun.cpp
    src/gnome_fortress/game/PineconeGun.cpp
    src/gnome_fortress/game/Projectile.cpp
    src/gnome_fortress/game/Projectiles.cpp
    src/gnome_fortress/game/Rock.cpp
    src/gnome_fortress/game/Rocket.cpp
    src/gnome_fortress/game/RocketStream.cpp
    src/gnome_fortress/game/RocketStreamTechnique.cpp
    src/gnome_fortress/game/SporeGround.cpp
    src/gnome_fortress/game/SporeGroundTechnique.cpp
    src/gnome_fortress/game/RocketGround.cpp
    src/gnome_fortress/game/RocketGroundTechnique.cpp
    src/gnome_fortress/game/Spore.cpp
    src/gnome_fortress/game/main.cpp
    src/gnome_fortress/game/Weapon.cpp
    src/gnome_fortress/game/Wall.cpp
    src/gnome_fortress/game/Walls.cpp
    
    src/gnome_fortress/model/BasicMeshGroupNode.cpp
    src/gnome_fortress/model/BasicMeshNode.cpp
    src/gnome_fortress/model/Material.cpp
    src/gnome_fortress/model/Mesh.cpp
    src/gnome_fortress/model/MeshGroup.cpp
    src/gnome_fortress/model/PointSet.cpp
    src/gnome_fortress/model/SceneNode.cpp
    src/gnome_fortress/model/Skybox.cpp
    src/gnome_fortress/model/Texture.cpp
    
    src/gnome_fortress/renderer/BasicMeshNodeTechnique.cpp
    src/gnome_fortress/renderer/BasicProjectionTechnique.cpp
    src/gnome_fortress/renderer/SkyboxTechnique.cpp
    src/gnome_fortress/renderer/Technique.cpp
    src/gnome_fortress/renderer/Uniform.cpp
    src/gnome_fortress/renderer/VertexAttribute.cpp

    src/gnome_fortress/resource/FileReader.cpp
    src/gnome_fortress/resource/MeshGroupLoader.cpp
    src/gnome_fortress/resource/ResourceManager.cpp
    src/gnome_fortress/resource/ShaderProgramLoader.cpp
    src/gnome_fortress/resource/TextureLoader.cpp
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
    find_library(IK_LIBRARY irrKlang)
elseif(WIN32)
    find_library(GLEW_LIBRARY glew32s HINTS ${LIBRARY_PATH}/lib)
    find_library(GLFW_LIBRARY glfw3 HINTS ${LIBRARY_PATH}/lib)
    find_library(SOIL_LIBRARY SOIL HINTS ${LIBRARY_PATH}/lib)
    find_library(IK_LIBRARY irrKlang HINTS ${LIBRARY_PATH}/lib)
endif(NOT WIN32)
target_link_libraries(${MAIN_EXECUTABLE} ${GLEW_LIBRARY})
target_link_libraries(${MAIN_EXECUTABLE} ${GLFW_LIBRARY})
target_link_libraries(${MAIN_EXECUTABLE} ${SOIL_LIBRARY})
target_link_libraries(${MAIN_EXECUTABLE} ${IK_LIBRARY})

# The rules here are specific to Windows Systems
if(WIN32)
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(${MAIN_EXECUTABLE} PROPERTIES DEBUG_POSTFIX _d)

    # Automatically generate source groups for Visual Studio
    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HDRS} ${SRCS})
endif(WIN32)
