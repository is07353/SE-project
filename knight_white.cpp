#include<iostream>
#include <vector>
#include <cmath>
#include "knight_white.hpp"
#include <string>
using namespace std;
    knight_white:: knight_white()
    {

    }
    void knight_white:: setFirstMove(bool first){}//Set the first move for the white knight
    void knight_white:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets, int num) //Initialize the white knight's position on the chessboard
    // - gRenderer: SDL renderer for rendering graphics
    // - assets: Texture assets for the chessboard
    // - num: Indicates the number of black knights to initialize
    // Logic:
    // - Renders the black knight's position on the chessboard based on 'once' and 'num'
    {   if(once==true)
        {
            SDL_RenderCopy(gRenderer, assets, &White_Knight.srcRect, &White_Knight.moverRect);
        }
        else
        {
            if(num==0)
            {
                SDL_RenderCopy(gRenderer, assets, &White_Knight.srcRect, &White_Knight.moverRect);
                once=true;
            }
            else if(num==1)
            {
                White_Knight.moverRect.x+=400;
                SDL_RenderCopy(gRenderer, assets, &White_Knight.srcRect, &White_Knight.moverRect);
                once=true;
            }
        }
    }
    void knight_white:: move(int x,int y,int selected_x,int selected_y) 
    /*Evaluates the movement validity for the white knight based on its specific L-shaped movement pattern.
    Checks if the absolute difference in x and y coordinates falls within specific ranges that represent valid knight moves.
    If the movement is valid, updates the moverRect coordinates to the new position (x, y).*/
    {
        if (std::abs(selected_x - x) <= 80 and std::abs(selected_y - y) <= 160)
        //validates if the absolute differences between the x and y coordinates are within the range of a typical knight move 
        //(maximum 2 squares in one direction and 1 square in another direction).
        //If both differences are within 80 and 160 respectively (or vice versa), it deems the move valid for a knight.
        //If the condition is met, it updates the moverRect coordinates of the white knight to the new position (x, y).
        {   
                White_Knight.moverRect.x = x;
                White_Knight.moverRect.y = y; 
        }
        else if (std::abs(selected_x - x) <= 160 and std::abs(selected_y - y) <= 80) 
        /*The second else if statement does a similar check but switches the allowed differences, allowing movement within 160 in the x direction and 80 in the y direction.
        If this condition is met, it also updates the moverRect coordinates to the new position (x, y).*/
        {   
                White_Knight.moverRect.x = x;
                White_Knight.moverRect.y = y; 
        }
    }
    string knight_white:: getType() //Returns a string identifying the type of the piece ("White_Knight").
    {
        return "White_Knight";
    }
    int knight_white:: getPlacedX()//Returns the x coordinates of the white knight
    {
        return White_Knight.moverRect.x;
    }
    int knight_white:: getPlacedY()//Returns the y coordinates of the white knight
    {
        return White_Knight.moverRect.y;
    }
    bool knight_white:: is_black()//Indicates that the piece is not black, affirming its color as white.
    {
        return false;
    }
    bool knight_white:: get_enabled()//Get whether the white knight is enabled or not
    {
        return enabled;
    }
    void knight_white:: set_enabled(bool enabled_in)//Set whether the white knight is enabled or not
    {
        enabled = enabled_in;
    }
    knight_white:: ~knight_white()
    {
        //Destructor for the white knight
    }