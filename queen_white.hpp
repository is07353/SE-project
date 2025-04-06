#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class queen_white: public chess_piece
{
    private:
    Unit White_Queen = {{1518, 1132, 60, 122},{440, 10, 50, 50}};// Position and size information for rendering
    bool enabled = true;// State to track if the piece is enabled
    public:
    queen_white();//def const
    queen_white(chess_piece* other);// Constructor taking another chess piece as an argument
    // Virtual functions from the base class
    virtual void setFirstMove(bool first);
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) override;
    virtual void move(int x,int y,int selected_x,int selected_y) override;
    virtual string getType();
    virtual int getPlacedX();
    virtual int getPlacedY();
    virtual bool is_black();
    virtual bool get_enabled();
    virtual void set_enabled(bool enabled_in);
    virtual ~queen_white(); //Virtual Destructor
    //Rule of three
    queen_white(const queen_white& obj) = delete;
    queen_white& operator = (const queen_white& obj) = delete;
};