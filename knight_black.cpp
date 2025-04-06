#include<iostream>
#include <vector>
#include <cmath>
#include "knight_black.hpp"
#include <string>
using namespace std;
    knight_black:: knight_black()
    {

    }
    void knight_black:: setFirstMove(bool first){}//Set the first move for the black knight
    void knight_black:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets, int num) //Initialize the black knight's position on the chessboard
    // - gRenderer: SDL renderer for rendering graphics
    // - assets: Texture assets for the chessboard
    // - num: Indicates the number of black knights to initialize
    // Logic:
    // - Renders the black knight's position on the chessboard based on 'once' and 'num'
    {   
        if(once==true)
        {
            SDL_RenderCopy(gRenderer, assets, &Black_Knight.srcRect, &Black_Knight.moverRect);
        }
        else
        {
            if(num==0)// Renders the knight's image on the default position and sets once to true to indicate initialization.
            {
                SDL_RenderCopy(gRenderer, assets, &Black_Knight.srcRect, &Black_Knight.moverRect);
                once=true;
            }
            else if(num==1)
    //Shifts the knight's horizontal position by 400 units (presumably to set multiple knights at different starting positions) and then renders the knight's image.
            {
                Black_Knight.moverRect.x+=400;
                SDL_RenderCopy(gRenderer, assets, &Black_Knight.srcRect, &Black_Knight.moverRect);
                once=true;//to true to indicate that the knight's position has been set.
            }
        }
    }
    void knight_black:: move(int x,int y,int selected_x,int selected_y) 
    {// Function: move
    // Purpose: Move the black knight on the chessboard based on selected coordinates
    // - x, y: Current coordinates of the knight
    // - selected_x, selected_y: Selected coordinates to move the knight
    // Logic:
    // - Checks if the movement aligns with the knight's L-shaped move pattern
    // - Updates the knight's position if the move is valid
        if (std::abs(selected_x - x) <= 80 and std::abs(selected_y - y) <= 160)
        /*Checks if the absolute difference between the selected x and the current x is less than or equal to 80 
        AND the absolute difference between the selected y and the current y is less than or equal to 160.*/
        {   
                Black_Knight.moverRect.x = x;
                Black_Knight.moverRect.y = y; 
        }
        else if (std::abs(selected_x - x) <= 160 and std::abs(selected_y - y) <= 80) 
        /*If the first condition is not met, this condition is evaluated.
        Checks if the absolute difference between the selected x and the current x is less than or equal to 160
         AND the absolute difference between the selected y and the current y is less than or equal to 80.*/
        {   
                Black_Knight.moverRect.x = x;
                Black_Knight.moverRect.y = y; 
        }
    }
    string knight_black:: getType()
    {
        return "Black_Knight"; // Purpose: Return the type of the chess piece ("Black_Knight")
    }
    int knight_black:: getPlacedX()
    {
        return Black_Knight.moverRect.x;// Purpose: Get the X-coordinate where the black knight is placed on the chessboard
    }
    int knight_black:: getPlacedY()    // Purpose: Get the Y-coordinate where the black knight is placed on the chessboard
    {
        return Black_Knight.moverRect.y;
    }
    bool knight_black:: is_black()    // Purpose: Check if the piece is black (for black knight, it returns true)
    {
        return true;
    }
    bool knight_black:: get_enabled()//Get whether the black knight is enabled or not
    {
        return enabled;
    }
    void knight_black:: set_enabled(bool enabled_in)//Set whether the black knight is enabled or not
    {
        enabled = enabled_in;
    }
    knight_black:: ~knight_black()
    {
        // Destructor for the black knight
    }