#include <iostream>
#include<bitset>
using namespace std;
typedef enum { WHITE, BLACK } Color;
 class Position {
private:
    // board
    int board[64];  
    /* 0-63 squares, each square can hold a piece code 
    0  = Empty
1  = White Pawn
2  = White King
3  = White Queen
4  = White Bishop
5  = White Knight
6  = White Rook

-1 = Black Pawn
-2 = Black King
-3 = Black Queen
-4 = Black Bishop
-5 = Black Knight
-6 = Black Rook
    */
    // side to move
   

    Color sideToMove;  //WHITE or BLACK 

    // castling rights
    bitset<4> castlingRights;  // 1 for available 0 for not available, 1 bit for each castling right  K-white King-side, Q-white Queen-side, k-black King-side, q-black Queen-side
    // en-passant square
    int enPassantTargetSquare; //-1 if no en-passant square, otherwise 0-63
    // counters
    int halfMoveClock;
    int fullMoveNumber;
    

public:
    // constructor
    Position(){
        for(int i = 0; i < 64; i++){
            board[i] = 0; // initialize all squares to empty
        }
        sideToMove = WHITE;
        castlingRights.reset();
        enPassantTargetSquare = -1;
        halfMoveClock = 0;
        fullMoveNumber = 0;
    };
    
    // functions you want other files to call
    void setBoard(int square, int pieceCode){
        if(square >= 0 && square < 64){
            board[square] = pieceCode;
        }
    };
    int viewBoard(int square){
        if(square >= 0 && square < 64){
            return board[square];
        }
        return -1; // invalid square
    };
    void printBoard(){
        for(int i = 0; i < 64; i++){
            cout << board[i] << " ";
            if((i+1) % 8 == 0){
                cout << endl;
            }
        }
    };
    void setSideToMove(Color color){
        sideToMove = color;
    };
    Color getSideToMove(){
        return sideToMove;
    };
    void setCastlingRights(bool K, bool Q, bool k, bool q){
        castlingRights[0] = K;
        castlingRights[1] = Q;
        castlingRights[2] = k;
        castlingRights[3] = q;
    };
    bitset<4> getCastlingRights(){
        return castlingRights;
    };
     void setEnPassantTargetSquare(int square){
        if(square >= 0 && square < 64){
            enPassantTargetSquare = square;
        } else {
            enPassantTargetSquare = -1; // no en-passant square
        } };
    int getEnPassantTargetSquare(){
        return enPassantTargetSquare;
    };
    void setHalfMoveClock(int count){
        halfMoveClock = count;
    };      
    int getHalfMoveClock(){
        return halfMoveClock;
    };  
    void setFullMoveNumber(int count){
        fullMoveNumber = count;
    };
    int getFullMoveNumber(){
        return fullMoveNumber;
    };
    void printPosition(){
        cout << "Board: " << endl;
        printBoard();
        cout << "Side to move: " << (sideToMove == WHITE ? "White" : "Black") << endl;
        cout << "Castling rights: " << castlingRights << endl;
        cout << "En-passant target square: " << enPassantTargetSquare << endl;
        cout << "Half-move clock: " << halfMoveClock << endl;
        cout << "Full-move number: " << fullMoveNumber << endl;
    };
    void resetPosition(){
        for(int i = 0; i < 64; i++){
            board[i] = 0;
        }
        sideToMove = WHITE;
        castlingRights.reset();
        enPassantTargetSquare = -1;
        halfMoveClock = 0;
        fullMoveNumber = 0;
    };
    

    int getPieceCode(int square){
        return viewBoard(square);
    };
};