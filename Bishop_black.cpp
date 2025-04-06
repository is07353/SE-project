#include<iostream>
#include <vector>
#include <cmath>
#include "Bishop_black.hpp"
#include <string>
using namespace std;
    Bishop_black:: Bishop_black()
    {

    }
    void Bishop_black:: setFirstMove(bool first){}// Implementation of the setFirstMove method
    void Bishop_black:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) 
    {   // Method to initialize the black bishop
        if(once==true)
        {
            SDL_RenderCopy(gRenderer, assets, &Black_Bishop.srcRect, &Black_Bishop.moverRect);
        }
        else
        {
            if(num == 0)
            {
            SDL_RenderCopy(gRenderer, assets, &Black_Bishop.srcRect, &Black_Bishop.moverRect);
            once = true;

            }
            else if (num==1)
            {
                Black_Bishop.moverRect.x+=240;
                SDL_RenderCopy(gRenderer, assets, &Black_Bishop.srcRect, &Black_Bishop.moverRect);
                once = true;
            }
        }
    }
    void Bishop_black:: move(int x,int y,int selected_x,int selected_y) // Method to move the black bishop to a new position
     {  
        cout<<x<<" "<<y<<endl;
        // cout<<selected_x<<" "<<selected_y<<endl;
        // cout<<std::abs(selected_x - x)<<" "<<std::abs(selected_y - y)<<endl;
        // Check if the movement is valid based on x, y coordinates
        if (std::abs(selected_x - x) >= std::abs(selected_y - y) and (std::abs(selected_x - x) - std::abs(selected_y - y))<=25 and x>180 and x< 760) 
        {   
            Black_Bishop.moverRect.x = x;
            Black_Bishop.moverRect.y = y; 
        }

     }
    string Bishop_black:: getType()
    {
        return "Bishop_Black"; // Method to get the type of the piece (Bishop_Black)
    }
    int Bishop_black:: getPlacedX()// Method to get the current X position of the black bishop
    {
        return Black_Bishop.moverRect.x;
    }
    int Bishop_black:: getPlacedY()// Method to get the current Y position of the black bishop
    {
        return Black_Bishop.moverRect.y;
    }
    bool Bishop_black:: is_black()// Method to check if the piece is black
    {
        return true;
    }
    bool Bishop_black:: get_enabled() // Method to get the enabled status of the piece
    {
        return enabled;
    }
    void Bishop_black:: set_enabled(bool enabled_in)// Method to set the enabled status of the piece
    {
        enabled = enabled_in;
    }
    Bishop_black:: ~Bishop_black() // Destructor for the Bishop_black class
    {

    } 
    