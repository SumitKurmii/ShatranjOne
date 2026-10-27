#include <gtest/gtest.h>
#include "../src/position.h"

TEST(PositionTest, Constructor) {
    Position pos;
    EXPECT_EQ(pos.getSideToMove(), WHITE);
    for (int i = 0; i < 64; i++) {
        EXPECT_EQ(pos.viewBoard(i), 0);
    }
    EXPECT_EQ(pos.getCastlingRights(0),false);
    EXPECT_EQ(pos.getCastlingRights(1),false);
    EXPECT_EQ(pos.getCastlingRights(2),false);
    EXPECT_EQ(pos.getCastlingRights(3),false);
    EXPECT_EQ(pos.getHalfMoveClock(), 0);
    EXPECT_EQ(pos.getFullMoveNumber(), 0);
    EXPECT_EQ(pos.getEnPassantTargetSquare(), -1);

    
}
TEST(PositionTest,Board){
    Position pos;
    EXPECT_EQ(pos.viewBoard(28), 0);
    pos.setBoard(28, 1);
    EXPECT_EQ(pos.viewBoard(28), 1);
}
TEST(PositionTest,SideToMove){
    Position pos;
    EXPECT_EQ(pos.getSideToMove(), WHITE);
    pos.setSideToMove(BLACK);
    EXPECT_EQ(pos.getSideToMove(), BLACK);
}
TEST(PositionTest,CastlingRights){
    Position pos;
    EXPECT_EQ(pos.getCastlingRights(0),false);
    EXPECT_EQ(pos.getCastlingRights(1),false);
    EXPECT_EQ(pos.getCastlingRights(2),false);
    EXPECT_EQ(pos.getCastlingRights(3),false);
    pos.setCastlingRights(true, false, true, false);
    EXPECT_EQ(pos.getCastlingRights(0),true);
    EXPECT_EQ(pos.getCastlingRights(1),false);
    EXPECT_EQ(pos.getCastlingRights(2),true);
    EXPECT_EQ(pos.getCastlingRights(3),false);
}
TEST(PositionTest,EnPassantTargetSquare){
    Position pos;
    EXPECT_EQ(pos.getEnPassantTargetSquare(), -1);
    pos.setEnPassantTargetSquare(20);
    EXPECT_EQ(pos.getEnPassantTargetSquare(), 20);
    pos.setEnPassantTargetSquare(-1);
    EXPECT_EQ(pos.getEnPassantTargetSquare(), -1);
}
TEST(PositionTest,HalfMoveClock){
    Position pos;
    EXPECT_EQ(pos.getHalfMoveClock(), 0);
    pos.setHalfMoveClock(5);
    EXPECT_EQ(pos.getHalfMoveClock(), 5);
}
TEST(PositionTest,FullMoveNumber){
    Position pos;
    EXPECT_EQ(pos.getFullMoveNumber(), 0);
    pos.setFullMoveNumber(10);
    EXPECT_EQ(pos.getFullMoveNumber(), 10);
}
TEST(PositionTest,ResetPosition){
    Position pos;
    pos.setBoard(28, 1);
    pos.setSideToMove(BLACK);
    pos.setCastlingRights(true, false, true, false);
    pos.setEnPassantTargetSquare(20);
    pos.setHalfMoveClock(5);
    pos.setFullMoveNumber(10);

    pos.resetPosition(); // Reset the position

    EXPECT_EQ(pos.getSideToMove(), WHITE);
    for (int i = 0; i < 64; i++) {
        EXPECT_EQ(pos.viewBoard(i), 0);
    }
    EXPECT_EQ(pos.getCastlingRights(0),false);
    EXPECT_EQ(pos.getCastlingRights(1),false);
    EXPECT_EQ(pos.getCastlingRights(2),false);
    EXPECT_EQ(pos.getCastlingRights(3),false);
    EXPECT_EQ(pos.getHalfMoveClock(), 0);
    EXPECT_EQ(pos.getFullMoveNumber(), 0);
    EXPECT_EQ(pos.getEnPassantTargetSquare(), -1);
}
TEST(PositionTest,InvalidSquare){
    Position pos;
    EXPECT_EQ(pos.viewBoard(-1), -1);
    EXPECT_EQ(pos.viewBoard(64), -1);
    pos.setBoard(-1, 1); // should not change anything
    pos.setBoard(64, 1); // should not change anything
    for (int i = 0; i < 64; i++) {
        EXPECT_EQ(pos.viewBoard(i), 0);
    }
}
TEST(PositionTest, LoadFEN) {
    Position pos;

    std::string fen =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    ASSERT_TRUE(pos.loadFEN(fen));

    EXPECT_EQ(pos.getSideToMove(), WHITE);

    EXPECT_TRUE(pos.getCastlingRights(0)); // K
    EXPECT_TRUE(pos.getCastlingRights(1)); // Q
    EXPECT_TRUE(pos.getCastlingRights(2)); // k
    EXPECT_TRUE(pos.getCastlingRights(3)); // q

    EXPECT_EQ(pos.getEnPassantTargetSquare(), NO_SQUARE);
    EXPECT_EQ(pos.getHalfMoveClock(), 0);
    EXPECT_EQ(pos.getFullMoveNumber(), 1);

    EXPECT_EQ(pos.getPieceCode(A1), WR);
    EXPECT_EQ(pos.getPieceCode(B1), WN);
    EXPECT_EQ(pos.getPieceCode(E1), WK);

    EXPECT_EQ(pos.getPieceCode(A8), BR);
    EXPECT_EQ(pos.getPieceCode(B8), BN);
    EXPECT_EQ(pos.getPieceCode(E8), BK);

    EXPECT_EQ(pos.getPieceCode(E4), EMPTY);
}
TEST(PositionTest, LoadFENWithState) {
    Position pos;

    std::string fen =
        "k3r2r/qp2npp1/n1p1b2p/3pN3/Q2P1B2/2P3P1/P4PBP/1R2R1K1 b - - 0 1";

    ASSERT_TRUE(pos.loadFEN(fen));

    EXPECT_EQ(pos.getSideToMove(), BLACK);

    EXPECT_FALSE(pos.getCastlingRights(0));
    EXPECT_FALSE(pos.getCastlingRights(1));
    EXPECT_FALSE(pos.getCastlingRights(2));
    EXPECT_FALSE(pos.getCastlingRights(3));

    EXPECT_EQ(pos.getEnPassantTargetSquare(), NO_SQUARE);
    EXPECT_EQ(pos.getHalfMoveClock(), 0);
    EXPECT_EQ(pos.getFullMoveNumber(), 1);

    EXPECT_EQ(pos.getPieceCode(A8), BK);
    EXPECT_EQ(pos.getPieceCode(E8), BR);
    EXPECT_EQ(pos.getPieceCode(H8), BR);
}
TEST(PositionTest, LoadFENInvalid) {
    Position pos;

    std::string fen = "invalid_fen_string";

    EXPECT_FALSE(pos.loadFEN(fen));
}
TEST(PositionTest, LoadFENInvalidPiece) {
    Position pos;

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNX w KQkq - 0 1"; // Invalid piece 'X'

    EXPECT_FALSE(pos.loadFEN(fen));
}
TEST(PositionTest, LoadFENInvalidSide) {
    Position pos;

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR x KQkq - 0 1"; // Invalid side 'x'

    EXPECT_FALSE(pos.loadFEN(fen));
}
TEST(PositionTest, LoadFENInvalidCastling) {
    Position pos;

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w ABCD - 0 1"; // Invalid castling rights 'ABCD'

    EXPECT_FALSE(pos.loadFEN(fen));
}
TEST(PositionTest, LoadFENInvalidEnPassant) {
    Position pos;

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq z9 0 1"; // Invalid en passant square 'z9'

    EXPECT_FALSE(pos.loadFEN(fen));
}
TEST(PositionTest, LoadFENInvalidHalfMove) {    
    
    Position pos;

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - -1 1"; // Invalid halfmove clock '-1'

    EXPECT_FALSE(pos.loadFEN(fen));
}   
TEST(PositionTest, LoadFENInvalidFullMove) {
    Position pos;

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0"; // Invalid fullmove number '0'

    EXPECT_FALSE(pos.loadFEN(fen));
}
TEST(PositionTest, LoadFENInvalidSquare) {
    Position pos;

    std::string fen = "rnbqk1bnr/ppppppp/8/8/7/8/PPPPPPPPP/R1QKBNR w KQkq - 0 1 extra"; // Extra part in FEN

    EXPECT_FALSE(pos.loadFEN(fen));
}