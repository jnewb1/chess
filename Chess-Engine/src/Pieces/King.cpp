#include "Pieces/King.h"

King::King(bool is_white, int x, int y) : Piece(is_white ? KING_W : KING_B, x, y, 9000)
{
	pos_value = { {

				{-3, -4, -4, -5, -5, -4, -4, -3},
	{-3, -4, -4, -5, -5, -4, -4, -3},
	{-3, -4, -4, -5, -5, -4, -4, -3},
	{-3, -4, -4, -5, -5, -4, -4, -3},
	{-2, -3, -3, -4, -4, -3, -3, -2},
	{-1, -2, -2, -2, -2, -2, -2, -1},
	{2,  2,  0,  0,  0,  0,  2,  2},
{2, 3, 1, 0, 0, 1, 3, 2}
} };
}

bool King::invalid_move(const Move move, const ChessBoard *board)  const
{
    return invalid_move_all(move, board);
}

std::vector<Move> King::get_possible_moves()  const
{
    std::vector<Move> moves(0); //8 possible moves for King

	moves.push_back(Move({ piece, y, x, y - 1, x - 1 }));
	moves.push_back(Move({ piece, y, x, y - 1, x     }));
	moves.push_back(Move({ piece, y, x, y - 1, x + 1 }));
	moves.push_back(Move({ piece, y, x, y    , x - 1 }));
	moves.push_back(Move({ piece, y, x, y    , x + 1 }));
	moves.push_back(Move({ piece, y, x, y + 1, x - 1 }));
	moves.push_back(Move({ piece, y, x, y + 1, x     }));
	moves.push_back(Move({ piece, y, x, y + 1, x + 1 }));

    return moves;
}