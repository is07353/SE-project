// Button.cpp
#include "Button.hpp"

Button::Button(int x, int y, int w, int h, SDL_Texture* tex) {
    rect = {x, y, w, h};
    texture = tex;
}

void Button::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

bool Button::isClicked(int x, int y) {
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}
