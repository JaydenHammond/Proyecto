#include "mapa.h"

int main(int argc, char* args[]) {
    SDLApp sdlApp;

// Inicializa SDL y crea la ventana
    if (!sdlApp.init()) {
        printf("¡Error al inicializar!\n");
    } else {
        // Carga los recursos multimedia
        if (!sdlApp.loadMedia()) {
            printf("¡Error al cargar los medios!\n");
        } else {
            // Ejecuta la aplicación
            sdlApp.run();
        }
    }

    return 0;
}

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("DOOM PITERO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia(Player& player)
{
    bool success = true;

    // Imágenes de movimiento hacia arriba
    player.surfaces[KEY_PRESS_SURFACE_UP][0] = loadSurface("assets/images/Slayer/Slayer/Arma/BFG/SlayerUP.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_UP][0] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }
    player.surfaces[KEY_PRESS_SURFACE_UP][1] = loadSurface("assets/images/Armas/BFG/BalaUp.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_UP][1] == NULL)
    {
        printf("Failed to load shoot image!\n");
        success = false;
    }

    // Imágenes de movimiento hacia abajo
    player.surfaces[KEY_PRESS_SURFACE_DOWN][0] = loadSurface("assets/images/Slayer/Slayer/Arma/BFG/SlayerDown.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_DOWN][0] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }
    player.surfaces[KEY_PRESS_SURFACE_DOWN][1] = loadSurface("assets/images/Armas/BFG/BalaDown.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_DOWN][1] == NULL)
    {
        printf("Failed to load shoot image!\n");
        success = false;
    }

    // Imágenes de movimiento hacia la izquierda
    player.surfaces[KEY_PRESS_SURFACE_LEFT][0] = loadSurface("assets/images/Slayer/Slayer/Arma/BFG/SlayerLeft.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_LEFT][0] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }
    player.surfaces[KEY_PRESS_SURFACE_LEFT][1] = loadSurface("assets/images/Armas/BFG/BalaLeft.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_LEFT][1] == NULL)
    {
        printf("Failed to load shoot image!\n");
        success = false;
    }

    // Imágenes de movimiento hacia la derecha
    player.surfaces[KEY_PRESS_SURFACE_RIGHT][0] = loadSurface("assets/images/Slayer/Slayer/Arma/BFG/SlayerRight.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_RIGHT][0] == NULL)
    {
        printf("Failed to load right image!\n");
        success = false;
    }
    player.surfaces[KEY_PRESS_SURFACE_RIGHT][1] = loadSurface("assets/images/Armas/BFG/BalaRight.bmp");
    if (player.surfaces[KEY_PRESS_SURFACE_RIGHT][1] == NULL)
    {
        printf("Failed to load shoot image!\n");
        success = false;
    }

    return success;
}

void close(Player& player)
{
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            SDL_FreeSurface(player.surfaces[i][j]);
            player.surfaces[i][j] = NULL;
        }
    }

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 177, 64));
    }

    return loadedSurface;
}

void renderMap(int map[])
{
    // Renderizar el mapa de tiles en la pantalla
    for (int i = 0; i < 100; ++i)
    {
        int tileX = (i % 10) * TILE_SIZE;
        int tileY = (i / 10) * TILE_SIZE;

        SDL_Rect tileRect = {tileX, tileY, TILE_SIZE, TILE_SIZE};

        switch (map[i])
        {
        case 1:
            // Renderizar tile 1 (puedes cargar la imagen correspondiente)
            tile1 = loadSurface("assets/images/Tiles/1.png");
            SDL_BlitSurface(tile1, NULL, gScreenSurface, &tileRect);
            break;

        case 2:
            // Renderizar tile 2 (puedes cargar la imagen correspondiente)
            tile2 = loadSurface("assets/images/Tiles/2.png");
            SDL_BlitSurface(tile2, NULL, gScreenSurface, &tileRect);
            break;

        case 3:
            // Renderizar tile 3 (puedes cargar la imagen correspondiente)
            tile3 = loadSurface("assets/images/Tiles/3.png");
            SDL_BlitSurface(tile3, NULL, gScreenSurface, &tileRect);
            break;

        // Agrega más casos según los tipos de tiles que tengas
        // ...

        default:
            // Renderizar tile por defecto (puedes cargar la imagen correspondiente)
            SDL_BlitSurface(tile3, NULL, gScreenSurface, &tileRect);
            break;
        }
    }
}

