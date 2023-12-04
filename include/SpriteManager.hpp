// SpriteManager.h
#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <SDL.h>
#include <string>

class SpriteManager {
public:
    SpriteManager();
    ~SpriteManager();

    bool loadMedia(int arma);
    void render(SDL_Surface* screenSurface, int x, int y, bool isShooting, Uint32 shootAnimationStartTime, Uint32 currentTime, int currentDirection);

private:
    SDL_Surface* surfaces[KEY_PRESS_SURFACE_TOTAL][2];
    std::string slayerPath;
    std::string balaPath;
};

#endif
