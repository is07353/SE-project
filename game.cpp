#include "game.hpp"
#include "chess_piece.hpp"
#include "Board.hpp"
#include "Button.hpp"
#include "stockfish.hpp"
#include <chrono> 
bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Chess Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ); 
					success = false;
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

	startButtonTex = loadTexture("start.png");
	exitButtonTex = loadTexture("exit.png");

	if (startButtonTex == NULL || exitButtonTex == NULL) {
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

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(gTexture);
	SDL_DestroyTexture(introTexture);
	introTexture = NULL;
	SDL_DestroyTexture(startButtonTex);
	SDL_DestroyTexture(exitButtonTex);
	
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
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
// void Game::run( )
// {
// 	showIntroScreen();
// 	Board B1;
// 	bool quit = false;
// 	bool once = true;
// 	SDL_Event e;
// 	bool tpm = false;
// 	showIntroScreen();
// 	{
// 		tpm = true;
// 	}

// 	while( !quit)
// 	{
		
// 		//Handle events on queue
// 		while( SDL_PollEvent( &e ) != 0 )
// 		{
// 			float deltaX = 0;
//     		float deltaY = 0;
// 			//User requests quit
// 			if( e.type == SDL_QUIT )
// 			{
// 				quit = true;
// 			}

// 			  if (e.type == SDL_MOUSEMOTION )
// 				{	
					
					
// 						//cout<<"motion"<<endl;
// 						int xMouse, yMouse;
// 						SDL_GetMouseState(&xMouse,&yMouse);
// 						// deltaX += e.motion.x;
// 						// deltaY += e.motion.y;
// 						//cout<<"deltaX"<<deltaX<<"deltay"<<deltaY<<endl;
// 						B1.mouse_in(xMouse,yMouse);
					
					
// 				}
// 				if(e.type == SDL_MOUSEBUTTONDOWN)
// 				{	
// 					int xMouse, yMouse;
// 					SDL_GetMouseState(&xMouse,&yMouse);
// 					//cout << "clicked " <<xMouse<< endl;
// 					B1.select_piece(xMouse,yMouse);
// 					std::string uci_history =  B1.generate_uci_move_history();
// 					bool status = getCheckStatusFromStockfish(uci_history);
// 					std::cout<<status<<std::endl;
// 					//std::string status = getCheckStatusFromStockfish(B1.generate_uci_move_history());
					

				
// 				}
// 				if (e.type == SDL_KEYDOWN) {
// 					switch (e.key.keysym.sym) {
// 						case SDLK_m:
// 						{
// 							std::string uci_history =  B1.generate_uci_move_history();
// 							std::cout << "uci history: " << uci_history << std::endl;
// 							std::string user_input_move = getBestMoveFromStockfish(uci_history,20);
// 							//std::cout << "Enter your move (e.g. a7a5): ";
// 							//std::cin >> user_input_move;
// 							//cout<<getBestMoveFromStockfish("position startpos moves e2e4 e7e5",10)<<std::endl;
							
// 							B1.apply_uci_move(user_input_move);
// 							B1.print_board_debug(); // Optional debug visual
// 							std::cout << "Aimove: " << user_input_move << std::endl;
// 							bool status = getCheckStatusFromStockfish(uci_history);
// 							std::cout<<status<<std::endl;
// 							break;
// 						}
// 					}
// 				}
// 		}
		
// 		SDL_RenderClear(gRenderer); //removes everything from renderer
// 		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
// 		//***********************draw the objects here********************
// 		B1.run(gRenderer,assets,once);
// 		once = false;

// 		//****************************************************************
//     	SDL_RenderPresent(gRenderer); //displays the updated renderer

// 	    SDL_Delay(2);	//causes sdl engine to delay for specified miliseconds
// 	}
			
// }
#include <chrono>

void Game::run()
{
    showIntroScreen();
    Board B1;
    bool quit = false;
    bool once = true;
    SDL_Event e;

    int turn = 0; // 0 for AI, 1 for Player
    auto turnStart = std::chrono::steady_clock::now();
    const int maxTurnTime = 15; // seconds
	int click = 0;
	int game_type = 1; //0 pvc 1pvp
	int ai_difficulty = 20; //10,15,20 are the options
    while (!quit)
    {
		//pvc loop
		if(game_type == 0)
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
							std::cout << "Click status: " << click << std::endl;
							if(click == 2)
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
						B1.print_board_debug();
						std::cout << "AI move: " << aiMove << std::endl;

						bool status = getCheckStatusFromStockfish(uci_history);
						std::cout << "Check status: " << status << std::endl;

						// Turn completed
						turn = 1;
						turnStart = std::chrono::steady_clock::now(); // reset clock
					}
				}

				// Optional: auto-forfeit or auto-move if time exceeds limit
				auto now = std::chrono::steady_clock::now();
				int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - turnStart).count();
				if (elapsed >= maxTurnTime)
				{
					std::cout << "Time limit reached for turn " << turn << std::endl;

					if (turn == 1)
					{
						// Optional: auto-move for AI
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
	//pvp loop
		if(game_type == 1)
		{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					float deltaX = 0;
					float deltaY = 0;
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
		
					if (e.type == SDL_MOUSEMOTION )
					{	
						
						
							//cout<<"motion"<<endl;
							int xMouse, yMouse;
							SDL_GetMouseState(&xMouse,&yMouse);
							// deltaX += e.motion.x;
							// deltaY += e.motion.y;
							//cout<<"deltaX"<<deltaX<<"deltay"<<deltaY<<endl;
							B1.mouse_in(xMouse,yMouse);
						
						
					}
					if(e.type == SDL_MOUSEBUTTONDOWN)
					{	
						int xMouse, yMouse;
						SDL_GetMouseState(&xMouse,&yMouse);
						//cout << "clicked " <<xMouse<< endl;
						B1.select_piece(xMouse,yMouse);
					
					}
				}
		
				SDL_RenderClear(gRenderer); //removes everything from renderer
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);//Draws background to renderer
				//***********************draw the objects here********************
				B1.run(gRenderer,assets,once);
				once = false;
		
				//****************************************************************
				SDL_RenderPresent(gRenderer); //displays the updated renderer
		
				SDL_Delay(2);
		}
	}
}


void Game::showIntroScreen()
{
    Button startButton(400, 200, 200, 80, startButtonTex);
    Button exitButton(400, 300, 200, 80, exitButtonTex);

    bool introActive = true;
    SDL_Event e;

    while (introActive) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                introActive = false;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (startButton.isClicked(x, y)) {
                    introActive = false; // Start game
                } 
				else if (exitButton.isClicked(x, y)) {
                    SDL_Quit(); // Exit the game
                    exit(0);
                }
				
            }
        }

        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, introTexture, NULL, NULL); // Background
        startButton.render(gRenderer);
        exitButton.render(gRenderer);
        SDL_RenderPresent(gRenderer);
    }
}
