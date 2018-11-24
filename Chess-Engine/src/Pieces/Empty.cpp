#include "Pieces/Empty.h"

Empty::Empty(int x, int y) : Piece("", x, y, 0)
{
}

bool Empty::invalid_move(const Move move, const ChessBoard *board)  const
{
	return true;
}

std::vector<Move> Empty::get_possible_moves()  const
{
    std::vector<Move> moves(0); //empty spaces cant move!

    return moves;
}