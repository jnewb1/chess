#include "pch.h"
#include "Players/AIPlayer.h"



TEST(AIPlayerTests, basic_take_king01) {
	ChessBoard board;
	PieceFactory piece_factory;

	// A queen which can take the opponents king
	Piece* queenw = piece_factory.Create(queen_w, 0, 0);
	board.set(queenw);
	Piece* kingb = piece_factory.Create(king_b, 0, 5);
	board.set(kingb);
	Piece* kingw = piece_factory.Create(king_w, 7, 0);
	board.set(kingw);


	// Create an white AI with 10 seconds to think
	AIPlayer player(true, 10);

	// Optimal move is for the queen to take the king
	GameMove optimal_move( queenw, kingb );

	GameMove player_move = player.request_move(board);

	EXPECT_EQ(optimal_move, player_move);
}

TEST(AIPlayerTests, basic_take_king02) {
	ChessBoard board;
	PieceFactory piece_factory;

	// A bishop which can take the opponents king
	Piece* bishopw = piece_factory.Create(bishop_w, 5, 0);
	board.set(bishopw);
	Piece* kingb = piece_factory.Create(king_b, 0, 5);
	board.set(kingb);
	Piece* kingw = piece_factory.Create(king_w, 0, 0);
	board.set(kingw);

	// Create an white AI with 10 seconds to think
	AIPlayer player(true, 10);

	// Optimal move is for the bishop to take the king
	GameMove optimal_move(bishopw, kingb);

	GameMove player_move = player.request_move(board);

	EXPECT_EQ(optimal_move, player_move);
}

TEST(AIPlayerTests, basic_take_king03) {
	ChessBoard board;
	PieceFactory piece_factory;

	// A bishop which can take the oppponents king
	Piece* bishopw = piece_factory.Create(bishop_w, 4, 3);
	board.set(bishopw);
	Piece* kingb = piece_factory.Create(king_b, 0, 7);
	board.set(kingb);

	// White's king is also in check by a rook
	Piece* rookb = piece_factory.Create(rook_b, 2, 0);
	board.set(rookb);
	Piece* kingw = piece_factory.Create(king_w, 5, 0);
	board.set(kingw);

	// Create an white AI with 10 seconds to think
	AIPlayer player(true, 10);

	// Optimal move is for the bishop to take the king
	// Even if white is in check, it can still win by taking the king.
	GameMove optimal_move(bishopw, kingb);

	GameMove player_move = player.request_move(board);

	EXPECT_EQ(optimal_move, player_move);
}