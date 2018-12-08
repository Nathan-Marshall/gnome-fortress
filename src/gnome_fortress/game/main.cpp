#include "gnome_fortress/game/Game.h"

using namespace gnome_fortress::game;

// Main function that builds and runs the game
int main(void) {
    Game app; // Game application

    try {
        // Initialize game
        app.Init();

        // Setup the scene in the game
        app.SetupScene();
        // Run game
        app.MainLoop();
        // Clean up the scene in the game
        app.CleanupScene();

        // Destroy the game
        app.Destroy();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}