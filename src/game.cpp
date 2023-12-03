#include "game_lib.hpp"

int main(int argc, char* args[])
{
    // Inicialización de SDL y otros requisitos

    Character character;
    character.init("path_up.bmp", "path_shoot.bmp");

    // Bucle principal
    while (!quit)
    {
        character.handleEvent(e, isShooting, bullets);
        character.update(isShooting, bullets);
        character.render(isShooting, bullets);

        // Resto del bucle principal
    }

    // Cierre y liberación de recursos

    return 0;
}
