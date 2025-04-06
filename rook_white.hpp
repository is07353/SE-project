#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class rook_white:public chess_piece// Defines the white rook class inheriting from chess_piece
{
    private:
    Unit White_rook = {{263, 1162, 60, 98},{200, 10, 50, 50}};// Represents the white rook's dimensions and position on the board
    bool once = false;// Flags if the rook has moved before
    bool enabled = true;// Indicates if the rook is enabled
    public:
    
    rook_white(); // Default constructor to cater ro3
    // Functions that override the base class methods
    virtual void setFirstMove(bool first);
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) override;
    virtual void move(int x,int y,int selected_x,int selected_y) override;
    virtual string getType();
    virtual int getPlacedX();
    virtual int getPlacedY();
    virtual bool is_black();
    virtual bool get_enabled();
    virtual void set_enabled(bool enabled_in);
    virtual ~rook_white(); //Virtual Destructor
    //Rule of three
    rook_white(const rook_white& obj) = delete;
    rook_white& operator = (const rook_white& obj) = delete;
};