#include "Pieces/Rook.h"

Rook::Rook(bool is_white, int x, int y) : Piece(is_white ? ROOK_W : ROOK_B, x, y, 50)
{
	pos_value = { {
				{0,  0,  0,  0,  0,  0,  0,  0},
	{0.5,  1,  1,  1,  1,  1,  1,  0.5},
	{-0.5,  0,  0,  0,  0,  0,  0, -0.5},
	{-0.5,  0,  0,  0,  0,  0,  0, -0.5},
	{-0.5,  0,  0,  0,  0,  0,  0, -0.5},
	{-0.5,  0,  0,  0,  0,  0,  0, -0.5},
	{-0.5,  0,  0,  0,  0,  0,  0, -0.5},
{0, 0, 0, 0.5, 0.5, 0, 0, 0}

} };
}

bool Rook::invalid_move(const Move move, const ChessBoard *board)  const
{
    return invalid_move_all(move, board);
}

std::vector<Move> Rook::get_possible_moves()  const
{
    std::vector<Move> moves(0); //8 possible moves for Rook
	for (int x1 = -8; x1 < 8; x1++) {
		moves.push_back(Move({ piece, y, x, y, x1 }));
	}
	for (int y1 = -8; y1 < 8; y1++) {
		moves.push_back(Move({ piece, y, x, y1, x }));
	}

    return moves;
}