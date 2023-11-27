#include <SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_SHOOT,
    KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

int main(int argc, char* args[])
{
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            bool isShooting = false;  // Variable para rastrear si se está disparando
            bool quit = false;
            SDL_Event e;

            int centerX = SCREEN_WIDTH / 2;
            int centerY = SCREEN_HEIGHT / 2;

            const int MOVEMENT_SPEED = 5;

            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP]; // Inicializar con el bmp de movimiento hacia arriba

            // Aplicar la imagen en las coordenadas iniciales del centro de la pantalla
            SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 187, 79, 55)); // Fondo blanco
            SDL_Rect destinationRect = {centerX, centerY, 0, 0};
            SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &destinationRect);
            SDL_UpdateWindowSurface(gWindow);

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            centerY -= MOVEMENT_SPEED;
                            break;

                        case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            centerY += MOVEMENT_SPEED;
                            break;

                        case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            centerX -= MOVEMENT_SPEED;
                            break;

                        case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            centerX += MOVEMENT_SPEED;
                            break;

                        case SDLK_SPACE:  // Tecla de espacio para cambiar entre disparo y estado normal
                            isShooting = true;
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_SHOOT];
                            break;

                        default:
                            break;
                        }
                    }
                    else if (e.type == SDL_KEYUP)
                    {
                        if (e.key.keysym.sym == SDLK_SPACE)
                        {
                            isShooting = false;
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP]; // Cambiar de vuelta al estado normal
                        }
                    }
                }

                SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 187, 79, 55));
                SDL_Rect destinationRect = {centerX, centerY, 0, 0};
                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, &destinationRect);
                SDL_UpdateWindowSurface(gWindow);
            }

            close();
            return 0;
        }
    }
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

bool loadMedia()
{
    bool success = true;

    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("assets/images/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("assets/images/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("assets/images/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("assets/images/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Failed to load right image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_SHOOT] = loadSurface("assets/images/shoot.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_SHOOT] == NULL)
    {
        printf("Failed to load shoot image!\n");
        success = false;
    }

    return success;
}

void close()
{
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
    }

    return loadedSurface;
}
