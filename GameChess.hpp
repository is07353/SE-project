#pragma once
class Gamechess
{
    public:
    int* ptrx=nullptr;// Pointer for X-coordinate
    int* ptry=nullptr;// Pointer for Y-coordinate
    // Constructor 
    Gamechess();
    //For Rule of 3
    Gamechess(const Gamechess& obj) = delete;
    Gamechess& operator = (const Gamechess& obj) = delete;
    // Destructor
    ~Gamechess();
    
};