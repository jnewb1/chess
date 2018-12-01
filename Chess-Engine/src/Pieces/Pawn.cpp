#include "Pieces/Pawn.h"
#include "ChessBoard\ChessBoard.h"

Pawn::Pawn(bool is_white, int x, int y) : Piece(is_white ? pawn_w : pawn_b, x, y, 10)
{
	pos_value = { {
		{0,  0,  0,  0,  0,  0,  0,  0},
		{5,  5,  5,  5,  5,  5,  5,  5},
		{1,  1,  2,  3,  3,  2,  1,  1},
		{0.5,  0.5,  1,  2.5,  2.5,  1,  0.5,  0.5},
		{0,  0,  0,  2,  2,  0,  0,  0},
		{0.5, -0.5, -1,  0,  0, -1, -0.5,  0.5},
		{0.5,  1, 1,  -2, -2,  1,  1,  0.5},
		{0, 0, 0, 0, 0, 0, 0, 0}
} };
}

bool Pawn::invalid_move(const PieceMove move, const ChessBoard &board) const
{
	bool invalid = invalid_move_all(move, board);
	if (invalid) {
		return invalid;
	}
	if (x != move.x) {
		// If pawn tries to attack diagonally, there has to be a piece there
		if (board.get(move.x, move.y)->is_empty()) {
			return true;
		}
	}
	else {
		// If pawn tries to move forward, there cannot be a piece there
		if (!board.get(move.x, move.y)->is_empty()) {
			return true;
		}
	}
	return invalid;
}

std::vector<Piece::PieceMove> Pawn::get_possible_moves() const
{
	std::vector<PieceMove> moves(0); //4 possible moves for Pawn
	int dir = is_white() ? 1 : -1;

	moves.push_back(PieceMove({ x  ,   y + dir, }));
	moves.push_back(PieceMove({ x - 1 ,y + dir, }));
	moves.push_back(PieceMove({ x + 1, y + dir, }));

	// Opening move can move two spaces!
	if (y == 1 || y == 6) {
		moves.push_back(PieceMove({ x, y + 2 * dir }));
	}

	return moves;
}