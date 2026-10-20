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