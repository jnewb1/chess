#include "Pieces/Bishop.h"
#include "ChessBoard\ChessBoard.h"

Bishop::Bishop(bool is_white, int x, int y) : Piece(is_white ? BISHOP_W : BISHOP_B, x, y, 30)
{
	pos_value = {
		{
		{-2, -1, -1, -1, -1, -1, -1, -2},
		{-1,  0, 0, 0, 0, 0, 0, -1},
		{-1,  0, 0.5, 1, 1, 0.5, 0, -1},
		{-1, 0.5, 0.5, 1, 1, 0.5, 0.5, -1},
		{-1, 0, 1, 1, 1, 1, 0, -1},
		{-1, 1, 1, 1, 1, 1, 1, -1},
		{-1, 0.5, 0, 0, 0, 0, 0.5, -1},
		{-2, -1, -1, -1, -1, -1, -1, -2 }
		}
	};
}

bool Bishop::invalid_move(const PieceMove move, const ChessBoard *board) const
{
    return invalid_move_all(move, board);
}

std::vector<Piece::PieceMove> Bishop::get_possible_moves() const
{
    std::vector<PieceMove> moves(0); //8 possible moves for Bishop

	for (int p = 0; p < 8; p++) {
		moves.push_back(PieceMove({ x - p, y - p }));
		moves.push_back(PieceMove({ x - p, y + p }));
		moves.push_back(PieceMove({ x + p, y - p }));
		moves.push_back(PieceMove({ x + p, y + p }));
	}

    return moves;
}