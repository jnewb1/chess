#include "Pieces/Empty.h"
#include "ChessBoard\ChessBoard.h"

Empty::Empty(int x, int y) : Piece("", x, y, 0)
{
}

bool Empty::invalid_move(const PieceMove move, const ChessBoard *board)  const
{
	return true;
}

std::vector<Piece::PieceMove> Empty::get_possible_moves() const
{
    std::vector<PieceMove> moves(0); //empty spaces cant move!

    return moves;
}