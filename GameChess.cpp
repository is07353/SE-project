#include "GameChess.hpp"
using namespace std;
    // Constructor implementation
    Gamechess:: Gamechess()
    {
        ptrx= new int;// Allocate memory for X-coordinate pointer
        ptry=new int;// Allocate memory for y-coordinate pointer
    }
    // Destructor implementation
    Gamechess:: ~Gamechess()
    {
        delete  ptrx;// Deallocate memory for X-coordinate pointer
        ptrx=nullptr;//pointer set to null
        delete ptry;// Deallocate memory for y coordinate pointer
        ptry=nullptr;//pointer set to null
    }
