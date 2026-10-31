
#include <gtest/gtest.h>

#include "../src/position.h"

#include <stdexcept>
#include <string>

// ============================================================
// 1. POSITION CONSTRUCTOR
// ============================================================

TEST(PositionTest, Constructor) {
    Position pos;

    EXPECT_EQ(pos.getSideToMove(), WHITE);

    for (int i = 0; i < 64; ++i) {
        EXPECT_EQ(pos.viewBoard(i), EMPTY);
    }

    for (int i = 0; i < 4; ++i) {
        EXPECT_FALSE(pos.getCastlingRights(i));
    }

    EXPECT_EQ(pos.getEnPassantTargetSquare(), NO_SQUARE);
    EXPECT_EQ(pos.getHalfMoveClock(), 0);
    EXPECT_EQ(pos.getFullMoveNumber(), 1);
}


// ============================================================
// 2. BOARD OPERATIONS
// ============================================================

TEST(PositionTest, Board) {
    Position pos;

    EXPECT_EQ(pos.viewBoard(28), EMPTY);

    pos.setBoard(28, WP);

    EXPECT_EQ(pos.viewBoard(28), WP);
}

TEST(PositionTest, InvalidSquare) {
    Position pos;

    EXPECT_EQ(pos.viewBoard(-1), -1);
    EXPECT_EQ(pos.viewBoard(64), -1);

    pos.setBoard(-1, WP);
    pos.setBoard(64, WP);

    for (int i = 0; i < 64; ++i) {
        EXPECT_EQ(pos.viewBoard(i), EMPTY);
    }
}


// ============================================================
// 3. POSITION STATE
// ============================================================

TEST(PositionTest, SideToMove) {
    Position pos;

    EXPECT_EQ(pos.getSideToMove(), WHITE);

    pos.setSideToMove(BLACK);

    EXPECT_EQ(pos.getSideToMove(), BLACK);
}

TEST(PositionTest, CastlingRights) {
    Position pos;

    for (int i = 0; i < 4; ++i) {
        EXPECT_FALSE(pos.getCastlingRights(i));
    }

    pos.setCastlingRights(true, false, true, false);

    EXPECT_TRUE(pos.getCastlingRights(0));
    EXPECT_FALSE(pos.getCastlingRights(1));
    EXPECT_TRUE(pos.getCastlingRights(2));
    EXPECT_FALSE(pos.getCastlingRights(3));
}

TEST(PositionTest, EnPassantTargetSquare) {
    Position pos;

    EXPECT_EQ(pos.getEnPassantTargetSquare(), NO_SQUARE);

    pos.setEnPassantTargetSquare(20);

    EXPECT_EQ(pos.getEnPassantTargetSquare(), 20);

    pos.setEnPassantTargetSquare(-1);

    EXPECT_EQ(pos.getEnPassantTargetSquare(), NO_SQUARE);
}

TEST(PositionTest, HalfMoveClock) {
    Position pos;

    EXPECT_EQ(pos.getHalfMoveClock(), 0);

    pos.setHalfMoveClock(5);

    EXPECT_EQ(pos.getHalfMoveClock(), 5);
}

TEST(PositionTest, FullMoveNumber) {
    Position pos;

    EXPECT_EQ(pos.getFullMoveNumber(), 1);

    pos.setFullMoveNumber(10);

    EXPECT_EQ(pos.getFullMoveNumber(), 10);
}

TEST(PositionTest, ResetPosition) {
    Position pos;

    pos.setBoard(28, WP);
    pos.setSideToMove(BLACK);
    pos.setCastlingRights(true, false, true, false);
    pos.setEnPassantTargetSquare(20);
    pos.setHalfMoveClock(5);
    pos.setFullMoveNumber(10);

    pos.resetPosition();

    EXPECT_EQ(pos.getSideToMove(), WHITE);

    for (int i = 0; i < 64; ++i) {
        EXPECT_EQ(pos.viewBoard(i), EMPTY);
    }

    for (int i = 0; i < 4; ++i) {
        EXPECT_FALSE(pos.getCastlingRights(i));
    }

    EXPECT_EQ(pos.getEnPassantTargetSquare(), NO_SQUARE);
    EXPECT_EQ(pos.getHalfMoveClock(), 0);
    EXPECT_EQ(pos.getFullMoveNumber(), 1);
}


// ============================================================
// 4. BASIC FEN PARSING
// ============================================================

TEST(PositionTest, LoadFENStartingPosition) {
    Position pos;

    const std::string fen =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    ASSERT_TRUE(pos.loadFEN(fen));

    EXPECT_EQ(pos.getSideToMove(), WHITE);

    EXPECT_TRUE(pos.getCastlingRights(0));
    EXPECT_TRUE(pos.getCastlingRights(1));
    EXPECT_TRUE(pos.getCastlingRights(2));
    EXPECT_TRUE(pos.getCastlingRights(3));

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

    const std::string fen =
        "k3r2r/qp2npp1/n1p1b2p/3pN3/Q2P1B2/2P3P1/P4PBP/1R2R1K1 b - - 0 1";

    ASSERT_TRUE(pos.loadFEN(fen));

    EXPECT_EQ(pos.getSideToMove(), BLACK);

    for (int i = 0; i < 4; ++i) {
        EXPECT_FALSE(pos.getCastlingRights(i));
    }

    EXPECT_EQ(pos.getEnPassantTargetSquare(), NO_SQUARE);
    EXPECT_EQ(pos.getHalfMoveClock(), 0);
    EXPECT_EQ(pos.getFullMoveNumber(), 1);

    EXPECT_EQ(pos.getPieceCode(A8), BK);
    EXPECT_EQ(pos.getPieceCode(E8), BR);
    EXPECT_EQ(pos.getPieceCode(H8), BR);
}


// ============================================================
// 5. INVALID FEN INPUT
// ============================================================

class InvalidFENTest :
    public ::testing::TestWithParam<std::string> {
};

TEST_P(InvalidFENTest, RejectsInvalidFEN) {
    Position pos;

    EXPECT_FALSE(pos.loadFEN(GetParam()))
        << "Unexpectedly accepted FEN: " << GetParam();
}

INSTANTIATE_TEST_SUITE_P(
    InvalidInputs,
    InvalidFENTest,
    ::testing::Values(

        // Invalid or incomplete FEN
        "",
        "invalid_fen_string",
        "4k3/8/8/8/8/8/8/4K3 w - - 0",
        "4k3/8/8/8/8/8/8/4K3 w -",

        // Unknown piece characters
        "4k3/8/8/8/8/8/8/3XK3 w - - 0 1",
        "4k3/8/8/8/8/8/8/3@K3 w - - 0 1",

        // Invalid side
        "4k3/8/8/8/8/8/8/4K3 x - - 0 1",

        // Invalid castling characters
        "4k2r/8/8/8/8/8/8/4K2R w ABC - 0 1",

        // Duplicate castling rights
        "4k2r/8/8/8/8/8/8/4K2R w KK - 0 1",
        "4k2r/8/8/8/8/8/8/4K2R w KQK - 0 1",

        // Invalid en-passant notation
        "4k3/8/8/8/8/8/8/4K3 w - z9 0 1",

        // Invalid counters
        "4k3/8/8/8/8/8/8/4K3 w - - -1 1",
        "4k3/8/8/8/8/8/8/4K3 w - - 0 0",
        "4k3/8/8/8/8/8/8/4K3 w - - abc 1",
        "4k3/8/8/8/8/8/8/4K3 w - - 0 xyz",

        // Extra fields
        "4k3/8/8/8/8/8/8/4K3 w - - 0 1 extra",
        "4k3/8/8/8/8/8/8/4K3 w - - 0 1 extra another",

        // Seven and nine ranks
        "4k3/8/8/8/8/8/4K3 w - - 0 1",
        "4k3/8/8/8/8/8/8/4K3/8 w - - 0 1",

        // Seven and nine squares in a rank
        "4k3/8/8/8/8/8/8/3K w - - 0 1",
        "4k3/8/8/8/8/8/8/4K4 w - - 0 1",

        // Missing or consecutive separators
        "4k38/8/8/8/8/8/8/4K3 w - - 0 1",
        "4k3//8/8/8/8/8/4K3 w - - 0 1",

        // Invalid zero digit
        "4k3/8/8/8/8/8/8/0K7 w - - 0 1",

        // Missing white king
        "4k3/8/8/8/8/8/8/8 w - - 0 1",

        // Missing black king
        "8/8/8/8/8/8/8/4K3 w - - 0 1",

        // Multiple white kings
        "4k3/8/8/8/8/8/8/3KK3 w - - 0 1",

        // Multiple black kings
        "3kk3/8/8/8/8/8/8/4K3 w - - 0 1",

        // Pawns on first or eighth rank
        "4k3/8/8/8/8/8/8/P3K3 w - - 0 1",
        "P3k3/8/8/8/8/8/8/4K3 w - - 0 1",
        "4k3/8/8/8/8/8/8/p3K3 w - - 0 1",
        "p3k3/8/8/8/8/8/8/4K3 w - - 0 1",

        // Invalid castling king/rook placement
        "4k3/8/8/8/8/8/8/5K1R w K - 0 1",
        "4k3/8/8/8/8/8/8/4K3 w K - 0 1",
        "4k3/8/8/8/8/8/8/4K2R w Q - 0 1",
        "4k3/8/8/8/8/8/8/R3K3 w k - 0 1",
        "4k3/8/8/8/8/8/8/R3K3 w q - 0 1",

        // Invalid en-passant ranks
        "4k3/8/8/8/8/8/8/4K3 w - e4 0 1",
        "4k3/8/8/8/8/8/8/4K3 b - e5 0 1",

        // En-passant without previous double-pushed pawn
        "4k3/8/8/8/8/8/8/4K3 w - e6 0 1",

        // En-passant target occupied
        "4k3/8/4N3/4p3/8/8/8/4K3 w - e6 0 1",

        // Wrong pawn colour for en-passant
        "4k3/8/8/4P3/8/8/8/4K3 w - e6 0 1",

        // Previous pawn starting square not empty
        "4k3/4p3/8/4p3/8/8/8/4K3 w - e6 0 1"
    )
);


// ============================================================
// 6. KING COUNT VALIDATION
// ============================================================

TEST(PositionTest, LoadFENExactlyOneKingEach) {
    Position pos;

    ASSERT_TRUE(pos.loadFEN(
        "4k3/8/8/8/8/8/8/4K3 w - - 0 1"
    ));

    int whiteKingCount = 0;
    int blackKingCount = 0;

    for (int square = 0; square < 64; ++square) {
        int piece = pos.getPieceCode(square);

        if (piece == WK) {
            ++whiteKingCount;
        }
        else if (piece == BK) {
            ++blackKingCount;
        }
    }

    EXPECT_EQ(whiteKingCount, 1);
    EXPECT_EQ(blackKingCount, 1);
}


// ============================================================
// 7. CASTLING RIGHTS
// ============================================================

TEST(PositionTest, LoadFENAllCastlingRights) {
    Position pos;

    ASSERT_TRUE(pos.loadFEN(
        "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
    ));

    EXPECT_TRUE(pos.getCastlingRights(0));
    EXPECT_TRUE(pos.getCastlingRights(1));
    EXPECT_TRUE(pos.getCastlingRights(2));
    EXPECT_TRUE(pos.getCastlingRights(3));
}

TEST(PositionTest, LoadFENPartialCastlingRights) {
    Position pos;

    ASSERT_TRUE(pos.loadFEN(
        "r3k2r/8/8/8/8/8/8/R3K2R w Kq - 0 1"
    ));

    EXPECT_TRUE(pos.getCastlingRights(0));
    EXPECT_FALSE(pos.getCastlingRights(1));
    EXPECT_FALSE(pos.getCastlingRights(2));
    EXPECT_TRUE(pos.getCastlingRights(3));
}

TEST(PositionTest, LoadFENNoCastlingRights) {
    Position pos;

    ASSERT_TRUE(pos.loadFEN(
        "4k3/8/8/8/8/8/8/4K3 w - - 0 1"
    ));

    for (int i = 0; i < 4; ++i) {
        EXPECT_FALSE(pos.getCastlingRights(i));
    }
}


// ============================================================
// 8. EN-PASSANT VALIDATION
// ============================================================

TEST(PositionTest, LoadFENValidWhiteEnPassant) {
    Position pos;

    ASSERT_TRUE(pos.loadFEN(
        "4k3/8/8/4p3/8/8/8/4K3 w - e6 0 1"
    ));

    EXPECT_EQ(pos.getEnPassantTargetSquare(), E6);
}

TEST(PositionTest, LoadFENValidBlackEnPassant) {
    Position pos;

    ASSERT_TRUE(pos.loadFEN(
        "4k3/8/8/8/4P3/8/8/4K3 b - e3 0 1"
    ));

    EXPECT_EQ(pos.getEnPassantTargetSquare(), E3);
}

TEST(PositionTest, LoadFENNoEnPassant) {
    Position pos;

    ASSERT_TRUE(pos.loadFEN(
        "4k3/8/8/8/8/8/8/4K3 w - - 0 1"
    ));

    EXPECT_EQ(pos.getEnPassantTargetSquare(), NO_SQUARE);
}


// ============================================================
// 9. REPEATED AND TRANSACTIONAL LOADING
// ============================================================

TEST(PositionTest, LoadFENRepeatedLoadReplacesBoard) {
    Position pos;

    const std::string firstFen =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    const std::string secondFen =
        "4k3/8/8/8/8/8/8/4K3 b - - 0 1";

    ASSERT_TRUE(pos.loadFEN(firstFen));
    ASSERT_TRUE(pos.loadFEN(secondFen));

    for (int square = 0; square < 64; ++square) {
        if (square == E1) {
            EXPECT_EQ(pos.getPieceCode(square), WK);
        }
        else if (square == E8) {
            EXPECT_EQ(pos.getPieceCode(square), BK);
        }
        else {
            EXPECT_EQ(pos.getPieceCode(square), EMPTY)
                << "Unexpected piece at square " << square;
        }
    }

    EXPECT_EQ(pos.fenSerialization(), secondFen);
}

TEST(PositionTest, LoadFENFailedLoadPreservesPosition) {
    Position pos;

    const std::string originalFen =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    ASSERT_TRUE(pos.loadFEN(originalFen));

    const std::string before = pos.fenSerialization();

    EXPECT_FALSE(pos.loadFEN(
        "4k3/8/8/8/8/8/8/4KX2 b - - 0 1"
    ));

    EXPECT_EQ(pos.fenSerialization(), before);
}

TEST(PositionTest, LoadFENFailedLateValidationPreservesPosition) {
    Position pos;

    const std::string originalFen =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    ASSERT_TRUE(pos.loadFEN(originalFen));

    const std::string before = pos.fenSerialization();

    // Board is valid, but the side field is invalid.
    EXPECT_FALSE(pos.loadFEN(
        "4k3/8/8/8/8/8/8/4K3 x - - 0 1"
    ));

    EXPECT_EQ(pos.fenSerialization(), before);
}


// ============================================================
// 10. FEN SERIALIZATION
// ============================================================

TEST(PositionTest, SerializeDefaultPosition) {
    Position pos;

    EXPECT_EQ(
        pos.fenSerialization(),
        "8/8/8/8/8/8/8/8 w - - 0 1"
    );
}



// ============================================================
// 11. PARAMETERIZED ROUND-TRIP TESTS
// ============================================================

class FENSerializationTest :
    public ::testing::TestWithParam<std::string> {
};

TEST_P(FENSerializationTest, RoundTrip) {
    Position pos;

    const std::string originalFen = GetParam();

    ASSERT_TRUE(pos.loadFEN(originalFen))
        << "Failed to load: " << originalFen;

    EXPECT_EQ(pos.fenSerialization(), originalFen);
}

INSTANTIATE_TEST_SUITE_P(
    FENCases,
    FENSerializationTest,
    ::testing::Values(

        // 1. Standard starting position
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",

        // 2. Kings only
        "4k3/8/8/8/8/8/8/4K3 w - - 0 1",

        // 3. Black to move
        "4k3/8/8/8/8/8/8/4K3 b - - 12 25",

        // 4. Partial castling rights
        "r3k3/8/8/8/8/8/8/4K2R w Kq - 0 1",

        // 5. Valid en-passant target on rank 6
       "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 15",

        // 6. Valid en-passant target on rank 3
        "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1",

        // 7. Nonzero counters
        "4k3/8/8/8/8/8/8/4K3 b - - 99 120",

        // 8. Complex position with all castling rights
        "r3k2r/ppp2ppp/2n1bn2/3qp3/3P4/2N1BN2/PPP2PPP/R2QK2R w KQkq - 4 18",

        // 9. White queenside and black kingside rights
        "r3k2r/8/8/8/8/8/8/R3K3 b Qk - 3 9",

        // 10. Mixed pieces
        "4k3/1p3pp1/2n5/3P4/4B3/8/PPP3P1/4K3 w - - 6 32"
    )
);

TEST(PositionTest, InvalidCastlingRightsIndex) {
    Position pos;

    EXPECT_FALSE(pos.getCastlingRights(-1));
    EXPECT_FALSE(pos.getCastlingRights(4));
    EXPECT_FALSE(pos.getCastlingRights(100));
}

TEST(PositionTest, SetBoardRejectsInvalidPieceCode) {
    Position pos;

    pos.setBoard(A1, WP);
    pos.setBoard(A1, 99);

    EXPECT_EQ(pos.getPieceCode(A1), WP);

    pos.setBoard(B1, -99);

    EXPECT_EQ(pos.getPieceCode(B1), EMPTY);
}

TEST(PositionTest, SetSideToMoveRejectsInvalidColor) {
    Position pos;

    pos.setSideToMove(static_cast<Color>(2));

    EXPECT_EQ(pos.getSideToMove(), WHITE);

    pos.setSideToMove(BLACK);
    pos.setSideToMove(static_cast<Color>(-1));

    EXPECT_EQ(pos.getSideToMove(), BLACK);
}

TEST(PositionTest, LoadFENRejectsNonzeroHalfmoveWithEnPassant) {
    Position pos;

    EXPECT_FALSE(pos.loadFEN(
        "4k3/8/8/4p3/8/8/8/4K3 w - e6 1 1"
    ));

    EXPECT_FALSE(pos.loadFEN(
        "4k3/8/8/8/4P3/8/8/4K3 b - e3 5 1"
    ));
}

TEST(PositionTest, LoadFENAcceptsZeroHalfmoveWithEnPassant) {
    Position pos;

    EXPECT_TRUE(pos.loadFEN(
        "4k3/8/8/4p3/8/8/8/4K3 w - e6 0 1"
    ));

    EXPECT_EQ(pos.getHalfMoveClock(), 0);
    EXPECT_EQ(pos.getEnPassantTargetSquare(), E6);
}
