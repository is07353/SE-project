#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class knight_white: public chess_piece
{
    private:
    Unit White_Knight = {{886, 1122, 90, 119}, {280, 10, 50, 50}};// Represents the white knight's source and mover rectangles
    bool once=false;// Tracks if the knight has moved before.
    bool enabled =true;//// Indicates if the knight is currently enabled.
    public:
    // Function declarations
    knight_white(); // Default constructor to cater ro3
    virtual void setFirstMove(bool first);
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets, int num) override;
    virtual void move(int x,int y,int selected_x,int selected_y) override;
    virtual string getType();
    virtual int getPlacedX();
    virtual int getPlacedY();
    virtual bool is_black();
    virtual bool get_enabled();
    virtual void set_enabled(bool enabled_in);
    virtual ~knight_white(); //Virtual Destructor
    //Rule of three
    knight_white(const knight_white& obj) = delete;
    knight_white& operator = (const knight_white& obj) = delete;
};