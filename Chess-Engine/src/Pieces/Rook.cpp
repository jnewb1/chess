#include "Pieces/Rook.h"
#include "ChessBoard\ChessBoard.h"

Rook::Rook(bool is_white, int x, int y) : Piece(is_white ? rook_w : rook_b, x, y, 50)
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

bool Rook::invalid_move(const PieceMove move, const ChessBoard &board)  const
{
    return invalid_move_all(move, board);
}

std::vector<Piece::PieceMove> Rook::get_possible_moves() const
{
    std::vector<PieceMove> moves(0); //8 possible moves for Rook
	for (int x1 = -8; x1 < 8; x1++) {
		moves.push_back(PieceMove({ x1, y }));
	}
	for (int y1 = -8; y1 < 8; y1++) {
		moves.push_back(PieceMove({ x, y1 }));
	}

    return moves;
}