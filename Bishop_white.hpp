#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class Bishop_white: public chess_piece
{
    private:
    Unit White_Bishop = {{554, 1137, 60, 111},{360, 10, 50, 50}};//the unit for the wgite bishop
    bool once = false;
    bool enabled = true;
    public:
    Bishop_white();//Default constructor to cater ro3
    virtual void setFirstMove(bool first);
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) override;
    virtual void move(int x,int y,int selected_x,int selected_y) override;
    virtual string getType();
    virtual int getPlacedX();
    virtual int getPlacedY();
    virtual bool is_black();
    virtual bool get_enabled();
    virtual void set_enabled(bool enabled_in);
    virtual ~Bishop_white(); // Virtual destructor
    //Rule of three
    Bishop_white(const Bishop_white& obj) = delete;
    Bishop_white& operator = (const Bishop_white& obj) = delete;
};