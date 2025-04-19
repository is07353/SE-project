#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <chrono>

extern SDL_Renderer* gRenderer;

#pragma once
class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 600;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    // SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    
    SDL_Texture* pvpButtonTex;
    SDL_Texture* pvcButtonTex;
    SDL_Texture* easyButtonTex;
    SDL_Texture* mediumButtonTex;
    SDL_Texture* hardButtonTex;
    SDL_Texture* exitButtonTex;

    //difficulty screen bkgd
    SDL_Texture* backgroundTex;
    SDL_Texture* backButtonTex;
    SDL_Texture* textTex;

    SDL_Texture* introTexture;
    //global reference to png image sheets
    SDL_Texture* assets=NULL;

private:
    int timePlayer1;  // Time remaining for Player 1
    int timePlayer2;  // Time remaining for Player 2
    std::chrono::steady_clock::time_point turnStart;  // Starting time for the current turn
    const int maxTurnTime = 15;  // Max time per turn in seconds
    int timeLeftPlayer1 = 300; // 5 minutes
    int timeLeftPlayer2 = 300; // 5 minutes
    Uint32 lastTick = 0;
    bool isPlayer1Turn = true;
    TTF_Font* font;

public:
    int game_type;
    int difficulty;
    void renderTimers(SDL_Renderer* gRenderer);
    std::string formatTime(int totalMSeconds);
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();
    void showIntroScreen();
    void showDifficultyScreen();
};

