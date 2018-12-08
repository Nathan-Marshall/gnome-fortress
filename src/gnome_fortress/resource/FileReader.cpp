/*
 * Copyright (c) 2018 Nathan Marshall <NathanMarshall@cmail.carleton.ca>, Mitchell Blanchard <MiitchellBlanchard@cmail.carleton.ca>, Megan Perera <MeganPerera@cmail.carleton.ca>,
 * Oliver van Kaick <Oliver.vanKaick@carleton.ca>, David Mould <mould@scs.carleton.ca>
 */

#include "gnome_fortress/resource/FileReader.h"

#include <fstream>
#include <iostream>

namespace gnome_fortress {
namespace resource {

std::string ReadTextFile(const std::string &filename) {

    // Open file
    std::ifstream f;
    f.open(filename);
    if (f.fail()) {
        throw(std::ios_base::failure(std::string("Error opening file ") + std::string(filename)));
    }

    // Read file
    std::string content;
    std::string line;
    while (std::getline(f, line)) {
        content += line + "\n";
    }

    // Close file
    f.close();

    return content;
}

}
}