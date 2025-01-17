#pragma once

#include "Piece.h"



class Pawn : public Piece
{
public:
  Pawn(bool is_white, int x, int y);
  virtual bool invalid_move(const PieceMove move, const ChessBoard &board) const;
  std::vector<PieceMove> get_possible_moves() const;
private:
	bool is_first_move = true;
};