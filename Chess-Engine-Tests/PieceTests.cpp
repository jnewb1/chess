#include "pch.h"
#include "ChessBoard\ChessBoard.h"
#include "Pieces\PieceFactory.h"

TEST(PieceTests, Pawn_basic01) {
	ChessBoard board;
	PieceFactory piece_factory;

	Piece* pawn = piece_factory.Create(pawn_w, 0, 1);
	board.set(0, 1, pawn);

	// A pawn has two possible moves on the opening move.
	EXPECT_EQ(pawn->get_valid_moves(board).size(), 2);

	// Move the pawn one space forward, at which point it only has a single possible move.
	board.move(ChessBoard::GameMove( pawn, 0, 1, board.get(0,2), 0, 2 ));

	// A pawn now only has a single move.
	EXPECT_EQ(pawn->get_valid_moves(board).size(), 1);
}

TEST(PieceTests, King_basic01) {
	ChessBoard board;
	PieceFactory piece_factory;

	Piece* king = piece_factory.Create(king_w, 4, 4);
	board.set(4, 4, king);

	// A king has 8 possible moves when its surroundings are empty
	EXPECT_EQ(king->get_valid_moves(board).size(), 8);
}