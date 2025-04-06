#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class king_black : public chess_piece// Class definition for the black king inheriting from the chess_piece class.
{
    private:
    Unit Black_King = {{1263, 89, 64, 154},{440, 540, 50, 50}};// Represents the black king's properties, including source and mover rectangles.
    bool enabled = true;// Indicates whether the piece is enabled or disabled
    public:
    king_black(); // Default constructor to cater ro3
    // Functions to override from the base class (chess_piece).
    virtual void setFirstMove(bool first);
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) override;
    virtual void move(int x,int y,int selected_x,int selected_y) override;
    virtual string getType();
    virtual int getPlacedX();
    virtual int getPlacedY();
    virtual bool is_black();
    virtual bool get_enabled();
    virtual void set_enabled(bool enabled_in);
    virtual ~king_black(); //Virtual Destructor
    //Rule of three
    king_black(const king_black& obj) = delete;
    king_black& operator = (const king_black& obj) = delete;
};