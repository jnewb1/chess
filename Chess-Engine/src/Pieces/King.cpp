#include "Pieces/King.h"
#include "ChessBoard\ChessBoard.h"

King::King(bool is_white, int x, int y) : Piece(is_white ?  king_w : king_b, x, y, 9000)
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

bool King::invalid_move(const PieceMove move, const ChessBoard &board)  const
{
    return invalid_move_all(move, board);
}

std::vector<Piece::PieceMove> King::get_possible_moves() const
{
    std::vector<PieceMove> moves(0); //8 possible moves for King

	moves.push_back(PieceMove({ x - 1, y - 1 }));
	moves.push_back(PieceMove({ x - 1, y     }));
	moves.push_back(PieceMove({ x - 1, y + 1 }));
	moves.push_back(PieceMove({ x    , y - 1 }));
	moves.push_back(PieceMove({ x    , y + 1 }));
	moves.push_back(PieceMove({ x + 1, y - 1 }));
	moves.push_back(PieceMove({ x + 1, y     }));
	moves.push_back(PieceMove({ x + 1, y + 1 }));

    return moves;
}