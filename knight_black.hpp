#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class knight_black : public chess_piece
{
    private:
    Unit Black_Knight = {{ 880, 119, 94, 125}, {280, 540, 50, 50}};// Represents the black knight's source and mover rectangles
    bool once=false;// Tracks if the knight has moved before.
    bool enabled=true;// Indicates if the knight is currently enabled.
    public:
    knight_black();//Default constructor to cater ro3
    // Function declarations
    virtual void setFirstMove(bool first);
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets, int num) override;
    virtual void move(int x,int y,int selected_x,int selected_y) override;
    virtual string getType();
    virtual int getPlacedX();
    virtual int getPlacedY();
    virtual bool is_black();
    virtual bool get_enabled();
    virtual void set_enabled(bool enabled_in);
    virtual ~knight_black(); //Virtual Destructor
    //Rule of three
    knight_black(const knight_black& obj) = delete;
    knight_black& operator = (const knight_black& obj) = delete;
};