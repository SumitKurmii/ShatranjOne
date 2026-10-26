#include <gtest/gtest.h>
#include "../src/position.h"

TEST(PositionTest, Constructor) {
    Position pos;
    EXPECT_EQ(pos.getSideToMove(), WHITE);
    for (int i = 0; i < 64; i++) {
        EXPECT_EQ(pos.viewBoard(i), 0);
    }
    EXPECT_EQ(pos.getCastlingRights(),std::bitset<4>("0000"));
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
    EXPECT_EQ(pos.getCastlingRights(),std::bitset<4>("0000"));
    pos.setCastlingRights(true, false, true, false);
    EXPECT_EQ(pos.getCastlingRights(),std::bitset<4>("0101"));
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
    EXPECT_EQ(pos.getCastlingRights(),std::bitset<4>("0000"));
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