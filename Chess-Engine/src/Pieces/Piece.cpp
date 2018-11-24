#include "Pieces/Piece.h"
#include "ChessBoard/ChessBoard.h"

// Moves that are invalid for all pieces
bool Piece::invalid_move_all(const Move move, const ChessBoard *board) const
{

	if (invalid_move_most(move, board)) {
		return true;
	}
	if (invalid_move_no_hop(move, board)) {
		return true;
	}


    return false;
}

bool Piece::invalid_move_no_hop(const Move move, const ChessBoard *board) const {
	// cannot move over non empty squares
	// TODO: This logic does not work entirely correctly!
	int xdir = -sgn(move.current_col - move.new_col);
	int ydir = -sgn(move.current_row - move.new_row);
	int x1 = move.current_col + xdir;
	int y1 = move.current_row + ydir;
	while(x1 != move.new_col || y1 != move.new_row) {
		if (!(board->get(x1, y1)->is_empty())) {
			return true;
		}
		x1 += xdir;
		y1 += ydir;
	}
	return false;
}

// Moves that are invalid for most pieces.
bool Piece::invalid_move_most(const Move move, const ChessBoard *board) const
{
	// If move is outside board, it isn't valid
	if (move.new_col >= BOARD_SIZE || move.new_col < 0 || move.new_row >= BOARD_SIZE || move.new_row < 0)
	{
		return true;
	}

	if (move.new_col == move.current_col && move.new_row == move.current_row) {
		// No movement is not a valid move.
		return true;
	}


	// If move lands on our own piece, it isn't valid
	if (!board->get(move.new_col, move.new_row)->is_empty()) {
		if ((int)board->get(move.new_col, move.new_row)->is_white() == (int)this->is_white())
		{
			return true;
		}
		else {

		}
	}
    return false;
}

std::vector<Move> Piece::get_valid_moves(const ChessBoard *board) const
{
    std::vector<Move> moves = get_possible_moves();
	auto iterator = std::remove_if(moves.begin(), moves.end(), [this, board](Move move) { return invalid_move(move, board); });
	moves.erase(iterator, moves.end());
    return moves;
}