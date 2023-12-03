#include <sdl.h> 
#include "../include/mapa.hpp"


int main(int argc, char* args[]) {
    SDLApp app;

    // Start up SDL and create window
    if (!app.init()) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if (!app.loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            // Run the application
            app.run();
        }
    }

    return 0;
}