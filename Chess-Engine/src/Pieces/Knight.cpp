#include "Pieces/Knight.h"

Knight::Knight(bool is_white, int x, int y) : Piece(is_white ? KNIGHT_W : KNIGHT_B, x, y, 30)
{
	pos_value = {
		{
		{-5, -4, -3, -3, -3, -3, -4, -5},
		{-4, -2,  0,  0,  0,  0, -2, -4},
		{-3,  0,  1,  1.5,  1.5,  1,  0, -3},
		{-3,  0.5,  1.5,  2,  2,  1.5,  0.5, -3},
		{-3,  0,  1.5,  2,  2,  1.5,  0, -3},
		{-3,  0.5,  1,  1.5,  1.5,  1,  0.5, -3},
		{-4, -2,  0,  0.5,  0.5,  0, -2, -4},
		{-5, -4, -3, -3, -3, -3, -4, -5} 
		}
		};
}

bool Knight::invalid_move(const Move move, const ChessBoard *board)  const
{
    return invalid_move_most(move, board);
}

std::vector<Move> Knight::get_possible_moves()  const
{
    std::vector<Move> moves(0); //8 possible moves for knight

	moves.push_back(Move({ piece, y, x, y + 2, x + 1 }));
	moves.push_back(Move({ piece, y, x, y + 1, x + 2 }));
	moves.push_back(Move({ piece, y, x, y - 1, x + 2 }));
	moves.push_back(Move({ piece, y, x, y - 2, x + 1 }));
	moves.push_back(Move({ piece, y, x, y + 2, x - 1 }));
	moves.push_back(Move({ piece, y, x, y + 1, x - 2 }));
	moves.push_back(Move({ piece, y, x, y - 1, x - 2 }));
	moves.push_back(Move({ piece, y, x, y - 2, x - 1 }));

    return moves;
}