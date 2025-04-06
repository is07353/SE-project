#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once// Header guard to prevent multiple inclusions of the same file during compilation.
using namespace std;
class Bishop_black : public chess_piece
{
    private:
    Unit Black_Bishop = {{ 535,114,68,127},{360, 540, 50, 50}};
    bool once = false;//A boolean flag to manage initialization.
    bool enabled = true;//A boolean flag to determine if the piece is enabled.
    public:
    //These functions are declared as virtual to potentially override the base class (chess_piece) functions.
    Bishop_black(); //Default constructor to cater ro3
    virtual void setFirstMove(bool first);
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) override;
    virtual void move(int x,int y,int selected_x,int selected_y) override;
    virtual string getType();
    virtual int getPlacedX();
    virtual int getPlacedY();
    virtual bool is_black();
    virtual bool get_enabled();
    virtual void set_enabled(bool enabled_in);
    virtual ~Bishop_black(); // Virtual destructor
    //Rule of three
    Bishop_black(const Bishop_black& obj) = delete;
    Bishop_black& operator = (const Bishop_black& obj) = delete;
};