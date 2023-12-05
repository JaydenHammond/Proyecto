#include <SDL.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <SDL_timer.h>
#include <string>
#include <SDL_image.h>

class Game
{
public:
    Game();
    ~Game();
    bool init();
    bool loadMedia();
    void run();
    bool handleEvents();
    void update();
    void render();
    void cleanUp();

private:
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 600;
    const int BULLET_SPEED = 8;

    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_SHOOT_UP,
        KEY_PRESS_SURFACE_SHOOT_DOWN,
        KEY_PRESS_SURFACE_SHOOT_LEFT,
        KEY_PRESS_SURFACE_SHOOT_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };

    struct Player
    {
        int centerX;
        int centerY;
        KeyPressSurfaces currentDirection;
        SDL_Surface* surfaces[KEY_PRESS_SURFACE_TOTAL][2];
    };

    struct Bullet
    {
        int x;
        int y;
        KeyPressSurfaces direction;
        SDL_Surface* surface;
    };

    bool isShooting;
    bool quit;
    SDL_Window* gWindow;
    SDL_Surface* gScreenSurface;
    Player player;
    std::vector<Bullet> bullets;

    Uint32 shootAnimationStartTime;
    const Uint32 SHOOT_ANIMATION_DURATION = 500;

    Uint32 lastUpdateTime;

    
    SDL_Surface* loadSurface(std::string path);
};

Game::Game()
    : isShooting(false),
      quit(false),
      gWindow(nullptr),
      gScreenSurface(nullptr),
      shootAnimationStartTime(0),
      lastUpdateTime(0)
{
}

Game::~Game()
{
}

bool Game::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("DOOM PITERO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return true;
}

bool Game::loadMedia()
{
    // Load media here
    // ...

    return true;
}

bool Game::handleEvents()
{
    SDL_Event e;

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
                player.currentDirection = KEY_PRESS_SURFACE_UP;
                break;

            case SDLK_DOWN:
                player.currentDirection = KEY_PRESS_SURFACE_DOWN;
                break;

            case SDLK_LEFT:
                player.currentDirection = KEY_PRESS_SURFACE_LEFT;
                break;

            case SDLK_RIGHT:
                player.currentDirection = KEY_PRESS_SURFACE_RIGHT;
                break;

            case SDLK_SPACE:
                if (!isShooting)
                {
                    isShooting = true;
                    shootAnimationStartTime = SDL_GetTicks();

                    // Create a new bullet and add it to the vector
                    Bullet bullet;
                    bullet.x = player.centerX;
                    bullet.y = player.centerY;
                    bullet.direction = player.currentDirection;
                    bullet.surface = player.surfaces[player.currentDirection][1];
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

    return true;
}

void Game::update()
{
    const int MOVEMENT_SPEED = 4;

    switch (player.currentDirection)
    {
    case KEY_PRESS_SURFACE_UP:
        if (player.centerY - MOVEMENT_SPEED >= 0)
            player.centerY -= MOVEMENT_SPEED;
        break;

    case KEY_PRESS_SURFACE_DOWN:
        if (player.centerY + MOVEMENT_SPEED + player.surfaces[player.currentDirection][0]->h <= SCREEN_HEIGHT)
            player.centerY += MOVEMENT_SPEED;
        break;

    case KEY_PRESS_SURFACE_LEFT:
        if (player.centerX - MOVEMENT_SPEED >= 0)
            player.centerX -= MOVEMENT_SPEED;
        break;

    case KEY_PRESS_SURFACE_RIGHT:
        if (player.centerX + MOVEMENT_SPEED + player.surfaces[player.currentDirection][0]->w <= SCREEN_WIDTH)
            player.centerX += MOVEMENT_SPEED;
        break;

    default:
        break;
    }

    Uint32 currentTime = SDL_GetTicks();

    if (isShooting)
    {
        Uint32 elapsedTime = currentTime - shootAnimationStartTime;
        if (elapsedTime >= SHOOT_ANIMATION_DURATION)
        {
            isShooting = false;
        }
    }

    // Update bullet positions
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

    // Remove bullets outside the screen
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
                       [this](const Bullet& bullet) {
                           return bullet.x < 0 || bullet.x >= SCREEN_WIDTH || bullet.y < 0 || bullet.y >= SCREEN_HEIGHT;
                       }),
        bullets.end());

    lastUpdateTime = currentTime;
}

void Game::render()
{
    // Render here

    // Clear the screen
    SDL_FillRect(gScreenSurface, NULL, 0);

    // Render player
    SDL_Rect playerRect = {player.centerX, player.centerY, 0, 0};
    SDL_BlitSurface(player.surfaces[player.currentDirection][0], NULL, gScreenSurface, &playerRect);

    // Render bullets
    for (const auto& bullet : bullets)
    {
        SDL_Rect bulletRect = {bullet.x, bullet.y, 0, 0};
        SDL_BlitSurface(bullet.surface, NULL, gScreenSurface, &bulletRect);
    }

    // Update the window
    SDL_UpdateWindowSurface(gWindow);

    // Delay to control frame rate
    SDL_Delay(16);
}

void Game::cleanUp()
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

SDL_Surface* Game::loadSurface(std::string path)
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

int main(int argc, char* args[])
{
    Game game;

    if (!game.init())
    {
        printf("Failed to initialize!\n");
        return 1;
    }

    if (!game.loadMedia())
    {
        printf("Failed to load media!\n");
        return 2;
    }

    game.run();

    return 0;
}
