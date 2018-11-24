#include "Pieces/Pawn.h"

Pawn::Pawn(bool is_white, int x, int y) : Piece(is_white ? PAWN_W : PAWN_B, x, y, 10)
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

bool Pawn::invalid_move(const Move move, const ChessBoard *board) const
{
	bool invalid = invalid_move_all(move, board);
	if (invalid) {
		return invalid;
	}
	if (move.current_col != move.new_col) {
		// If pawn tries to attack diagonally, there has to be a piece there
		if (board->get(move.new_col, move.new_row)->is_empty()) {
			return true;
		}
	}
	else {
		// If pawn tries to move forward, there cannot be a piece there
		if (!board->get(move.new_col, move.new_row)->is_empty()) {
			return true;
		}
	}
	return invalid;
}

std::vector<Move> Pawn::get_possible_moves() const
{
	std::vector<Move> moves(0); //1 possible moves for Pawn (typical)
	int dir = is_white() ? 1 : -1;

	moves.push_back(Move({piece, y, x, y+dir,   x }));
	moves.push_back(Move({ piece, y, x, y + dir,   x-1 }));
	moves.push_back(Move({ piece, y, x, y + dir,   x + 1 }));

	// Opening move can move two spaces!
	if (y == 1 || y == 6) {
		moves.push_back(Move({ piece, y, x, y + 2*dir,   x }));
	}

    return moves;
}