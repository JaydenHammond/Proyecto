// game_lib.cpp

#include "game_lib.hpp"

SDL_Surface* loadSurface(std::string path)
{
    
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
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

Character::Character()
    : centerX(SCREEN_WIDTH / 2), centerY(SCREEN_HEIGHT / 2), currentDirection(KEY_PRESS_SURFACE_UP)
{
}

bool Character::init(const char* upPath, const char* shootPath)
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

void Character::handleEvent(SDL_Event& e, bool& isShooting, std::vector<Bullet>& bullets)
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
                            currentDirection = KEY_PRESS_SURFACE_UP;
                            break;

                        case SDLK_DOWN:
                            currentDirection = KEY_PRESS_SURFACE_DOWN;
                            break;

                        case SDLK_LEFT:
                            currentDirection = KEY_PRESS_SURFACE_LEFT;
                            break;

                        case SDLK_RIGHT:
                            currentDirection = KEY_PRESS_SURFACE_RIGHT;
                            break;
                        case SDLK_SPACE:
                            if (!isShooting)
                            {
                                isShooting = true;
                                shootAnimationStartTime = currentTime;

                                // Crear una nueva bala y agregarla al vector
                                Bullet bullet;
                                bullet.x = centerX;
                                bullet.y = centerY;
                                bullet.direction = currentDirection;
                                bullet.surface = surfaces[currentDirection][1];
                                bullets.push_back(bullet);
                            }
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
                        }
                    }
}

void Character::update(bool& isShooting, std::vector<Bullet>& bullets)
{
    const int MOVEMENT_SPEED = 4;

    switch (currentDirection)
    {
    case KEY_PRESS_SURFACE_UP:
        if (centerY - MOVEMENT_SPEED >= 0)  // Verifica límite superior
            centerY -= MOVEMENT_SPEED;
        break;

    case KEY_PRESS_SURFACE_DOWN:
        if (centerY + MOVEMENT_SPEED + surfaces[currentDirection][0]->h <= SCREEN_HEIGHT)  // Verifica límite inferior
            centerY += MOVEMENT_SPEED;
        break;

    case KEY_PRESS_SURFACE_LEFT:
        if (centerX - MOVEMENT_SPEED >= 0)  // Verifica límite izquierdo
            centerX -= MOVEMENT_SPEED;
        break;

    case KEY_PRESS_SURFACE_RIGHT:
        if (centerX + MOVEMENT_SPEED + surfaces[currentDirection][0]->w <= SCREEN_WIDTH)  // Verifica límite derecho
            centerX += MOVEMENT_SPEED;
        break;

    default:
        break;
    }

    // Actualizar la posición de las balas
                for (auto& bullet : bullets)
                {
                    switch (bullet.direction)
                    {
                    case KEY_PRESS_SURFACE_UP:
                        bullet.y -= BULLET_SPEED;
                        break;

                    case KEY_PRESS_SURFACE_DOWN:
                        bullet.y += BULLET_SPEED;
                        break;

                    case KEY_PRESS_SURFACE_LEFT:
                        bullet.x -= BULLET_SPEED;
                        break;

                    case KEY_PRESS_SURFACE_RIGHT:
                        bullet.x += BULLET_SPEED;
                        break;

                    default:
                        break;
                    }
                }
}

void Character::render(bool isShooting, std::vector<Bullet>& bullets)
{
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 187, 79, 55));

    // Renderizar al jugador
    SDL_Rect playerRect = {centerX, centerY, 0, 0};
    SDL_BlitSurface(surfaces[currentDirection][0], NULL, gScreenSurface, &playerRect);

    // Renderizar las balas
    for (const auto& bullet : bullets)
    {
        SDL_Rect bulletRect = {bullet.x, bullet.y, 0, 0};
        SDL_BlitSurface(bullet.surface, NULL, gScreenSurface, &bulletRect);
    }

    // Actualizar la ventana
    SDL_UpdateWindowSurface(gWindow);
}

// Otras implementaciones si es necesario
