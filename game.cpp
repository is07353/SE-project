#include "game.hpp"
#include "chess_piece.hpp"
#include "Board.hpp"
#include "Button.hpp"
#include "stockfish.hpp"
#include <chrono>
#include <SDL_ttf.h>
SDL_Renderer* gRenderer = NULL;
// global variables
int game_type = 1; // 0 = PVC, 1 = PVP
int ai_difficulty = 10; // 10 = EASY, 15 = MEDIUM, 20 = HARD

// countdown timer support for PVP
int countdown = 20; // seconds
std::chrono::steady_clock::time_point countdownStart;
bool startCountdown = false;

TTF_Font* font = nullptr;

bool Game::init()
{
    bool success = true;
	TTF_Init();
	if (TTF_Init() == -1) {
		std::cout << "TTF_Init failed: " << TTF_GetError() << std::endl;
	}

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            printf("Warning: Linear texture filtering not enabled!\n");

        gWindow = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!gWindow)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (!gRenderer)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                if (TTF_Init() == -1)
                {
                    printf("TTF could not initialize! TTF Error: %s\n", TTF_GetError());
                    success = false;
                }
                else
                {
                    font = TTF_OpenFont("english.ttf", 24);
                    if (!font)
                    {
                        printf("Failed to load font! TTF Error: %s\n", TTF_GetError());
                        success = false;
                    }
                }
            }
        }
    }
    return success;
}
bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;

	introTexture = loadTexture("intro.png");
	if (introTexture == NULL) {
		printf("Failed to load intro screen!\n");
		success = false;
	}

	pvpButtonTex = loadTexture("pvp.png");
	pvcButtonTex = loadTexture("pvc.png");
	exitButtonTex = loadTexture("exit.png");
	easyButtonTex = loadTexture("easy.png");
	mediumButtonTex = loadTexture("medium.png");
	hardButtonTex = loadTexture("hard.png");
	backButtonTex = loadTexture("back.png");
	backgroundTex = loadTexture("bkgd.png");
	textTex = loadTexture("choose.png");


	if (pvpButtonTex == NULL || pvcButtonTex == NULL || easyButtonTex == NULL || mediumButtonTex == NULL || hardButtonTex == NULL || exitButtonTex == NULL) {
		printf("Failed to load button textures!\n");
		success = false;
	}

	
	assets = loadTexture("assets.png"); // replace with piece image
    gTexture = loadTexture("hu.png"); // chess board
	if(assets==NULL || gTexture==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
 }

void Game::showIntroScreen()
{
    SDL_Event e;
    Button pvpButton(400, 200, 200, 80, pvpButtonTex);
    Button pvcButton(400, 220, 200, 250, pvcButtonTex);
    Button exitButton(400, 400, 200, 80, exitButtonTex);

    while (true)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) return;
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (pvpButton.isClicked(x, y)) {
                    game_type = 1;
                    return;
                }
                if (pvcButton.isClicked(x, y)) {
                    game_type = 0;
                    showDifficultyScreen();
                    return;
                }
                if (exitButton.isClicked(x, y)) return;
            }
        }
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, introTexture, NULL, NULL);
        pvpButton.render(gRenderer);
        pvcButton.render(gRenderer);
        exitButton.render(gRenderer);
        SDL_RenderPresent(gRenderer);
    }
}

void Game::showDifficultyScreen()
{
    SDL_Event e;

    // create buttons
    Button easy(400, 100, 200, 250, easyButtonTex);
    Button medium(400, 200, 200, 250, mediumButtonTex);
    Button hard(400, 300, 200, 250, hardButtonTex);
    Button back(20, 10, 200, 250, backButtonTex); // position and size of back button

    // title setup
    TTF_Font* font = TTF_OpenFont("english.ttf", 28);
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Choose Bot Difficulty", textColor);
    SDL_Texture* textTex = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    int textW = textSurface->w;
    int textH = textSurface->h;
    SDL_FreeSurface(textSurface);
    SDL_Rect textRect = { 350, 20, textW, textH };  // center aligned

    while (true)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) return;
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (easy.isClicked(x, y)) { ai_difficulty = 10; goto cleanup; }
                if (medium.isClicked(x, y)) { ai_difficulty = 15; goto cleanup; }
                if (hard.isClicked(x, y)) { ai_difficulty = 20; goto cleanup; }
                if (back.isClicked(x, y)) { showIntroScreen(); goto cleanup; }
            }
        }

        SDL_RenderClear(gRenderer);

        // render background
        SDL_RenderCopy(gRenderer, backgroundTex, NULL, NULL);

        // render title
        SDL_RenderCopy(gRenderer, textTex, NULL, &textRect);

        // render buttons
        easy.render(gRenderer);
        medium.render(gRenderer);
        hard.render(gRenderer);
        back.render(gRenderer);

        SDL_RenderPresent(gRenderer);
    }

cleanup:
    SDL_DestroyTexture(textTex);
    TTF_CloseFont(font);
}

// void renderCountdown(int secondsLeft)
// {
//     SDL_Color textColor = { 255, 0, 0, 255 };
//     std::string timerText = "Time: " + std::to_string(secondsLeft);
//     SDL_Surface* textSurface = TTF_RenderText_Solid(font, timerText.c_str(), textColor);
//     if (!textSurface) return;
//     SDL_Texture* counter = SDL_CreateTextureFromSurface(gRenderer, textSurface);
//     SDL_Rect renderQuad = { 600, 10, textSurface->w, textSurface->h };
//     SDL_RenderCopy(gRenderer, counter, NULL, &renderQuad);
//     SDL_FreeSurface(textSurface);
//     SDL_DestroyTexture(counter);
// }

void renderCountdown(int secondsLeft) {
    if (secondsLeft <= 0) return;

    TTF_Font* font = TTF_OpenFont("english.ttf", 48); 
    if (!font) {
        std::cout << "Font not found: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color color = {255, 255, 255}; // red text
    std::string text = std::to_string(secondsLeft);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);

    SDL_Rect dstRect = {55, 500, surface->w, surface->h}; // adjust pos
    SDL_RenderCopy(gRenderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void Game::run()
{
    showIntroScreen();
    Board B1;
    bool quit = false;
    bool once = true;
    SDL_Event e;
    int turn = 0;
    auto turnStart = std::chrono::steady_clock::now();
	countdownStart = std::chrono::steady_clock::now();
    int click = 0;

    while (!quit)
    {
        if (game_type == 0) // PVC
        {
            {
				while (SDL_PollEvent(&e) != 0)
				{
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
	
						// Player's turn
						if (turn == 1)
						{
							//std::cout << "player loop " << std::endl;
							if (e.type == SDL_MOUSEMOTION)
							{
								int xMouse, yMouse;
								SDL_GetMouseState(&xMouse, &yMouse);
								B1.mouse_in(xMouse, yMouse);
							}
							if (e.type == SDL_MOUSEBUTTONDOWN)
							{
								click++;
								int xMouse, yMouse;
								SDL_GetMouseState(&xMouse, &yMouse);
								B1.select_piece(xMouse, yMouse);
								std::string uci_history = B1.generate_uci_move_history();
								bool status = getCheckStatusFromStockfish(uci_history);
								std::cout << "Check status: " << status << std::endl;
								// Turn completed
								//if(status==1){B1.showWinScreen(gRenderer, "white Wins!");}
                                    
								if(click == 2 )
								{
								turn = 0;
								turnStart = std::chrono::steady_clock::now(); // reset clock
								click = 0;
								}
							}
						}
	
						// AI’s turn
						if (turn == 0 )
						{
							std::string uci_history = B1.generate_uci_move_history();
							std::cout << "UCI history: " << uci_history << std::endl;
							std::string aiMove = getBestMoveFromStockfish(uci_history, ai_difficulty);
							B1.apply_uci_move(aiMove);
							//B1.print_board_debug();
							std::cout << "AI move: " << aiMove << std::endl;
	
							bool status = getCheckStatusFromStockfish(uci_history);
							std::cout << "Check status: " << status << std::endl;
                            //if(status==1){B1.showWinScreen(gRenderer, "white Wins!");}
                            
							// Turn completed
							turn = 1;
							turnStart = std::chrono::steady_clock::now(); // reset clock
						}
					}
	
					// Optional: auto-forfeit or auto-move if time exceeds limit
					auto now = std::chrono::steady_clock::now();
					int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - turnStart).count();
                    int secondsLeft = countdown - elapsed;
                    if (secondsLeft < 0) secondsLeft = 0;
                    renderCountdown(elapsed);
                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(10);
					if (elapsed >= maxTurnTime)
					{
						std::cout << "Time limit reached for turn " << turn << std::endl;
	
						if (turn == 1)
						{
							// auto-move for AI
							std::string uci_history = B1.generate_uci_move_history();
							std::string aiMove = getBestMoveFromStockfish(uci_history, ai_difficulty);
							B1.apply_uci_move(aiMove);
							std::cout << "AI auto-move: " << aiMove << std::endl;
							turn = 0;
							click = 0;
						}
						else
						{
							// Optional: end player’s turn or auto-skip
							std::cout << "Player took too long, skipping turn." << std::endl;
							turn = 0;
						}
	
						turnStart = now;
					}
	
					SDL_RenderClear(gRenderer);
					SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
					B1.run(gRenderer, assets, once);
					once = false;
					SDL_RenderPresent(gRenderer);
					SDL_Delay(2);
			}
        }
        else if (game_type == 1) // PVP
        {
            while (SDL_PollEvent(&e))
            {
				
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
				if (e.type == SDL_MOUSEMOTION )
				{	
					//cout<<"motion"<<endl;
					int xMouse, yMouse;
					SDL_GetMouseState(&xMouse,&yMouse);
					B1.mouse_in(xMouse,yMouse);
				}
				
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int xMouse, yMouse;
                    SDL_GetMouseState(&xMouse, &yMouse);
                    B1.select_piece(xMouse, yMouse);
                    click++;
					
                    if (click == 2)
                    {
                        turn = 1 - turn; // switch turn
                        countdownStart = std::chrono::steady_clock::now();
                        click = 0;
                    }
                }
            }

            
            SDL_RenderClear(gRenderer);
            SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
            B1.run(gRenderer, assets, once);
            once = false;
			
			auto now = std::chrono::steady_clock::now();
			int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - countdownStart).count();
			int secondsLeft = countdown - elapsed;
			if (secondsLeft < 0) secondsLeft = 0;
			renderCountdown(secondsLeft);
			
			SDL_RenderPresent(gRenderer);
			
            SDL_Delay(10);
        }
    }
}

void Game::close()
{
    SDL_DestroyTexture(assets);
    SDL_DestroyTexture(gTexture);
    SDL_DestroyTexture(introTexture);
    SDL_DestroyTexture(pvpButtonTex);
	SDL_DestroyTexture(pvcButtonTex);
	SDL_DestroyTexture(easyButtonTex);
	SDL_DestroyTexture(mediumButtonTex);
	SDL_DestroyTexture(hardButtonTex);
    SDL_DestroyTexture(exitButtonTex);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}