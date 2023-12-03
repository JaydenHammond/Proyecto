// game_lib.hpp

#ifndef GAME_LIB_HPP
#define GAME_LIB_HPP

#include <SDL.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <SDL_timer.h>
#include <string>
#include <SDL_image.h>

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
// Enumeraciones, estructuras, y otras declaraciones necesarias

class Character
{
public:
    Character();
    bool init(const char* upPath, const char* shootPath);
    void handleEvent(SDL_Event& e, bool& isShooting, std::vector<Bullet>& bullets);
    void update(bool& isShooting, std::vector<Bullet>& bullets);
    void render(bool isShooting, std::vector<Bullet>& bullets);

private:
    int centerX;
    int centerY;
    KeyPressSurfaces currentDirection;
    SDL_Surface* surfaces[KEY_PRESS_SURFACE_TOTAL][2];
};

// Otras declaraciones y funciones si es necesario

#endif // GAME_LIB_HPP
