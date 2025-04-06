#include<iostream>
#include <vector>
#include <cmath>
#include "queen_white.hpp"
#include <string>
using namespace std;
//CONSTRUCTOR OVERLOADING
/*Two constructors are defined - one default constructor (queen_white::queen_white()) and another that takes a pointer to a chess_piece object (queen_black::queen_black(chess_piece* other)).
The second constructor initializes the Black_Queen object's position based on the position of another chess piece (other).*/
    queen_white:: queen_white()
    {

    }
    queen_white:: queen_white(chess_piece* other)
    {
        White_Queen.moverRect.x = other->getPlacedX();
        White_Queen.moverRect.y = other->getPlacedY();
    }
     void  queen_white:: setFirstMove(bool first){}
     void  queen_white:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) 
    {
        SDL_RenderCopy(gRenderer, assets, &White_Queen.srcRect, &White_Queen.moverRect);
    }
    void  queen_white:: move(int x,int y,int selected_x,int selected_y) 
    /* Handles the queen's movement logic based on selected coordinates. 
    Moves are allowed either horizontally, vertically, or diagonally.*/
    {
        if( x>selected_x-20 and x<selected_x+20    )    // Condition 1: Checks if the movement is within a close horizontal range of the selected position
        {   
            White_Queen.moverRect.x = x;
            White_Queen.moverRect.y = y; 
        }
        else if( y>selected_y-30 and y<selected_y    )// Condition 2: Checks if the movement is within a close vertical range of the selected position
        {   
            White_Queen.moverRect.x = x;
            White_Queen.moverRect.y = y; 
        }
        // Condition 3: Checks if the movement is along a diagonal path within a specified range
        else if (std::abs(selected_x - x) >= std::abs(selected_y - y) and (std::abs(selected_x - x) - std::abs(selected_y - y))<=30)
        {
            White_Queen.moverRect.x = x;
            White_Queen.moverRect.y = y; 
        }
    }
    string queen_white:: getType()
    {
        return "Queen_White";
    }
    int queen_white:: getPlacedX()
    {
        return White_Queen.moverRect.x;
    }
    int queen_white:: getPlacedY()
    {
        return White_Queen.moverRect.y;
    }
    bool queen_white:: is_black()
    {
        return false;
    }
    bool queen_white:: get_enabled()
    {
        return enabled;
    }
    void queen_white:: set_enabled(bool enabled_in)
    {
        enabled = enabled_in;
    }
    queen_white:: ~queen_white()
    {

    }