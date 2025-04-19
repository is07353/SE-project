#include "game.hpp"
int main(int argc, char *argv[]){
    Game game;// Instantiates the Game class
    srand(time(NULL));// Seeds the random number generator
    if( !game.init() ){// Checks if initialization of the game fails
		printf( "Failed to initialize!\n" );
        return 0;
	}
		//Load media
    if( !game.loadMedia() ){
        printf( "Failed to load media!\n" );
        return 0;
    }

    game.run();// Starts the game loop and runs the game
    game.close();// Closes and performs cleanup for the game

    return 0;
}