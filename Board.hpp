#include<iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "chess_piece.hpp"
#include "GameChess.hpp"// Include all other chess piece headers
#include "white_pawn.hpp"
#include "rook_white.hpp"
#include "knight_white.hpp"
#include "Bishop_white.hpp"
#include "king_white.hpp"
#include "queen_white.hpp"
#include "knight_black.hpp"
#include "king_black.hpp"
#include "black_pawn.hpp"
#include "rook_black.hpp"
#include "queen_black.hpp"
#include "Bishop_black.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
// Inherits from Gamechess
// Has access to Gamechess functionalities 
// Includes additional functionalities specific to managing the chessboard and game logic
class Board : private Gamechess
{   private:
    chess_piece* board[8][8];//an array of 8 by 8 is created for the board
    chess_piece* temppiece;
    std::vector<std::string> move_history;


    public:
    // Constructor and member functions
    Board();// Constructor for initializing the board
    
    void run(SDL_Renderer* gRenderer,SDL_Texture* assets, bool first_time);    // Function to run the game logic and manage piece initialization

    std::string generate_uci_move_history() const;
    std::string get_uci_move(int from_x, int from_y, int to_x, int to_y) const;
    void apply_uci_move(const std::string& uci_move);
    void print_board_debug() const;


    bool black_queen_onboard();// Check if the black queen is on the board
    bool white_queen_onboard();// Check if the white queen is on the board
    void checknate(SDL_Renderer* renderer);// Check if a checkmate has occurred
    void disableall();// Disable all pieces on the board
    void select_piece(int x, int y);// Select a piece to move or perform an action
    void next_player(int x, int y);// Switch to the next player's turn
    void mouse_in(int x, int y);// Handle mouse input for interactions with the board
    void showWinScreen(SDL_Renderer* renderer, const string& winnerText);
    ~Board(); // Destructor for board
    //For rule of three
    Board(const Board& obj) = delete;
    Board& operator = (const Board& obj) = delete;
};