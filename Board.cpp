#include<iostream>
#include "chess_piece.hpp"
#include "GameChess.hpp"
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
#include "Board.hpp"
#include <vector>
#include <cmath>
using namespace std;
Board:: Board():Gamechess{}
    {
        for(int i = 0; i <= 7; i++)
        {
            for(int j = 0; j <= 7; j++)
            {
                cout<<i<<" "<<j<<endl;
                board[i][j] = nullptr;
            }
        }
        cout<<"test tty"<<endl;
        *ptrx = -10;
        *ptry = -10;
        board[0][6] = new Pawn_black;
        board[1][6] = new Pawn_black;
        board[2][6] = new Pawn_black;
        board[3][6] = new Pawn_black;
        board[4][6] = new Pawn_black;
        board[5][6] = new Pawn_black;
        board[6][6] = new Pawn_black;
        board[7][6] = new Pawn_black;
        board[0][7] = new rook_black;
        board[7][7] = new rook_black;
        board[2][7] = new Bishop_black;
        board[5][7] = new Bishop_black;
        board[1][7] = new knight_black;
        board[6][7] = new knight_black;
        board[3][7] = new king_black;
        board[4][7] = new queen_black;
        //white pieces
        board[0][1] = new white_pawn;
        board[1][1] = new white_pawn;
        board[2][1] = new white_pawn;
        board[3][1] = new white_pawn;
        board[4][1] = new white_pawn;
        board[5][1] = new white_pawn;
        board[6][1] = new white_pawn;
        board[7][1] = new white_pawn;
        board[0][0] = new rook_white;
        board[7][0] = new rook_white;
        board[5][0] = new Bishop_white;
        board[2][0] = new Bishop_white;
        board[6][0] = new knight_white;
        board[1][0] = new knight_white;
        board[4][0] = new king_white;
        board[3][0] = new queen_white;
        
    }
Board:: ~Board()
    {
        for(int i = 0; i <= 7; i++)
        {
            for(int j = 0; j <= 7; j++)
            {
                if (board[i][j] != nullptr)
                {
                    delete board[i][j];
                    board[i][j] = nullptr;
                }
            }
        }
    }
void Board:: run(SDL_Renderer* gRenderer,SDL_Texture* assets, bool first_time)
    {   
        if(first_time)
        {   
            //black pawns
            board[0][6]->initializer(gRenderer,assets,0);
            board[1][6]->initializer(gRenderer,assets,1);
            board[2][6]->initializer(gRenderer,assets,2);
            board[3][6]->initializer(gRenderer,assets,3);
            board[4][6]->initializer(gRenderer,assets,4);
            board[5][6]->initializer(gRenderer,assets,5);
            board[6][6]->initializer(gRenderer,assets,6);
            board[7][6]->initializer(gRenderer,assets,7);
            //black rook
            board[0][7]->initializer(gRenderer,assets,0);
            board[7][7]->initializer(gRenderer,assets,1);
            board[1][7]->initializer(gRenderer,assets,0);
            board[2][7]->initializer(gRenderer,assets,0);
            board[5][7]->initializer(gRenderer,assets,1);
            board[6][7]->initializer(gRenderer,assets,1);
            board[3][7]->initializer(gRenderer,assets,0);
            board[4][7]->initializer(gRenderer,assets,0);
            //white pawns
            board[0][1]->initializer(gRenderer,assets,0);
            board[1][1]->initializer(gRenderer,assets,1);
            board[2][1]->initializer(gRenderer,assets,2);
            board[3][1]->initializer(gRenderer,assets,3);
            board[4][1]->initializer(gRenderer,assets,4);
            board[5][1]->initializer(gRenderer,assets,5);
            board[6][1]->initializer(gRenderer,assets,6);
            board[7][1]->initializer(gRenderer,assets,7);
            // white rook
            board[0][0]->initializer(gRenderer,assets,0);
            board[7][0]->initializer(gRenderer,assets,1);
            //white knight
            board[6][0]->initializer(gRenderer,assets,1);
            board[1][0]->initializer(gRenderer,assets,0);
            // white bishop
            board[5][0]->initializer(gRenderer,assets,1);
            board[2][0]->initializer(gRenderer,assets,0);
            // white king
            board[4][0]->initializer(gRenderer,assets,0);
            // white queen
            board[3][0]->initializer(gRenderer,assets,0);
        }
        else
        {
            for(int i = 0; i <= 7; i++)
            {
                for(int j = 0; j <= 7; j++)
                {
                    if(board[i][j] != nullptr)
                    {   
                        if(j==0 and board[i][j]->getType() == "Pawn_Black" and black_queen_onboard() == false)
                        {
                            chess_piece* temp = board[i][j];
                            board[i][j] = new queen_black{board[i][j]};
                            delete []temp;
                            temp = nullptr;
                        }
                        else if(j==7 and board[i][j]->getType() == "Pawn_White" and white_queen_onboard() == false)
                        {
                            chess_piece* temp = board[i][j];
                            board[i][j] = new queen_white{board[i][j]};
                            delete []temp;
                            temp = nullptr;
                        }
                        board[i][j]->initializer(gRenderer,assets,100);
                    }
                }
            }
        }
        //check mate
        checknate();
        
    }
bool Board:: black_queen_onboard()// Check if the black queen is on the board
    {
        bool queen = false;    // Initialize a boolean flag to track the presence of the queen
        // Loop through each row and column on the board
        for(int i = 0; i <= 7; i++)
        {
            for(int j = 0; j <= 7; j++)
            {
                if(board[i][j] != nullptr)// Check if the current board position holds a piece
                {
                    if(board[i][j]->getType()=="Queen_Black")// Check if the piece at the current position is a black queen
                    {
                        queen = true;// Set the flag to true as the black queen is found
                    }                   
                }
            }
        }
        return queen;// Return the status of the queen presence on the board
    }
    bool Board:: white_queen_onboard()//same with the white queen
    {
        bool queen = false;
        for(int i = 0; i <= 7; i++)
        {
            for(int j = 0; j <= 7; j++)
            {
                if(board[i][j] != nullptr)
                {
                    if(board[i][j]->getType()=="Queen_White")
                    {
                        queen = true;
                    }                   
                }
            }
        }
        return queen;
    }
    void Board:: checknate()
    {    // Initialize flags to track whether kings for both black and white teams are present
        bool king_white = false;
        bool king_black = false;
        // Iterate through each position on the board
        for(int i = 0; i <= 7; i++)
        {
            for(int j = 0; j <= 7; j++)
            {
                if(board[i][j] != nullptr)// Check if there's a piece at the current position
                {
                    if(board[i][j]->getType()=="King_Black")
                    {
                        king_black = true;// If the piece is a black king, set the flag for black king existence to true
                    }
                    if(board[i][j]->getType()=="King_White")
                    {
                        //cout<<"met"<<endl;
                        king_white = true;//else set for white king to true
                    }
                    // cout<<i<<" "<<j<<" "<<endl;
                    // cout<<board[i][j]->getType()<<endl;
                    // cout<<king_black<<" "<<king_white<<endl;
                    
                }
            }
        }
        if(king_black == false)// Check if either of the kings is missing, indicating a checkmate
        {
            cout<<"CHECKMATE: Team white Wins"<< endl;
            disableall();// Disable all pieces as the game is over
            //SDL_Delay(2000);
            //SDL_Quit();
            return;
        }
         if(king_white == false)
        {
            cout<<"CHECKMATE: Team black Wins"<< endl;
            disableall();// Disable all pieces as the game is over
            //SDL_Delay(2000);
           // SDL_Quit();
            return;
        }
    }
    void Board:: disableall()
    {
         for(int i = 0; i <= 7; i++)
        {
            for(int j = 0; j <= 7; j++)
            {
                if(board[i][j] != nullptr) //Check if the current position on the board holds a piece
                {
                    board[i][j]->set_enabled(false);// Disable the piece by setting its 'enabled' status to false
                }
            }
        }
    }
    void Board:: select_piece(int x, int y)
    {
        // cout<<"x: "<<x<<" y: "<<y<<endl;
       //cout<<"x: "<<*ptrx<<" y: "<<*ptry<<endl;
        if(*ptrx==-10 && *ptry==-10)    // Check if the pointer coordinates for the selected piece are set to -10
        {
            cout<<"button pressed"<<endl;
            // If so, assign the clicked coordinates to ptrx and ptry after conversion
            *ptrx=(x / 80)-2;
            *ptry= y / 70;
            // Check if the clicked coordinates are within the board's range or if the selected position is empty
            if(*ptrx<0 || *ptrx>7 || *ptry>7 || *ptry<0 || board[*ptrx][*ptry] == nullptr || board[*ptrx][*ptry]->get_enabled() == false)
            {
                cout<<"point not acessable"<<endl;// If not accessible or empty, reset ptrx and ptry to -10 and return
                *ptrx= -10;
                *ptry= -10;
                return;
            }
            temppiece=board[*ptrx][*ptry];// Store the selected piece temporarily in temppiece and print its coordinates
            cout<<"x: "<<*ptrx<<" y: "<<*ptry<<endl;
            
        }
        else if(*ptrx!=-10 && *ptry!=-10)// If ptrx and ptry are not -10 (indicating a piece has been selected)
        {   // Check if the selected move is valid for different piece types (Pawn, Rook, Bishop, Knight, Queen)
            // Various conditional checks based on different piece types
            // Move the piece to the new position if the move is valid
            // Code blocks managing the movement of different pieces
            //delete board[*ptrx][*ptry];
            int temp_ptrx=(board[*ptrx][*ptry]->getPlacedX() / 80)-2;
            int temp_ptry= board[*ptrx][*ptry]->getPlacedY()  / 70;
            if(temp_ptrx>=0 && temp_ptrx<=7 && temp_ptry<=7 && temp_ptry>=0 )//if it is on the board
            {
                if (board[temp_ptrx][temp_ptry]!=board[*ptrx][*ptry])
                {
                //delete board[*ptrx][*ptry];
                if(board[temp_ptrx][temp_ptry]!=board[*ptrx][*ptry])// Check if the destination is different from the current position
                {
                    if  (board[*ptrx][*ptry]->getType()=="Pawn_Black")
                    {   // Check valid moves for the black pawn
                        if((*ptrx+1 == temp_ptrx && *ptry-1==temp_ptry) || (*ptrx-1 == temp_ptrx && *ptry-1==temp_ptry))
                        {
                            if(board[temp_ptrx][temp_ptry]==nullptr)// Check if the diagonal move is to an empty space its invalid
                            {
                                return;
                            }
                        }
                        else
                        {
                            for(int i = 1 ; i<*ptry- temp_ptry; i++ )// Check if the pawn moves forward and that the path is clear
                            {   //It verifies that the path between the current and target positions is clear.
                                //If any square along the path is occupied, the move is deemed invalid.
                                if(board[*ptrx][*ptry-i] != nullptr)
                                {
                                    return;
                                }
                            }
                        }
                        
                        board[*ptrx][*ptry]->setFirstMove(true);// If the pawn passes all movement conditions, set its first move to true
                    }
                    if  (board[*ptrx][*ptry]->getType()=="Pawn_White")//same for white pawn except we reverse *ptry
                    {
                        if((*ptrx+1 == temp_ptrx && *ptry+1==temp_ptry) || (*ptrx-1 == temp_ptrx && *ptry+1==temp_ptry))
                        {
                            if(board[temp_ptrx][temp_ptry]==nullptr)
                            {
                                return;
                            }
                        }
                        else
                        {
                            for(int i = 1 ; i<=temp_ptry-*ptry ; i++ )
                            {     
                                
                                if(board[*ptrx][*ptry+i] != nullptr)
                                {
                                    return;
                                }
                            }
                        }
                        board[*ptrx][*ptry]->setFirstMove(true);
                    }
                    if  (board[*ptrx][*ptry]->getType()=="Rook_Black" or board[*ptrx][*ptry]->getType()=="Rook_White")
                    {   //Each section checks for obstacles (other pieces) along the specified path and stops the movement if an obstacle is encountered. If no obstacles are present, the move is considered valid. 
                        int rook_move_y=*ptry- temp_ptry;
                        if (rook_move_y>0)// Check vertical movement along the y-axis
                        {
                            for(int i = 1 ; i<*ptry- temp_ptry; i++ ) // Rook moving upward
                            {     
                            if(board[*ptrx][*ptry-i] != nullptr)
                            {
                                cout<<"loop 1 fail"<<endl;
                                return;
                            }
                            }
                        }
                        else if (rook_move_y<0)
                        {// Rook moving downward
                            for(int i = 1 ; i<(-1*(*ptry- temp_ptry)); i++ )
                            {     
                            if(board[*ptrx][*ptry+i] != nullptr)
                            {
                                cout<<"loop 2 fail"<<endl;
                                return;
                            }
                            }
                        }
                        int rook_move_x= *ptrx - temp_ptrx ;
                        if (rook_move_x>0)// Check horizontal movement along the x-axis
                        {
                            for(int i = 1 ; i<*ptrx- temp_ptrx; i++ )// Rook moving left
                            {     
                            if(board[*ptrx-i][*ptry] != nullptr)
                            {
                                cout<<"loop 3 fail"<<endl;
                                return;
                            }
                            }
                        }
                        else if (rook_move_x<0)
                        {
                            for(int i = 1 ; i<(*ptrx- temp_ptrx)*(-1); i++ )// right move
                            {     
                            if(board[*ptrx+i][*ptry] != nullptr)
                            {
                                cout<<"loop 4 fail "<< *ptrx-i<<' '<<*ptry<<endl;
                                return;
                            }
                            }
                        }
                    }
                    if  (board[*ptrx][*ptry]->getType()=="Bishop_Black" or board[*ptrx][*ptry]->getType()=="Bishop_White" )
                    {   
                        int bishop_move_y=*ptry- temp_ptry;
                        int bishop_move_X=*ptrx-temp_ptrx;
                        // Diagonal Movement Validation
                        // Each condition corresponds to one of the four diagonal directions 
                        if (bishop_move_X<0 and bishop_move_y>0)// Diagonal move towards the top-right direction
                        {
                            for(int i = 1 ; i< abs(*ptrx-temp_ptrx) ; i++ )
                            {     
                                cout<<temp_ptrx<<endl;
                                if(board[*ptrx+i][*ptry-i] != nullptr)
                                {// Obstacle encountered, invalid move
                                    return;
                                }
                            }
                        }
                        if (bishop_move_X<0 and bishop_move_y<0)// Diagonal move towards the bottom-right direction
                        {
                            for(int i = 1 ; i< abs(*ptrx-temp_ptrx ) ; i++ )
                            {     
                            if(board[*ptrx+i][*ptry+i] != nullptr)
                            {
                                return;
                            }
                            }
                        }
                        if (bishop_move_X>0 and bishop_move_y<0)// Diagonal move towards the bottom-left direction
                        {
                            for(int i = 1 ; i< abs(*ptrx-temp_ptrx ) ; i++ )
                            {     
                            if(board[*ptrx-i][*ptry+i] != nullptr)
                            {
                                return;
                            }
                            }
                        }
                        if (bishop_move_X>0 and bishop_move_y>0)// Diagonal move towards the top-left direction
                        {
                            for(int i = 1 ; i< abs(*ptrx-temp_ptrx ); i++ )
                            {     
                            if(board[*ptrx-i][*ptry-i] != nullptr)
                            {
                                return;
                            }
                            }
                        }
                    }
                    if (board[*ptrx][*ptry]->getType()=="Black_Knight" or board[*ptrx][*ptry]->getType()=="White_Knight")
                    {   //It calculates the horizontal movement knight_move_X and vertical movement knight_move_y from the current position to the target position (temp_ptrx, temp_ptry).
                        // These movements are checked to ensure they match the L-shaped movement pattern of a knight in chess.
                        int knight_move_y=*ptry- temp_ptry;
                        int knight_move_X=*ptrx-temp_ptrx; 
                        cout<<abs(knight_move_X)<<" "<<abs(knight_move_y)<<endl;
                        // Check if the movement matches the L-shape of a knight
                        if ((abs(knight_move_X) != 1 or abs(knight_move_y) != 2 ) and (abs(knight_move_X) != 2 or abs(knight_move_y) != 1 ))
                        {
                            return;
                        }
                        if(board[temp_ptrx][temp_ptry]!=nullptr)// Check if there's a piece at the destination square
                        {   // Check if the piece at the destination square is of a different color (opponent's piece)
                            if(board[temp_ptrx][temp_ptry]->is_black()!=board[*ptrx][*ptry]->is_black())
                            {   // Capture the opponent's piece
                                delete[] board[temp_ptrx][temp_ptry];
                                board[temp_ptrx][temp_ptry] = nullptr;
                                cout<<"kill"<<endl;// kill the piece if all conditions apply hehe
                            }
                            else
                            {
                                return;
                            }
                            
                        }
                       
                    }
                    if (board[*ptrx][*ptry]->getType()=="Queen_Black" or board[*ptrx][*ptry]->getType()=="Queen_White")
                    {   /*Calculates the horizontal movement as queen_move_X and vertical movement as queen_move_y
                        from the current position to the target position (temp_ptrx, temp_ptry).*/
                        int queen_move_y=*ptry- temp_ptry;
                        int queen_move_X=*ptrx-temp_ptrx;
                        if (queen_move_X<0 and queen_move_y>0)
                        {   //It checks different movement patterns in all eight directions: vertical, horizontal, and diagonal.
                        /*Each condition checks for obstacles or pieces in the queen's path along different directions:
                            Diagonal Movements (4 directions):
                                                            Checks diagonal movements in all four directions by iterating over the spaces between the queen's current and target positions.
                            Vertical Movements (2 directions):
                                                            Checks for obstacles or pieces in the vertical upward and downward directions.
                            Horizontal Movements (2 directions):
                                                            Checks for obstacles or pieces in the horizontal leftward and rightward directions.*/
                            for(int i = 1 ; i<= abs(*ptrx-temp_ptrx) ; i++ )
                            {
                                cout<<i<<" ";
                                cout<<abs(*ptrx-temp_ptrx)<<endl;     
                                if(board[*ptrx+i][*ptry-i] != nullptr)
                                {
                                    if (*ptrx+i!=temp_ptrx and *ptry-1 != temp_ptry)
                                    {
                                    cout<<"loop 1 failed"<<endl;//If there's an obstacle or a piece between the queen's current and target positions, it logs a failure for that particular loop.
                                    return;
                                    }
                                }
                            }
                        }
                        else if (queen_move_X<0 and queen_move_y<0)//down-right movement
                        {
                            for(int i = 1 ; i<= abs(*ptrx-temp_ptrx ) ; i++ )
                            {
                                cout<<i<<" ";
                                cout<<abs(*ptrx-temp_ptrx)<<endl;           
                            if(board[*ptrx+i][*ptry+i] != nullptr)
                            {
                                if (*ptrx+i!=temp_ptrx and *ptry+i != temp_ptry)
                                {
                                cout<<"loop 2 failed"<<endl;
                                return;
                                }
                            }
                            }
                        }
                        else if (queen_move_X>0 and queen_move_y<0)//down-left movement
                        {
                            for(int i = 1 ; i<= abs(*ptrx-temp_ptrx ) ; i++ )
                            {   
                                cout<<i<<" ";  
                                cout<<abs(*ptrx-temp_ptrx)<<endl;      
                            if(board[*ptrx-i][*ptry+i] != nullptr)
                            {
                                if (*ptrx-i!=temp_ptrx and *ptry+i != temp_ptry)
                                {
                                cout<<"loop 3 failed"<<endl;
                                return;
                                }
                            }
                            }
                        }
                        else if (queen_move_X>0 and queen_move_y>0)//top-left movement
                        {
                            for(int i = 1 ; i<= abs(*ptrx-temp_ptrx ); i++ )
                            {     
                                cout<<i<<" ";
                                cout<<abs(*ptrx-temp_ptrx)<<endl;     
                            if(board[*ptrx-i][*ptry-i] != nullptr && *ptrx-i!= temp_ptrx && *ptry-i!= temp_ptry)
                            {

                                cout<<"loop 4 failed"<<endl;
                                return;
                            }
                            }
                        }
                        else if (queen_move_y>0)//vertical movement
                        {
                            for(int i = 1 ; i<*ptry- temp_ptry; i++ )
                            {     
                            if(board[*ptrx][*ptry-i] != nullptr)
                            {
                                cout<<"loop 5 failed"<<endl;
                                return;
                            }
                            }
                        }
                        else if (queen_move_y<0)
                        {
                            for(int i = 1 ; i<(-1*(*ptry- temp_ptry)); i++ )
                            {     
                            if(board[*ptrx][*ptry+i] != nullptr)
                            {
                                cout<<"loop 6 failed"<<endl;
                                return;
                            }
                            }
                        }
                        else if (queen_move_X>0)//horizontal movement
                        {
                            for(int i = 1 ; i<*ptrx- temp_ptrx; i++ )
                            {     
                            if(board[*ptrx-i][*ptry] != nullptr)
                            {
                                cout<<"loop 7 failed"<<endl;
                                return;
                            }
                            }
                        }
                        else if (queen_move_X<0)
                        {
                            for(int i = 1 ; i<(*ptrx- temp_ptrx)*(-1); i++ )// right move
                            {     
                            if(board[*ptrx-i][*ptry] != nullptr)
                            {
                                cout<<"loop 8 failed"<<endl;
                                return;
                            }
                            }
                        }
                    }
                }    
                if (board[temp_ptrx][temp_ptry] != nullptr)//The code checks if there's a piece at the target position (temp_ptrx, temp_ptry).
                {
                    if((board[*ptrx][*ptry]->getType()=="Pawn_Black" or board[*ptrx][*ptry]->getType()=="Pawn_White" ))
                    {   //It compares the pointers to the pieces at the current and target positions. If they are different, indicating different pieces, it deletes the piece at the target position.
                        //If they are the same (indicating the same piece), it returns, considering it an invalid move.
                        if(board[*ptrx][*ptry]->getType()=="Pawn_Black")
                        {
                            cout<<"here"<<endl;
                            
                            cout<<"pawn cord: "<<*ptrx<<' '<<*ptry<<" to: "<<temp_ptrx<<' '<<temp_ptry<<' '<< endl;
                            if(*ptrx == temp_ptrx)//It verifies if the pawn is attempting a straight move (*ptrx == temp_ptrx). If so, it invalidates the move and returns.
                            {
                                return;
                            }
                        }
                        if(board[*ptrx][*ptry]->getType()=="Pawn_White")
                        {
                            cout<<"here"<<endl;
                            
                            cout<<"pawn cord: "<<*ptrx<<' '<<*ptry<<" to: "<<temp_ptrx<<' '<<temp_ptry<<' '<< endl;
                            if(*ptrx == temp_ptrx)
                            {
                                return;
                            }
                        }
                    }
                    cout<<(*board[temp_ptrx][temp_ptry]!=*board[*ptrx][*ptry])<<endl;
                    if(*board[temp_ptrx][temp_ptry]!=*board[*ptrx][*ptry])
                    {
                        delete[] board[temp_ptrx][temp_ptry];
                        board[temp_ptrx][temp_ptry] = nullptr;
                        cout<<"kill"<<endl;
                    }
                    else
                    {
                        return;
                    }
                }
                
                    cout<<"placed at x:"<< temp_ptrx<<" y:"<< temp_ptry<<endl;
                    board[temp_ptrx][temp_ptry] =  board[*ptrx][*ptry]; //memory leak
                    board[*ptrx][*ptry]=nullptr;
                    next_player(temp_ptrx,temp_ptry);//It calls next_player function to switch to the next player's turn based on the moved piece's new position.
                }
                //It resets the pointers *ptrx and *ptry to -10, indicating no currently selected piece.
                *ptrx=-10;
                *ptry=-10;
            }
            else
            {
                if(temppiece!=nullptr)//If there's a stored temporary piece (temppiece), it replaces it on the board at the initial position.
                {
                    board[*ptrx][*ptry]=temppiece;
                    next_player(*ptrx, *ptry);

                }
                
            }
            
        }
    }

    void Board:: next_player(int x, int y)
    { /*This function iterates through the entire chessboard (board) to assess the pieces.
        For each piece found on the board:
        If the piece's color (black or white) is different from the color of the piece at position (x, y), it sets the piece as enabled (set_enabled(true)).
        Otherwise, it disables the piece (set_enabled(false)).*/
        for(int i = 0; i <= 7; i++)
        {
            for(int j = 0; j <= 7; j++)
            {
                if(board[i][j] != nullptr)
                {
                    if(board[i][j]->is_black()!=board[x][y]->is_black())
                    {
                        board[i][j]->set_enabled(true);
                    }
                    else
                    {
                        board[i][j]->set_enabled(false);
                    }
                }
            }
        }
    }
    void Board:: mouse_in(int x, int y)
    {/*This function is likely triggered when the mouse moves over a particular position on the board.
        It checks if the mouse is within the board boundaries and if there's a piece at the selected position (*ptrx, *ptry) on the board.
        If a piece is present at that position:
        It calculates the selected position's center (selected_x, selected_y).
        It triggers the move() function of the piece at that position, likely for visual effects (like highlighting the se*/
        if(*ptrx>=0 && *ptrx<=7 && *ptry<=7 && *ptry>=0 && board[*ptrx][*ptry]!=nullptr)// Checks if the selected position (ptrx, ptry) is within the valid board boundaries
        {
            int selected_x = 80*(*ptrx+2)+40;// Calculates the x-coordinate offset
            int selected_y = 70*(*ptry)+35;// Calculates the y-coordinate offset
           board[*ptrx][*ptry]->move(x,y,selected_x,selected_y);// Calls the 'move' function of the piece at the selected position to handle updates or effects based on mouse interactions
        }
       
    }