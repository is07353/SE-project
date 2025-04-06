#include<iostream>
#include <vector>
#include <cmath>
#include "rook_black.hpp"
#include <string>
using namespace std;
    rook_black:: rook_black()
    {

    }
    void rook_black:: setFirstMove(bool first){}// Initializes the rook's first move
    // Initializes the rook's position on the board based on given coordinates
    void rook_black::  initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) 
    {
        if(once==true)
        {
            SDL_RenderCopy(gRenderer, assets, &Black_rook.srcRect, &Black_rook.moverRect);
        }
        else
        {
        if(num == 0)
        {
            SDL_RenderCopy(gRenderer, assets, &Black_rook.srcRect, &Black_rook.moverRect);
            once = true;
        }
        else if(num==1)
        {
            Black_rook.moverRect.x+=560;
            SDL_RenderCopy(gRenderer, assets, &Black_rook.srcRect, &Black_rook.moverRect);
            once = true;
        }
        }
    }
    void rook_black::  move(int x,int y,int selected_x,int selected_y) // Handles the rook's movement logic based on selected coordinates
    {
        if( x>selected_x-20 and x<selected_x+20    )
        {   
            Black_rook.moverRect.x = x;
            Black_rook.moverRect.y = y; 
        }
        else if( y>selected_y-10 and y<selected_y+10    )
        {   
            Black_rook.moverRect.x = x;
            Black_rook.moverRect.y = y; 
        }
    }
    string rook_black::  getType(){return "Rook_Black";}// Returns the type of the piece
    int rook_black::  getPlacedX()// Returns the X coordinate of the piece
    {
        return Black_rook.moverRect.x;
    }
    int rook_black::  getPlacedY()// Returns the y coordinate of the piece
    {
        return Black_rook.moverRect.y;
    }
    bool rook_black::  is_black()// Checks if the piece is black
    {
        return true;
    }
    bool rook_black::  get_enabled()// Gets the enabled status of the piece
    {
        return enabled;
    }
    void rook_black::  set_enabled(bool enabled_in)// Sets the enabled status of the piece
    {
        enabled = enabled_in;
    }
    rook_black:: ~rook_black()
    {
        // Destructor for the rook
    }