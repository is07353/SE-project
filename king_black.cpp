#include<iostream>
#include <vector>
#include <cmath>
#include "king_black.hpp"
#include <string>
using namespace std;  
    king_black:: king_black()
    {
        // Default constructor
    };
    void king_black:: setFirstMove(bool first){}
    void king_black:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) // Initializes the black king's position and appearance on the chessboard
    {
        SDL_RenderCopy(gRenderer, assets, &Black_King.srcRect, &Black_King.moverRect);
    }
    void king_black:: move(int x,int y,int selected_x,int selected_y) // Moves the black king on the chessboard based on selected coordinates
     {
        if( x>selected_x-20 and x<selected_x+20   and y>selected_y-80 and y<selected_y  )
        {   
            // Moves the king one square up
            Black_King.moverRect.x = x;
            Black_King.moverRect.y = y; 
        }
        else if(x>selected_x-20 and x<selected_x+20   and y<selected_y+70 and y>selected_y-25  )
        {   
            // Moves the king one square down
            Black_King.moverRect.x = x;
            Black_King.moverRect.y = y;
        }
        else if(x>selected_x and x<selected_x+90   and y<selected_y+20 and y>selected_y-20  )
        {   // Moves the king one square right
            Black_King.moverRect.x = x;
            Black_King.moverRect.y = y;
        }
         else if(x>selected_x and x<selected_x+90   and y<selected_y+80 and y>selected_y  )
        {   // Condition 4: Moves the king diagonally up and right
            Black_King.moverRect.x = x;
            Black_King.moverRect.y = y;
        }
         else if(x>selected_x and x<selected_x+90   and y<selected_y and y>selected_y-80  )
        {   // Condition 5: Moves the king diagonally up and left
            Black_King.moverRect.x = x;
            Black_King.moverRect.y = y;
        }
        else if(x>selected_x-90 and x<selected_x   and y<selected_y+20 and y>selected_y-20  )
        {   // Condition 6: Moves the king one square left
            Black_King.moverRect.x = x;
            Black_King.moverRect.y = y;
        }
        else if(x>selected_x-90 and x<selected_x   and y<selected_y+80 and y>selected_y  )
        {   // Condition 7: Moves the king diagonally down and left
            Black_King.moverRect.x = x;
            Black_King.moverRect.y = y;
        }
        else if(x>selected_x-90 and x<selected_x   and y<selected_y and y>selected_y-80  )
        {   // Condition 8: Moves the king diagonally down and right
            Black_King.moverRect.x = x;
            Black_King.moverRect.y = y;
        }
     }
    string king_black:: getType() // Returns the type of the chess piece (King_Black)
    {
        return "King_Black";
    }
    int king_black:: getPlacedX()// Gets the X position of the black king on the chessboard
    {
    return Black_King.moverRect.x;
    }
    int king_black:: getPlacedY()// Gets the y position of the black king on the chessboard
    {
    return Black_King.moverRect.y;
    }
    bool king_black:: is_black()// Checks if the piece is black
    {
    return true;
    }
    bool king_black:: get_enabled()// Gets the enabled status of the black king
    {
        return enabled;
    }
    void king_black:: set_enabled(bool enabled_in)// Sets the enabled status of the black king
    {
        enabled = enabled_in;
    }
    king_black:: ~king_black()
    {
        //Destructor
    }
