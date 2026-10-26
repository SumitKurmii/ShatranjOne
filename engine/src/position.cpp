#include "position.h"

Position::Position() {
    for (int i = 0; i < 64; i++) {
        board[i] = 0;
    }

    sideToMove = WHITE;
    castlingRights.reset();
    enPassantTargetSquare = -1;
    halfMoveClock = 0;
    fullMoveNumber = 0;
}

void Position::setBoard(int square, int pieceCode) {
    if (square >= 0 && square < 64) {
        board[square] = pieceCode;
    }
}

int Position::viewBoard(int square) {
    if (square >= 0 && square < 64) {
        return board[square];
    }

    return -1;
}

void Position::printBoard() {
    for (int i = 0; i < 64; i++) {
        std::cout << board[i] << " ";

        if ((i + 1) % 8 == 0) {
            std::cout << std::endl;
        }
    }
}

void Position::setSideToMove(Color color) {
    sideToMove = color;
}

Color Position::getSideToMove() {
    return sideToMove;
}

void Position::setCastlingRights(bool K, bool Q, bool k, bool q) {
    castlingRights[0] = K;
    castlingRights[1] = Q;
    castlingRights[2] = k;
    castlingRights[3] = q;
}

std::bitset<4> Position::getCastlingRights() {
    return castlingRights;
}

void Position::setEnPassantTargetSquare(int square) {
    if (square >= 0 && square < 64) {
        enPassantTargetSquare = square;
    } else {
        enPassantTargetSquare = -1;
    }
}

int Position::getEnPassantTargetSquare() {
    return enPassantTargetSquare;
}

void Position::setHalfMoveClock(int count) {
    halfMoveClock = count;
}

int Position::getHalfMoveClock() {
    return halfMoveClock;
}

void Position::setFullMoveNumber(int count) {
    fullMoveNumber = count;
}

int Position::getFullMoveNumber() {
    return fullMoveNumber;
}

void Position::printPosition() {
    std::cout << "Board: " << std::endl;
    printBoard();

    std::cout << "Side to move: "
              << (sideToMove == WHITE ? "White" : "Black")
              << std::endl;

    std::cout << "Castling rights: "
              << castlingRights
              << std::endl;

    std::cout << "En-passant target square: "
              << enPassantTargetSquare
              << std::endl;

    std::cout << "Half-move clock: "
              << halfMoveClock
              << std::endl;

    std::cout << "Full-move number: "
              << fullMoveNumber
              << std::endl;
}

void Position::resetPosition() {
    for (int i = 0; i < 64; i++) {
        board[i] = 0;
    }

    sideToMove = WHITE;
    castlingRights.reset();
    enPassantTargetSquare = -1;
    halfMoveClock = 0;
    fullMoveNumber = 0;
}

int Position::getPieceCode(int square) {
    return viewBoard(square);
}