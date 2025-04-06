#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class king_white: public chess_piece
{
    private:
    Unit White_King = {{1229, 1116, 56, 135},{520, 10, 50, 50}};// Represents the white king's source and mover rectangles
    bool enabled = true;// Indicates whether the white king is enabled
    public:
    king_white();
    virtual void setFirstMove(bool first);// Sets if it's the white king's first move
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) override;// Initializes the white king's position on the chessboard
    virtual void move(int x,int y,int selected_x,int selected_y) override;// Moves the white king on the chessboard based on selected coordinates
    virtual string getType();// Returns the type of chess piece (in this case, "King_White")
    virtual int getPlacedX();// Gets the X-coordinate where the white king is placed on the chessboard
    virtual int getPlacedY();// Gets the Y-coordinate where the white king is placed on the chessboard
    virtual bool is_black();// Checks if the piece is black (for white king, it returns false)
    virtual bool get_enabled();// Gets whether the white king is enabled or not
    virtual void set_enabled(bool enabled_in);// Sets whether the white king is enabled or not
    virtual ~king_white();//Virtual Destructor
    //Rule of three
    king_white(const king_white& obj) = delete;
    king_white& operator = (const king_white& obj) = delete;
};