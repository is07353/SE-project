#include<iostream>
#include <vector>
#include <cmath>
#include "queen_black.hpp"
#include <string>
using namespace std;
//CONSTRUCTOR OVERLOADING
/*Two constructors are defined - one default constructor (queen_black::queen_black()) and another that takes a pointer to a chess_piece object (queen_black::queen_black(chess_piece* other)).
The second constructor initializes the Black_Queen object's position based on the position of another chess piece (other).*/
    queen_black:: queen_black()
    {

    }
    queen_black:: queen_black(chess_piece* other)
    {
        Black_Queen.moverRect.x = other->getPlacedX();
        Black_Queen.moverRect.y = other->getPlacedY();
    }
     void queen_black:: setFirstMove(bool first){}//Marks if it's the queen's first move.
     void queen_black:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) //Initializes the queen's position and appearance 
    {
        SDL_RenderCopy(gRenderer, assets, &Black_Queen.srcRect, &Black_Queen.moverRect);
    }
     void queen_black:: move(int x,int y,int selected_x,int selected_y) 
     /* Handles the queen's movement logic based on selected coordinates. 
     Moves are allowed either horizontally, vertically, or diagonally.*/
    {
        if( x>selected_x-20 and x<selected_x+20    )
        {   
            Black_Queen.moverRect.x = x;
            Black_Queen.moverRect.y = y; 
        }
        else if( y>selected_y-10 and y<selected_y+10    )
        {   
            Black_Queen.moverRect.x = x;
            Black_Queen.moverRect.y = y; 
        }
        else if (std::abs(selected_x - x) >= std::abs(selected_y - y) and (std::abs(selected_x - x) - std::abs(selected_y - y))<=25){
            Black_Queen.moverRect.x = x;
            Black_Queen.moverRect.y = y; 
        }
    }
    void queen_black:: set_x_y(int x, int y)// Updates the queen's position to a specific x and y coordinate.
    {
        Black_Queen.moverRect.x = x;
        Black_Queen.moverRect.y = y;
    }
    string queen_black:: getType()//Returns the type of the chess piece (in this case, "Queen_Black").
    {
        return "Queen_Black";
    }
    int  queen_black:: getPlacedX()// Returns the x coordinates of the queen's position.
    {
        return Black_Queen.moverRect.x;
    }
    int  queen_black::getPlacedY()// Returns the y coordinates of the queen's position.
    {
        return Black_Queen.moverRect.y;
    }
    bool queen_black:: is_black() //Indicates if the queen is black (returns true for a black piece).
    {
        return true;
    }
    bool queen_black:: get_enabled()
    {
        return enabled;
    }
    void queen_black:: set_enabled(bool enabled_in)
    {
        enabled = enabled_in;
    }
    queen_black:: ~queen_black()
    {
        //Destructor
    }