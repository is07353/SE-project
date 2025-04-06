#include<iostream>
#include <vector>
#include <cmath>
#include "rook_white.hpp"
#include <string>
using namespace std;
    rook_white:: rook_white()
    {

    }
    void rook_white:: setFirstMove(bool first){}// Initializes the rook's first move
    void rook_white:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) // Initializes the rook's position on the board based on given coordinates
    {
        if(once==true)
        {
            SDL_RenderCopy(gRenderer, assets, &White_rook.srcRect, &White_rook.moverRect);
        }
        else
        {
        if(num == 0)
        {
            SDL_RenderCopy(gRenderer, assets, &White_rook.srcRect, &White_rook.moverRect);
            once = true;
        }
        else if(num==1)
        {
            White_rook.moverRect.x+=560;
            SDL_RenderCopy(gRenderer, assets, &White_rook.srcRect, &White_rook.moverRect);
            once = true;
        }
        }
    }
     void rook_white:: move(int x,int y,int selected_x,int selected_y)  // Handles the rook's movement logic based on selected coordinates
     {
        if( x>selected_x-20 and x<selected_x+20    )
        {   
            White_rook.moverRect.x = x;
            White_rook.moverRect.y = y; 
        }
        else if( y>selected_y-30 and y<selected_y    )
        {   
            White_rook.moverRect.x = x;
            White_rook.moverRect.y = y; 
        }
     }
    string rook_white:: getType()// Returns the type of the piece
    {
        return "Rook_White";
    }
    int rook_white:: getPlacedX()// Returns the X coordinate of the piece
    {
        return White_rook.moverRect.x;
    }
    int rook_white:: getPlacedY()// Returns the y coordinate of the piece
    {
        return White_rook.moverRect.y;
    }
    bool rook_white:: is_black()// Checks if the piece is black
    {
        return false;
    }
    bool rook_white:: get_enabled()// Gets the enabled status of the piece
    {
        return enabled;
    }
    void rook_white:: set_enabled(bool enabled_in)// Sets the enabled status of the piece
    {
        enabled = enabled_in;
    }
    rook_white:: ~rook_white()
    {
        // Destructor for the rook
    }