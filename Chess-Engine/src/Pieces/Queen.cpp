#include "Pieces/Queen.h"
#include "ChessBoard\ChessBoard.h"

Queen::Queen(bool is_white, int x, int y) : Piece(is_white ? queen_w : queen_b, x, y, 90)
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

bool Queen::invalid_move(const PieceMove move, const ChessBoard &board)  const
{
	return invalid_move_all(move, board);
}

std::vector<Piece::PieceMove> Queen::get_possible_moves() const
{
	std::vector<PieceMove> moves(0); //8 possible moves for Queen

	for (int x1 = -8; x1 < 8; x1++) {
		moves.push_back(PieceMove({ x1, y }));
	}
	for (int y1 = -8; y1 < 8; y1++) {
		moves.push_back(PieceMove({ x ,y1 }));
	}

	for (int p = 0; p < 8; p++) {
		moves.push_back(PieceMove({ x - p, y - p, }));
		moves.push_back(PieceMove({ x + p, y - p, }));
		moves.push_back(PieceMove({ x - p, y + p, }));
		moves.push_back(PieceMove({ x + p, y + p, }));
	}

	return moves;
}