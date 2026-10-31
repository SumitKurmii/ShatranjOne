#ifndef POSITION_H
#define POSITION_H
#include <string>

#include <bitset>
#include <iostream>
enum Color {
    WHITE,
    BLACK
};
enum Piece {
    EMPTY = 0,

    WP = 1,
    WK = 2,
    WQ = 3,
    WB = 4,
    WN = 5,
    WR = 6,

    BP = -1,
    BK = -2,
    BQ = -3,
    BB = -4,
    BN = -5,
    BR = -6
};
enum Square {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,

    NO_SQUARE = -1
};class Position {
private:
    int board[64];

    Color sideToMove;

    std::bitset<4> castlingRights;

    int enPassantTargetSquare;
    int halfMoveClock;
    int fullMoveNumber;

public:
    Position();

    void setBoard(int square, int pieceCode);
    int viewBoard(int square) const;

    void printBoard();

    void setSideToMove(Color color);
    Color getSideToMove() const;

    void setCastlingRights(bool K, bool Q, bool k, bool q);
    bool getCastlingRights(int index) const;

    void setEnPassantTargetSquare(int square);
    int getEnPassantTargetSquare() const;

    void setHalfMoveClock(int count);
    int getHalfMoveClock() const;

    void setFullMoveNumber(int count);
    int getFullMoveNumber() const   ;

    void printPosition();
    void resetPosition();

    int getPieceCode(int square) const;
    bool loadFEN(const std::string& fen);
    std::string fenSerialization() const;

};
#endif