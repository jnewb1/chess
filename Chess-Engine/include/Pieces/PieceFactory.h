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
    Piece *Create(char type, int x, int y)
    {
        if (type == knight_b)
        {
            return new Knight(false, x, y);
        }
        if (type == knight_w)
        {
            return new Knight(true, x, y);
        }
		if (type == pawn_b)
		{
			return new Pawn(false, x, y);
		}
		if (type == pawn_w)
		{
			return new Pawn(true, x, y);
		}
		if (type == king_b)
		{
			return new King(false, x, y);
		}
		if (type == king_w)
		{
			return new King(true, x, y);
		}
		if (type == rook_b)
		{
			return new Rook(false, x, y);
		}
		if (type == rook_w)
		{
			return new Rook(true, x, y);
		}
		if (type == bishop_b)
		{
			return new Bishop(false, x, y);
		}
		if (type == bishop_w)
		{
			return new Bishop(true, x, y);
		}
		if (type == queen_b)
		{
			return new Queen(false, x, y);
		}
		if (type == queen_w)
		{
			return new Queen(true, x, y);
		}
		if (type == empty) {
			return new Empty(x, y);
		}
        return nullptr;
    }

	Piece *Create(Piece* in) {
		return Create(in->get_piece(), in->getx(), in->gety());
	}

	Piece *Create(const std::string &in, int x, int y) {
		if (in.length() > 1) {
			if (in == KNIGHT_B) {
				return Create(knight_b, x, y);
			}
			if (in == KNIGHT_W) {
				return Create(knight_w, x, y);
			}
		}
		return Create(in[0], x, y);
	}
};
