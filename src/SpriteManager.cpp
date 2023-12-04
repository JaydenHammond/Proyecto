// SpriteManager.cpp
#include "SpriteManager.h"

SpriteManager::SpriteManager() {
    // Constructor, inicializaciones si es necesario
}

SpriteManager::~SpriteManager() {
    // Destructor, liberar recursos si es necesario
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        for (int j = 0; j < 2; ++j) {
            SDL_FreeSurface(surfaces[i][j]);
            surfaces[i][j] = NULL;
        }
    }
}

bool SpriteManager::loadMedia(int arma) {
  bool success = true;
    
    // Seleccionar las rutas correspondientes al arma elegida
    std::string slayerPath;
    std::string balaPath;
    

    switch (arma)
    {
    case 1:
        slayerPath = "assets/images/Slayer/Slayer/Arma/Pistola/";
        balaPath = "assets/images/Armas/Pistola/";  // Ajusta esto según sea necesario
        break;

    case 2:
        slayerPath = "assets/images/Slayer/Slayer/Arma/Escopeta/";
        balaPath = "assets/images/Armas/Escopeta/";  // Ajusta esto según sea necesario
        break;

    case 3:
        slayerPath = "assets/images/Slayer/Slayer/Arma/Mini/";
        balaPath = "assets/images/Armas/Mini/";  // Ajusta esto según sea necesario
        break;

    case 4:
        slayerPath = "assets/images/Slayer/Slayer/Arma/Fusil/";
        balaPath = "assets/images/Armas/Fusil/";  // Ajusta esto según sea necesario
        break;

    case 5:
        slayerPath = "assets/images/Slayer/Slayer/Arma/BFG/";
        balaPath = "assets/images/Armas/BFG/";  // Ajusta esto según sea necesario
        break;

    case 6:
        slayerPath = "assets/images/Slayer/Slayer/Arma/Plasma/";
        balaPath = "assets/images/Armas/Plasma/";  // Ajusta esto según sea necesario
        break;

    case 7:
        slayerPath = "assets/images/Slayer/Slayer/Arma/God/";
        balaPath = "assets/images/Armas/God/";  // Ajusta esto según sea necesario
        break;

    default:
        slayerPath = "assets/images/Slayer/Slayer/Arma/Pistola/";
        balaPath = "assets/images/Armas/Pistola/"; 
        break;
    }
    
    // Cargar las imágenes del jugador para todas las direcciones
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        // Construir las rutas específicas para cada dirección
        std::string slayerImagePath = constructImagePath(slayerPath, "Slayer", getDirectionString(i));
        std::string balaImagePath = constructImagePath(balaPath, "Bala", getDirectionString(i));

        // Imprimir la ruta antes de cargar la imagen
        printf("Loading image from path: %s\n", slayerImagePath.c_str());

        // Cargar las imágenes del jugador
        surfaces[i][0] = loadSurface(slayerImagePath);
        if (surfaces[i][0] == NULL) {
            printf("Failed to load %s image!\n", getDirectionString(i).c_str());
            success = false;
        }

        // Cargar las imágenes de las balas
        surfaces[i][1] = loadSurface(balaImagePath);
        if (surfaces[i][1] == NULL) {
            printf("Failed to load %s shoot image!\n", getDirectionString(i).c_str());
            success = false;
        }
    }

    return success;
}

std::string SpriteManager::constructImagePath(const std::string& basePath, const std::string& prefix, const std::string& direction) {
    std::filesystem::path imagePath(basePath);
    imagePath /= prefix + direction + ".bmp";
    return imagePath.string();
}

SDL_Surface* SpriteManager::loadSurface(const std::string& path) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    } else {
        printf("Image loaded successfully!\n");
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 177, 64));
    }

    return loadedSurface;
}


void SpriteManager::render(SDL_Surface* screenSurface, int x, int y, bool isShooting, Uint32 shootAnimationStartTime, Uint32 currentTime, int currentDirection) {
    // Lógica para renderizar los sprites en la pantalla
    // Similar a tu lógica en la función main(), pero utilizando las variables miembro de esta clase
    SDL_Rect destinationRect = {x, y, 0, 0};

    if (isShooting) {
        Uint32 elapsedTime = currentTime - shootAnimationStartTime;
        if (elapsedTime >= SHOOT_ANIMATION_DURATION) {
            isShooting = false;
        } else {
            SDL_BlitSurface(surfaces[currentDirection][1], NULL, screenSurface, &destinationRect);
        }
    } else {
        SDL_BlitSurface(surfaces[currentDirection][0], NULL, screenSurface, &destinationRect);
    }
}
