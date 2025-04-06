#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class rook_black : public chess_piece// Defines the black rook class inheriting from chess_piece
{
    private:
    Unit Black_rook = {{ 175, 120, 68, 111}, {200, 540, 50, 50}};// Represents the black rook's dimensions and position on the board
    bool once = false; // Flags if the rook has moved before
    bool enabled = true;// Indicates if the rook is enabled
    public:
    // Functions that override the base class methods
    rook_black(); //Default constructor to cater ro3
    virtual void setFirstMove(bool first);
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) override;// Initializes the rook's position on the board
    virtual void move(int x,int y,int selected_x,int selected_y) override;
    virtual string getType();
    virtual int getPlacedX();
    virtual int getPlacedY();
    virtual bool is_black();
    virtual bool get_enabled();
    virtual void set_enabled(bool enabled_in);
    virtual ~rook_black(); //Virtual Destructor
    //Rule of three
    rook_black(const rook_black& obj) = delete;
    rook_black& operator = (const rook_black& obj) = delete; 
};