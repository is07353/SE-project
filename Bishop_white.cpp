#include<iostream>
#include <vector>
#include <cmath>
#include "Bishop_white.hpp"
#include <string>
using namespace std;
    Bishop_white:: Bishop_white()
    {

    }
    void Bishop_white:: setFirstMove(bool first){}
    void Bishop_white:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) // Initializes the white bishop's position and appearance on the chessboard
    {   
        if(once==true)
        {
            SDL_RenderCopy(gRenderer, assets, &White_Bishop.srcRect, &White_Bishop.moverRect);
        }
        else
        {
            if(num == 0)
            {
            SDL_RenderCopy(gRenderer, assets, &White_Bishop.srcRect, &White_Bishop.moverRect);
            once = true;

            }
            else if (num==1)
            {
                White_Bishop.moverRect.x+=240;
                SDL_RenderCopy(gRenderer, assets, &White_Bishop.srcRect, &White_Bishop.moverRect);
                once = true;
            }
        }
    }
    void Bishop_white:: move(int x,int y,int selected_x,int selected_y) // Moves the white bishop on the chessboard based on selected coordinates
    {  
        // cout<<x<<" "<<y<<endl;
        // cout<<selected_x<<" "<<selected_y<<endl;
        cout<<std::abs(selected_x - x)<<" "<<std::abs(selected_y - y)<<endl;
        if (std::abs(selected_x - x) >= std::abs(selected_y - y) and (std::abs(selected_x - x) - std::abs(selected_y - y))<=25) 
        {   
            White_Bishop.moverRect.x = x;
            White_Bishop.moverRect.y = y; 
        }

    }
    string Bishop_white:: getType()
    {
        return "Bishop_White"; // Returns the type of the chess piece (Bishop_White)
    }
    int Bishop_white:: getPlacedX()// Gets the X position of the white bishop on the chessboard
    {
        return White_Bishop.moverRect.x;
    }
    int Bishop_white:: getPlacedY()// Gets the y position of the white bishop on the chessboard
    {
        return White_Bishop.moverRect.y;
    }
    bool Bishop_white:: is_black()
    {
        return false;
    }
    bool Bishop_white:: get_enabled()
    {
        return enabled;
    }
    void Bishop_white:: set_enabled(bool enabled_in)
    {
        enabled = enabled_in;
    }
    Bishop_white:: ~Bishop_white()
    {
        // Destructor for the Bishop White class
    } 
    