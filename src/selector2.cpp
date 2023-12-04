#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int IMAGE_SIZE = 64;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool init();
SDL_Texture* loadTexture(const std::string& path);
void close();

int main(int argc, char* args[])
{
    if (!init())
    {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    std::vector<SDL_Texture*> weaponTextures;

    // Cargar texturas de armas
    for (int i = 1; i <= 7; ++i)
    {
        std::string imagePath = "../assets/images/weapons/weapon" + std::to_string(i) + ".png";
        SDL_Texture* texture = loadTexture(imagePath);
        if (texture)
        {
            weaponTextures.push_back(texture);
        }
        else
        {
            std::cerr << "Failed to load texture for weapon " << i << std::endl;
        }
    }

    bool quit = false;
    SDL_Event e;

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
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
        }

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);  // Color blanco
        SDL_RenderClear(gRenderer);

        // Dibujar las texturas de las armas
        int x = 0;
        for (const auto& texture : weaponTextures)
        {
            SDL_Rect destinationRect = {x, 0, IMAGE_SIZE, IMAGE_SIZE};
            SDL_RenderCopy(gRenderer, texture, nullptr, &destinationRect);
            x += IMAGE_SIZE;
        }

        // Actualizar la ventana
        SDL_RenderPresent(gRenderer);
    }

    close();
    return 0;
}

// Resto del código (init, loadTexture, close) permanece sin cambios



bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Weapon Selector", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);  // Color blanco

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}




SDL_Texture* loadTexture(const std::string& path)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == nullptr)
        {
            std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            std::cout << "Successfully loaded texture from " << path << std::endl;
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}


std::vector<SDL_Texture*> weaponTextures;

void close()
{
    for (auto& texture : weaponTextures)
    {
        SDL_DestroyTexture(texture);
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    IMG_Quit();
    SDL_Quit();
}
