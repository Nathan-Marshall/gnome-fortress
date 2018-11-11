#pragma once

#include <string>

namespace gnome_fortress {
namespace game {

namespace resources {

namespace models {
    const std::string dirname = "models/";

    const std::string cube = models::dirname + "cube/cube.obj";
    const std::string gnome = models::dirname + "gnome/gnome.obj";
    const std::string mushroom_gun = models::dirname + "mushroom_gun/mushroom_gun.obj";
    const std::string peanut_gun = models::dirname + "peanut_gun/peanut_gun.obj";
    const std::string plane = models::dirname + "plane/plane.obj";
    const std::string rock1 = models::dirname + "rocks/rock1.obj";
    const std::string rock2 = models::dirname + "rocks/rock2.obj";
    const std::string rock3 = models::dirname + "rocks/rock3.obj";
    const std::string rock4 = models::dirname + "rocks/rock4.obj";
    const std::string rock5 = models::dirname + "rocks/rock5.obj";
    const std::string siege_turtle = models::dirname + "siege_turtle/siege_turtle.obj";
}

namespace shaders {
    const std::string dirname = "shaders/";

    const std::string textured_material = shaders::dirname + "textured_material";
}

}

}
}