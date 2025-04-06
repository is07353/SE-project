#include<iostream>
#include <vector>
#include <cmath>
#include "white_pawn.hpp"
#include <string>
using namespace std;
    white_pawn:: white_pawn()
    {

    }
    void white_pawn:: initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) // Initializes the white pawn's position on the board
    {   if(once==true)
        {
            SDL_RenderCopy(gRenderer, assets, &White_Pawn.srcRect, &White_Pawn.moverRect);
        }
        else
        {// Shifts the pawn's position based on the specified 'num'
            White_Pawn.moverRect.x += num*80;
            SDL_RenderCopy(gRenderer, assets, &White_Pawn.srcRect, &White_Pawn.moverRect);
            once=true;
        }
    }
    // Handles movement logic for the white pawn based on selected coordinates
    void white_pawn::move(int x,int y,int selected_x,int selected_y) 
    {
        if( first_move_white == false and x>selected_x-20 and x<selected_x+20 and y<selected_y+140 and y>selected_y-25  )
        {           // Moves the pawn two squares forward on its first move


            White_Pawn.moverRect.x = x;
            White_Pawn.moverRect.y = y;
            
        }
        else if(x>selected_x and x<selected_x+80  and y<selected_y +70 and y>selected_y )
        {    // Moves the pawn one square forward
            cout<<"new cond"<<x<<" "<<y<<endl;
            White_Pawn.moverRect.x = x;
            White_Pawn.moverRect.y = y;
            
        }
        else if( x>selected_x-80 and x<selected_x  and y<selected_y +70 and y>selected_y)
        {   // Moves the pawn one square forward (alternative direction)
            cout<<"new cond"<<x<<" "<<y<<endl;
            White_Pawn.moverRect.x = x;
            White_Pawn.moverRect.y = y;
            
        }
        else if(first_move_white == true and x>selected_x-20 and x<selected_x+20   and y<selected_y+70 and y>selected_y-25  )
        {   // Moves the pawn one square forward after its first move
            White_Pawn.moverRect.x = x;
            White_Pawn.moverRect.y = y;
            
        }   
    }
    void white_pawn:: setFirstMove(bool first) // Sets the first move flag for the white pawn
    {
        first_move_white = first;
    }
    string white_pawn:: getType() // Retrieves the type of the piece
    {
        return "Pawn_White";
    } 
    int  white_pawn::getPlacedX () // Retrieves the X coordinate of the piece on the board
    {
        return White_Pawn.moverRect.x;
    }
    int  white_pawn::getPlacedY() // Retrieves the Y coordinate of the piece on the board
    {
        return White_Pawn.moverRect.y;
    }
    bool white_pawn:: is_black() // Checks if the piece is black
    {
        return false;
    }
    bool white_pawn:: get_enabled()// Retrieves the enabled status of the piece
    {
        return enabled;
    }
     void white_pawn:: set_enabled(bool enabled_in)// Sets the enabled status of the piece
    {
        enabled = enabled_in;
    }
    white_pawn:: ~white_pawn()
    {
      // Destructor for the white_pawn class  
    }