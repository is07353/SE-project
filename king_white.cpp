#include<iostream>
#include <vector>
#include <cmath>
#include "king_white.hpp"
#include <string>
using namespace std;    
    king_white:: king_white()
    {
        //Default constrcutor
    }
    void king_white:: setFirstMove(bool first){}
    void king_white:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) // Initializes the black king's position and appearance on the chessboard
    {
        SDL_RenderCopy(gRenderer, assets, &White_King.srcRect, &White_King.moverRect);
    }
     void king_white:: move(int x,int y,int selected_x,int selected_y) // Moves the black king on the chessboard based on selected coordinates
     
    {
        if( x>selected_x-20 and x<selected_x+20   and y>selected_y-80 and y<selected_y  )// Condition: Moves the king one square up
        {   
    
            White_King.moverRect.x = x;
            White_King.moverRect.y = y; 
        }
        else if(x>selected_x-20 and x<selected_x+20   and y<selected_y+70 and y>selected_y-25  )// Condition: Moves the king one square down
        {   
            White_King.moverRect.x = x;
            White_King.moverRect.y = y;
        }
        else if(x>selected_x and x<selected_x+90   and y<selected_y+20 and y>selected_y-20  )// Condition: Moves the king one square right
        {   
            White_King.moverRect.x = x;
            White_King.moverRect.y = y;
        }
        else if(x>selected_x and x<selected_x+90   and y<selected_y+70 and y>selected_y  )// Condition: Moves the king diagonally up-right
        {   
            White_King.moverRect.x = x;
            White_King.moverRect.y = y;
        }
        else if(x>selected_x and x<selected_x+90   and y<selected_y and y>selected_y-90  )// Condition: Moves the king diagonally up-left
        {   
            White_King.moverRect.x = x;
            White_King.moverRect.y = y;
        }
        else if(x>selected_x-90 and x<selected_x   and y<selected_y+70 and y>selected_y  ) // Condition: Moves the king diagonally down-right
        {   
            White_King.moverRect.x = x;
            White_King.moverRect.y = y;
        }
        else if(x>selected_x-90 and x<selected_x   and y<selected_y and y>selected_y-90  )// Condition: Moves the king diagonally down-left
        {   
            White_King.moverRect.x = x;
            White_King.moverRect.y = y;
        }
        else if(x>selected_x-90 and x<selected_x   and y<selected_y+20 and y>selected_y-20  )// Condition: Moves the king one square left
        {   
            White_King.moverRect.x = x;
            White_King.moverRect.y = y;
        }
    }
    string king_white:: getType()
    {
        return "King_White";
    }
    int king_white:: getPlacedX()
    {
        return  White_King.moverRect.x;
    }
    int king_white:: getPlacedY()
    {
        return  White_King.moverRect.y;
    }
    bool king_white:: is_black()
    {
        return false;
    }   
    bool king_white:: get_enabled()
    {
        return enabled;
    }
     void king_white:: set_enabled(bool enabled_in)
    {
        enabled = enabled_in;
    }
    king_white:: ~king_white()
    {
        //Destructor
    }