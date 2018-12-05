#pragma once

#include <string>

namespace gnome_fortress {
namespace game {

namespace resources {

namespace models {
    const std::string dirname = "models/";

    const std::string acorn = models::dirname + "acorn/acorn.obj";
    const std::string berry = models::dirname + "pinecone_gun/berry.obj";
    const std::string cube = models::dirname + "cube/cube.obj";
    const std::string fence = models::dirname + "fences/fence.obj";
    const std::string flat_fence = models::dirname + "large_fence/flat_fence.obj";
    const std::string full_fence = models::dirname + "large_fence/full_fence.obj";
    const std::string full_flat_fence = models::dirname + "large_fence/full_flat_fence.obj";
    const std::string gnome = models::dirname + "gnome/gnome.obj";
    const std::string ground = models::dirname + "ground/ground.obj";
    const std::string jetpack = models::dirname + "jetpack/jetpack.obj";
    const std::string large_fence = models::dirname + "large_fence/large_fence.obj";
    const std::string mushroom_gun = models::dirname + "mushroom_gun/mushroom_gun.obj";
    const std::string peanut_gun = models::dirname + "peanut_gun/peanut_gun.obj";
    const std::string pinecone_gun = models::dirname + "pinecone_gun/pinecone_gun.obj";
    const std::string rock1 = models::dirname + "rocks/rock1.obj";
    const std::string rock2 = models::dirname + "rocks/rock2.obj";
    const std::string rock3 = models::dirname + "rocks/rock3.obj";
    const std::string rock4 = models::dirname + "rocks/rock4.obj";
    const std::string rock5 = models::dirname + "rocks/rock5.obj";
    const std::string siege_turtle = models::dirname + "siege_turtle/siege_turtle.obj";
    const std::string spider = models::dirname + "spider/skSpiderLargeMesh.obj";
    const std::string squirrel = models::dirname + "squirrel/Squirrel.obj";
    const std::string tree_conifer = models::dirname + "trees/Conifer_1_OBJ/Tree_Conifer_1.obj";
    const std::string tree2 = models::dirname + "trees/tree002-2/tree002-2.obj";
    const std::string tree3 = models::dirname + "trees/Low_Poly_Tree_Obj/Low_Poly_Tree_1.obj";
    const std::string tree4 = models::dirname + "trees/Low_Poly_Tree_Obj/Low_Poly_Tree_2.obj";
    const std::string tree5 = models::dirname + "trees/Low_Poly_Tree_Obj/Low_Poly_Tree_3.obj";
}

namespace shaders {
    const std::string dirname = "shaders/";

    const std::string rocket_stream = shaders::dirname + "rocket_stream";
    const std::string skybox = shaders::dirname + "skybox";
    const std::string textured_material = shaders::dirname + "textured_material";
}

namespace textures {
    const std::string dirname = "textures/";

    const std::string noon_grass = textures::dirname + "skyboxes/noon_grass/noon_grass.png";
    const std::string flame4x4 = textures::dirname + "particles/flame4x4.png";
}

namespace audioClips {
    const std::string dirname = "audio/";

    const std::string breakout = audioClips::dirname + "background/breakout.mp3";
    const std::string action_rhythm = audioClips::dirname + "background/action_rhythm.mp3";
    const std::string bit_builders = audioClips::dirname + "background/bit_builders.mp3";
    const std::string bog_creatures = audioClips::dirname + "background/bog_creatures.mp3";
    const std::string spider_atk = audioClips::dirname + "enemies/spider_atk.mp3";
    const std::string turtle_atk = audioClips::dirname + "enemies/turtle_atk.mp3";
    const std::string squirrel_atk = audioClips::dirname + "enemies/squirrel_atk.mp3";
    const std::string shotgun = audioClips::dirname + "weapons/shotgun.mp3";
    const std::string mushroom = audioClips::dirname + "weapons/mushroom.mp3";
    const std::string rocket = audioClips::dirname + "weapons/rocket.mp3";
}

}

}
}