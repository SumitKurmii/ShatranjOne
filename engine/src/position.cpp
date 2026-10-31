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
    fullMoveNumber = 1;
}

void Position::setBoard(int square, int pieceCode) {
    if (square < 0 || square >= 64) {
        return;
    }

    switch (pieceCode) {
        case EMPTY:
        case WP:
        case WK:
        case WQ:
        case WB:
        case WN:
        case WR:
        case BP:
        case BK:
        case BQ:
        case BB:
        case BN:
        case BR:
            board[square] = pieceCode;
            break;

        default:
            return;
    }
}

int Position::viewBoard(int square) const {
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
    if (color == WHITE || color == BLACK) {
        sideToMove = color;
    }
}
Color Position::getSideToMove() const {
    return sideToMove;
}


void Position::setCastlingRights(bool K, bool Q, bool k, bool q) {
    castlingRights[0] = K;
    castlingRights[1] = Q;
    castlingRights[2] = k;
    castlingRights[3] = q;
}

bool Position::getCastlingRights(int index) const {
    if (index < 0 || index >= 4) {
        return false;
    }

    return castlingRights[index];
}

void Position::setEnPassantTargetSquare(int square) {
    if (square >= 0 && square < 64) {
        enPassantTargetSquare = square;
    } else {
        enPassantTargetSquare = -1;
    }
}

int Position::getEnPassantTargetSquare() const {
    return enPassantTargetSquare;
}

void Position::setHalfMoveClock(int count) {
    halfMoveClock = count;
}

int Position::getHalfMoveClock() const {
    return halfMoveClock;
}

void Position::setFullMoveNumber(int count) {
    fullMoveNumber = count;
}

int Position::getFullMoveNumber() const {
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
    fullMoveNumber = 1;
}

int Position::getPieceCode(int square) const {
    return viewBoard(square);
}


// fen parsing function 

bool Position::loadFEN(const std::string& fen) {
    Position parsed;
    std::stringstream ss(fen);

    std::string boardPart;
    char sidePart;
    std::string castlingPart;
    std::string enPassantPart;
    int halfMovePart;
    int fullMovePart;

    // Extract exactly six fields.
    if (!(ss >> boardPart >> sidePart >> castlingPart
             >> enPassantPart >> halfMovePart >> fullMovePart)) {
        return false;
    }

    std::string extraField;
    if (ss >> extraField) {
        return false;
    }

    // 1. Parse board placement.
    int rank = 7;
    int file = 0;

    for (char c : boardPart) {
        if (c == '/') {
            if (file != 8 || rank == 0) {
                return false;
            }

            --rank;
            file = 0;
        }
        else if (c >= '1' && c <= '8') {
            int emptySquares = c - '0';

            if (file + emptySquares > 8) {
                return false;
            }

            file += emptySquares;
        }
        else {
            int pieceCode = EMPTY;

            switch (c) {
                case 'P': pieceCode = WP; break;
                case 'K': pieceCode = WK; break;
                case 'Q': pieceCode = WQ; break;
                case 'B': pieceCode = WB; break;
                case 'N': pieceCode = WN; break;
                case 'R': pieceCode = WR; break;

                case 'p': pieceCode = BP; break;
                case 'k': pieceCode = BK; break;
                case 'q': pieceCode = BQ; break;
                case 'b': pieceCode = BB; break;
                case 'n': pieceCode = BN; break;
                case 'r': pieceCode = BR; break;

                default:
                    return false;
            }

            if (rank < 0 || file >= 8) {
                return false;
            }

            parsed.setBoard(rank * 8 + file, pieceCode);
            ++file;
        }
    }

    if (rank != 0 || file != 8) {
        return false;
    }

    // 2. Validate exactly one king of each colour.
    int whiteKingCount = 0;
    int blackKingCount = 0;

    for (int square = 0; square < 64; ++square) {
        int piece = parsed.getPieceCode(square);

        if (piece == WK) {
            ++whiteKingCount;
        }
        else if (piece == BK) {
            ++blackKingCount;
        }

        // Pawns cannot occupy rank 1 or rank 8.
        if ((piece == WP || piece == BP) &&
            (square / 8 == 0 || square / 8 == 7)) {
            return false;
        }
    }

    if (whiteKingCount != 1 || blackKingCount != 1) {
        return false;
    }

    // 3. Side to move.
    if (sidePart == 'w') {
        parsed.setSideToMove(WHITE);
    }
    else if (sidePart == 'b') {
        parsed.setSideToMove(BLACK);
    }
    else {
        return false;
    }

    // 4. Castling rights.
    bool K = false;
    bool Q = false;
    bool k = false;
    bool q = false;

    if (castlingPart != "-") {
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
    }

    // Required king and rook locations for each right.
    if (K && (parsed.getPieceCode(E1) != WK ||
              parsed.getPieceCode(H1) != WR)) {
        return false;
    }

    if (Q && (parsed.getPieceCode(E1) != WK ||
              parsed.getPieceCode(A1) != WR)) {
        return false;
    }

    if (k && (parsed.getPieceCode(E8) != BK ||
              parsed.getPieceCode(H8) != BR)) {
        return false;
    }

    if (q && (parsed.getPieceCode(E8) != BK ||
              parsed.getPieceCode(A8) != BR)) {
        return false;
    }

    parsed.setCastlingRights(K, Q, k, q);

    // 5. En-passant validation.
    if (enPassantPart == "-") {
        parsed.setEnPassantTargetSquare(-1);
    }
    else {
        if (enPassantPart.length() != 2) {
            return false;
        }

        int epFile = enPassantPart[0] - 'a';
        int epRank = enPassantPart[1] - '1';

        if (epFile < 0 || epFile > 7) {
            return false;
        }

        int epSquare = epRank * 8 + epFile;

        if (parsed.getSideToMove() == WHITE) {
            // Black must just have moved a pawn from rank 7 to rank 5.
            if (epRank != 5 ||
                parsed.getPieceCode(epSquare) != EMPTY ||
                parsed.getPieceCode(epSquare - 8) != BP ||
                parsed.getPieceCode(epSquare + 8) != EMPTY) {
                return false;
            }
        }
        else {
            // White must just have moved a pawn from rank 2 to rank 4.
            if (epRank != 2 ||
                parsed.getPieceCode(epSquare) != EMPTY ||
                parsed.getPieceCode(epSquare + 8) != WP ||
                parsed.getPieceCode(epSquare - 8) != EMPTY) {
                return false;
            }
        }
         // A double pawn push resets the halfmove clock.
        if (halfMovePart != 0) {
           return false;
         }

        parsed.setEnPassantTargetSquare(epSquare);
    }

    // 6. Move counters.
    if (halfMovePart < 0 || fullMovePart < 1) {
        return false;
    }
    parsed.setHalfMoveClock(halfMovePart);
    parsed.setFullMoveNumber(fullMovePart);
    *this = parsed;
    return true;
}

//fen Serialization
std::string Position::fenSerialization() const {
    std::string s;
    // 1. Piece placement
    for (int rank = 7; rank >= 0; rank--) {

        int emptyCount = 0;

        for (int file = 0; file < 8; file++) {

            int sq = rank * 8 + file;
            int pieceCode = getPieceCode(sq);

            if (pieceCode == EMPTY) {
                emptyCount++;
            }
            else {

                if (emptyCount > 0) {
                    s += std::to_string(emptyCount);
                    emptyCount = 0;
                }

                switch (pieceCode) {

                    case WP: s += 'P'; break;
                    case WK: s += 'K'; break;
                    case WQ: s += 'Q'; break;
                    case WB: s += 'B'; break;
                    case WN: s += 'N'; break;
                    case WR: s += 'R'; break;

                    case BP: s += 'p'; break;
                    case BK: s += 'k'; break;
                    case BQ: s += 'q'; break;
                    case BB: s += 'b'; break;
                    case BN: s += 'n'; break;
                    case BR: s += 'r'; break;

                    default:
                        throw std::logic_error(
                            "Invalid piece code in board"
                        );
                }
            }
        }

        // Flush remaining empty squares
        if (emptyCount > 0) {
            s += std::to_string(emptyCount);
        }

        if (rank > 0) {
            s += '/';
        }
    }

    // 2. Side to move
    s += ' ';
    s += (getSideToMove() == WHITE ? 'w' : 'b');

    // 3. Castling rights
    s += ' ';

    bool hasCastlingRights = false;

    if (getCastlingRights(0)) {
        s += 'K';
        hasCastlingRights = true;
    }

    if (getCastlingRights(1)) {
        s += 'Q';
        hasCastlingRights = true;
    }

    if (getCastlingRights(2)) {
        s += 'k';
        hasCastlingRights = true;
    }

    if (getCastlingRights(3)) {
        s += 'q';
        hasCastlingRights = true;
    }

    if (!hasCastlingRights) {
        s += '-';
    }

    // 4. En-passant target square
    s += ' ';

    int epSquare = getEnPassantTargetSquare();

    if (epSquare == -1) {
        s += '-';
    }
    else if (epSquare >= 0 && epSquare < 64) {
        char fileChar = 'a' + (epSquare % 8);
        char rankChar = '1' + (epSquare / 8);

        s += fileChar;
        s += rankChar;
    }
    else {
        throw std::logic_error("Invalid en-passant square");
    }

    // 5. Halfmove clock
    s += ' ';
    s += std::to_string(getHalfMoveClock());

    // 6. Fullmove number
    s += ' ';
    s += std::to_string(getFullMoveNumber());

    return s;
}