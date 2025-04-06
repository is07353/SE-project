#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class white_pawn : public chess_piece // Declaration of the white_pawn class inheriting from the chess_piece base class
{
    private:
    Unit White_Pawn  = {{916, 786, 63, 104},{200, 85, 50, 50}};// Unit defining the white pawn's dimensions and position on the board
    bool once = false;// Flag to handle the initialization process
    bool first_move_white = false; // Flag to track the first move of the white pawn
    bool enabled = true;    // Flag to control the enabled status of the white pawn

    public:
    white_pawn();
    // Overrides for base class methods
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) override;
    virtual void move(int x,int y,int selected_x,int selected_y) override;// Handles movement logic for the white pawn based on selected coordinates
    virtual void setFirstMove(bool first) override;// Sets the flag for the first move of the white pawn
    virtual string getType();// Retrieves the type of the piece
    virtual int getPlacedX (); // Retrieves the X coordinate of the piece on the board
    virtual int getPlacedY();// Retrieves the y coordinate of the piece on the board
    virtual bool is_black(); // Checks if the piece is black
    virtual bool get_enabled();    // Retrieves the enabled status of the piece
    virtual void set_enabled(bool enabled_in);// Sets the enabled status of the piece
    virtual ~white_pawn();//Virtual Destructor
    //Rule of three
    white_pawn(const white_pawn& obj) = delete;
    white_pawn& operator = (const white_pawn& obj) = delete;
};