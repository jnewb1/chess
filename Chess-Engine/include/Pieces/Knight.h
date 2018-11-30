#pragma once

#include "Piece.h"



class Knight : public Piece
{
public:
  Knight(bool is_white, int x, int y);
  virtual bool invalid_move(const PieceMove move, const ChessBoard *board) const;
  std::vector<PieceMove> get_possible_moves() const;
};