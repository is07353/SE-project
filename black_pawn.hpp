#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class Pawn_black : public chess_piece
{
    private:
    Unit Black_Pawn = {{910, 450, 63, 104},{200, 460, 50, 50}};// Represents the dimensions and coordinates of the black pawn
    // Flags to track if it's the pawn's first move and if it's enabled
    bool once = false;
    bool first_move = false;
    bool enabled = true;
    public:
    Pawn_black(); // Default constructor to cater ro3
    // Overridden functions from the base class
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) override;
    virtual void move(int x,int y,int selected_x,int selected_y) override;
    virtual void setFirstMove(bool first);
    virtual string getType();
    virtual int getPlacedX();
    virtual int getPlacedY();
    virtual bool is_black();
    virtual bool get_enabled();
    virtual void set_enabled(bool enabled_in);
    virtual ~Pawn_black();//  Virtual destructor
    //Rule of three
    Pawn_black(const Pawn_black& obj) = delete;
    Pawn_black& operator = (const Pawn_black& obj) = delete;
};