#include "Pieces/Piece.h"
#include "ChessBoard/ChessBoard.h"

// Moves that are invalid for all pieces
bool Piece::invalid_move_all(const PieceMove move, const ChessBoard &board) const
{

	if (invalid_move_most(move, board)) {
		return true;
	}
	if (invalid_move_no_hop(move, board)) {
		return true;
	}


    return false;
}

bool Piece::invalid_move_no_hop(const PieceMove move, const ChessBoard &board) const{
	// cannot move over non empty squares
	// TODO: This logic does not work entirely correctly!
	int xdir = -sgn(x - move.x);
	int ydir = -sgn(y - move.y);
	int x1 = x + xdir;
	int y1 = y + ydir;
	while(x1 != move.x || y1 != move.y) {
		if (!(board.get(x1, y1)->is_empty())) {
			return true;
		}
		x1 += xdir;
		y1 += ydir;
	}
	return false;
}

// Moves that are invalid for most pieces.
bool Piece::invalid_move_most(const PieceMove move, const ChessBoard &board) const
{
	// If move is outside board, it isn't valid
	if (move.x >= BOARD_SIZE || move.x < 0 || move.y >= BOARD_SIZE || move.y < 0)
	{
		return true;
	}

	if (x == move.x && y == move.y) {
		// No movement is not a valid move.
		return true;
	}


	// If move lands on our own piece, it isn't valid
	if (!board.get(move.x, move.y)->is_empty()) {
		if ((int)board.get(move.x, move.y)->is_white() == (int)this->is_white())
		{
			return true;
		}
		else {

		}
	}
    return false;
}

std::vector<Piece::PieceMove> Piece::get_valid_moves(const ChessBoard &board) const
{
    std::vector<PieceMove> moves = get_possible_moves();
	auto iterator = std::remove_if(moves.begin(), moves.end(), [this, board](PieceMove &move) { return invalid_move(move, board); });
	moves.erase(iterator, moves.end());
    return moves;
}