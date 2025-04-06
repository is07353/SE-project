#include<iostream>
#include "chess_piece.hpp"
#include <vector>
#include <cmath>
#include "white_pawn.hpp"
#include "rook_white.hpp"
#include "knight_white.hpp"
#include "Bishop_white.hpp"
#include "king_white.hpp"
#include "queen_white.hpp"
#include "knight_black.hpp"
#include "king_black.hpp"
#include "black_pawn.hpp"
#include "rook_black.hpp"
#include "queen_black.hpp"
#include "Bishop_black.hpp"
using namespace std;
// -----------------------game---------------------------
// Overloading the '!=' operator for chess pieces
bool chess_piece:: operator != (chess_piece& other)
    {   // Checking if the pieces belong to the same player (black or white)
        cout<<"overload "<< ( this->is_black() == other.is_black())<<endl;
        if ( this->is_black() == other.is_black())
        {
            return false;// Same player, so the pieces are not different
        }
        else
        {
        return true;// Different players, so the pieces are different
        }
    }
// chess_piece:: ~chess_piece() Commented out because game crashes when going for kill
// {
//     cout<<" called"<<endl;
// }
