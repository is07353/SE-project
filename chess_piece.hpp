#include<SDL.h>
#pragma once
using namespace std;
// Abstract base class defining a chess piece
class chess_piece 
{
    public:
    // Pure virtual functions to be implemented by derived classes
    
    virtual void move(int x,int y,int yselected_x,int selected_y)=0;
    virtual void initializer(SDL_Renderer* gRenderer,SDL_Texture* assets,int num) = 0;
    virtual string getType() = 0;
    virtual void setFirstMove(bool first)=0;
    virtual int getPlacedX() = 0;
    virtual int getPlacedY() = 0;
    virtual bool is_black() = 0;
    virtual bool get_enabled() = 0;
    virtual void set_enabled(bool enabled_in)=0;
    bool operator != (chess_piece& other);
    // virtual ~chess_piece(); //Virtual Destructor
    /* The virtual dtor is causing our game to crash hence I have commented it out.
    It crashes when you try to kill a piece.
    Since the pieces are derived from this base class it also deletes the entire chess piece class when a piece is killed causing it to crash
    I even tried to do it with a pure virtual detructor but it was still not working
    You can comment this code out and test it yourself as well */
};
// Structure defining a unit (for rendering)
struct Unit
{
    SDL_Rect srcRect, moverRect;
};
