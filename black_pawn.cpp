#include<iostream>
#include <vector>
#include <cmath>
#include "black_pawn.hpp"
#include <string>
using namespace std;
// Implementation of the functions for the black pawn class
    Pawn_black:: Pawn_black()
    {
        //Default constructor
    }
    void Pawn_black:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) // Initializes the black pawn's position and appearance on the chessboard
    {   if(once==true)
        {
            SDL_RenderCopy(gRenderer, assets, &Black_Pawn.srcRect, &Black_Pawn.moverRect);
        }
        else
        {
            Black_Pawn.moverRect.x += num*80;
            SDL_RenderCopy(gRenderer, assets, &Black_Pawn.srcRect, &Black_Pawn.moverRect);
            once=true;
        }
    }
    void Pawn_black:: move(int x,int y,int selected_x,int selected_y) // Moves the black pawn on the chessboard based on selected coordinates
    {

        if(first_move == false and x>selected_x-20 and x<selected_x+20   and y>selected_y-160 and y<selected_y  )// Condition for the first move of the black pawn
        {   
            // Moves the black pawn forward by setting new coordinates
            Black_Pawn.moverRect.x = x;
            Black_Pawn.moverRect.y = y;
            
        }
        else if(x>selected_x and x<selected_x+80  and y<selected_y -60 and y>selected_y-80 )
        {   
            cout<<"new cond"<<x<<" "<<y<<endl;
            // Moves the pawn forward 
            Black_Pawn.moverRect.x = x;
            Black_Pawn.moverRect.y = y;
            
        }
        else if( x>selected_x-80 and x<selected_x  and y<selected_y -60 and y>selected_y-80)
        {   // Condition to move the pawn forward diagonally to capture piece
            cout<<"new cond"<<x<<" "<<y<<endl;
            Black_Pawn.moverRect.x = x;
            Black_Pawn.moverRect.y = y;
            
        }
         // Condition for subsequent moves after the first one
        else if(first_move == true and x>selected_x-20 and x<selected_x+20   and y>selected_y-80 and y<selected_y  )
        {   // Moves the black pawn forward by setting new coordinates
    
            Black_Pawn.moverRect.x = x;
            Black_Pawn.moverRect.y = y;
            
        }
    }
    void Pawn_black:: setFirstMove(bool first)// Sets the first move status of the black pawn
    {
        first_move = first;
    }
    string Pawn_black:: getType() // Returns the type of the chess piece (Pawn_Black)
    {
        return "Pawn_Black";
    }
    int Pawn_black:: getPlacedX()// Gets the X position of the black pawn on the chessboard
    {
            return Black_Pawn.moverRect.x;
    }
    int Pawn_black:: getPlacedY()// Gets the y position of the black pawn on the chessboard
    {
            return Black_Pawn.moverRect.y;
    }
    bool Pawn_black:: is_black()// Checks if the piece is black (always returns true for a black pawn)
    {
            return true;
    }
    bool Pawn_black:: get_enabled()// Gets the enabled status of the black pawn
    {
        return enabled;
    }
    void Pawn_black:: set_enabled(bool enabled_in)// Sets the enabled status of the black pawn
    {
        enabled = enabled_in;
    }
    Pawn_black:: ~Pawn_black()
    {
        // Destructor for the Pawn_black class
    } 
    