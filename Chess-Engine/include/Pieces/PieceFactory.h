#pragma once

#include "Knight.h"
#include "Pawn.h"
#include "Empty.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"

class PieceFactory
{
  public:
    Piece *Create(std::string type, int x, int y)
    {
        if (type == KNIGHT_B)
        {
            return new Knight(false, x, y);
        }
        if (type == KNIGHT_W)
        {
            return new Knight(true, x, y);
        }
		if (type == PAWN_B)
		{
			return new Pawn(false, x, y);
		}
		if (type == PAWN_W)
		{
			return new Pawn(true, x, y);
		}
		if (type == KING_B)
		{
			return new King(false, x, y);
		}
		if (type == KING_W)
		{
			return new King(true, x, y);
		}
		if (type == ROOK_B)
		{
			return new Rook(false, x, y);
		}
		if (type == ROOK_W)
		{
			return new Rook(true, x, y);
		}
		if (type == BISHOP_B)
		{
			return new Bishop(false, x, y);
		}
		if (type == BISHOP_W)
		{
			return new Bishop(true, x, y);
		}
		if (type == QUEEN_B)
		{
			return new Queen(false, x, y);
		}
		if (type == QUEEN_W)
		{
			return new Queen(true, x, y);
		}
		if (type == "") {
			return new Empty(x, y);
		}
        return nullptr;
    }

	Piece *Create(Piece* in) {
		return Create(in->get_piece(), in->getx(), in->gety());
	}
};
