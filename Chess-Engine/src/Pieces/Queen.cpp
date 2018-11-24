#include "Pieces/Queen.h"

Queen::Queen(bool is_white, int x, int y) : Piece(is_white ? QUEEN_W : QUEEN_B, x, y, 90)
{
	pos_value = { {
				{-2, -1, -1, -0.5, -0.5, -1, -1, -2},
	{-1,  0,  0,  0,  0,  0,  0, -1},
	{-1,  0,  0.5,  0.5,  0.5,  0.5,  0, -1},
	{-0.5,  0,  0.5,  0.5,  0.5,  0.5,  0, -0.5},
	{0,  0,  0.5,  0.5,  0.5,  0.5,  0, -0.5},
	{-1,  0.5,  0.5,  0.5,  0.5,  0.5,  0, -1},
	{-1,  0,  0.5,  0,  0,  0,  0, -1},
{-2, -1, -1, -0.5, -0.5, -1, -1, -2}

} };
}

bool Queen::invalid_move(const Move move, const ChessBoard *board)  const
{
    return invalid_move_all(move, board);
}

std::vector<Move> Queen::get_possible_moves()  const
{
    std::vector<Move> moves(0); //8 possible moves for Queen

	for (int x1 = -8; x1 < 8; x1++) {
		moves.push_back(Move({ piece, y, x, y, x1 }));
	}
	for (int y1 = -8; y1 < 8; y1++) {
		moves.push_back(Move({ piece, y, x, y1, x }));
	}

	for (int p = 0; p < 8; p++) {
		moves.push_back(Move({ piece, y, x, y - p, x - p }));
		moves.push_back(Move({ piece, y, x, y - p, x + p }));
		moves.push_back(Move({ piece, y, x, y + p, x - p }));
		moves.push_back(Move({ piece, y, x, y + p, x + p }));
	}

    return moves;
}