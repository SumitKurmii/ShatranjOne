#include "position.h"
#include <sstream>
using namespace std;
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

bool Position::getCastlingRights(int index) {
    return castlingRights[index];
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


// fen parsing function 
bool Position::loadFEN(const std::string& fen) {

    int rank = 7;
    int file = 0;

    std::stringstream ss(fen);

    std::string boardPart;
    char sidePart;
    std::string castlingPart;
    std::string enPassantPart;
    int halfMovePart;
    int fullMovePart;

    if (!(ss >> boardPart
              >> sidePart
              >> castlingPart
              >> enPassantPart
              >> halfMovePart
              >> fullMovePart)) {
        return false;
    }

    // 1. Board
    for (char c : boardPart) {

        if (c == '/') {
            rank--;
            file = 0;
        }
        else if (c >= '1' && c <= '8') {
            file += c - '0';
        }
        else {
            int square = rank * 8 + file;
            int pieceCode = 0;

            switch(c){
                   case 'P': pieceCode = WP; break;
                   case 'K': pieceCode = WK; break;
                   case 'Q': pieceCode = WQ; break;
                   case 'B': pieceCode = WB; break;
                   case 'N': pieceCode = WN; break;
                   case 'R': pieceCode = WR; break;

                   case 'p': pieceCode = BP; break;
                   case 'k': pieceCode = BK;  break;
                   case 'q': pieceCode = BQ; break;
                   case 'b': pieceCode = BB; break;
                   case 'n': pieceCode = BN; break;
                   case 'r': pieceCode = BR; break;

                default: return false;
}

            if (rank < 0 || rank > 7 || file < 0 || file > 7)
                return false;

            setBoard(square, pieceCode);
            file++;
        }
    }

    // 2. Side to move
    if (sidePart == 'w')
        setSideToMove(WHITE);
    else if (sidePart == 'b')
        setSideToMove(BLACK);
    else
        return false;

    // 3. Castling rights
   if (castlingPart == "-") {
    setCastlingRights(false, false, false, false);
}

else {
    bool K = false;
    bool Q = false;
    bool k = false;
    bool q = false;

    for (char c : castlingPart) {
        switch (c) {
            case 'K':
                if (K) return false;
                K = true;
                break;

            case 'Q':
                if (Q) return false;
                Q = true;
                break;

            case 'k':
                if (k) return false;
                k = true;
                break;

            case 'q':
                if (q) return false;
                q = true;
                break;

            default:
                return false;
        }
    }

    setCastlingRights(K, Q, k, q);
}
 

    // 4. En passant
    if (enPassantPart == "-") {
        setEnPassantTargetSquare(-1);
    }
    else {
        if (enPassantPart.length() != 2)
            return false;

        int file = enPassantPart[0] - 'a';
        int rank = enPassantPart[1] - '1';

        if (file < 0 || file > 7 || rank < 0 || rank > 7)
            return false;

        setEnPassantTargetSquare(rank * 8 + file);
    }

    // 5. Halfmove clock
    if (halfMovePart < 0)
        return false;

    setHalfMoveClock(halfMovePart);

    // 6. Fullmove number
    if (fullMovePart < 1)
        return false;

    setFullMoveNumber(fullMovePart);

    return true;
}