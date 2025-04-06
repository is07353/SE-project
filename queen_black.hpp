#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#pragma once
using namespace std;
class queen_black : public chess_piece
{
    private:
    Unit Black_Queen = {{1585, 106, 68, 138},{520, 540, 50, 50}};// Position and size information for rendering
    bool enabled = true;// State to track if the piece is enabled
    public:
    // Constructors
    queen_black();// Default constructor
    queen_black(chess_piece* other);// Constructor taking another chess piece as an argument
    // Virtual functions from the base class
    virtual void setFirstMove(bool first);// Marks the first move
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) override;// Initializes piece appearance
    virtual void move(int x,int y,int selected_x,int selected_y) override;// Handles piece movement logic
    void set_x_y(int x, int y);
    virtual string getType();// Returns the type of the piece
    virtual int getPlacedX();// Returns the x-coordinate of the piece's position
    virtual int getPlacedY();// Returns the x-coordinate of the piece's position
    virtual bool is_black();
    virtual bool get_enabled();
    virtual void set_enabled(bool enabled_in);
    virtual ~queen_black(); //Virtual Destructor
    //Rule of three
    queen_black(const queen_black& obj) = delete;
    queen_black& operator =(const queen_black& obj) = delete;
};