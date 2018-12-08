#include "gnome_fortress/game/Game.h"

using namespace gnome_fortress::game;

// Main function that builds and runs the game
int main(void) {
    Game app; // Game application

    try {
        // Initialize game
        app.Init();

        // Run game
        app.MainLoop();

        // Destroy game
        app.Destroy();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}