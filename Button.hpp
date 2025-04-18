// Button.hpp
#pragma once
#include <SDL.h>

class Button {
public:
    SDL_Rect rect;
    SDL_Texture* texture;

    Button(int x, int y, int w, int h, SDL_Texture* tex);
    void render(SDL_Renderer* renderer);
    bool isClicked(int x, int y);
};
