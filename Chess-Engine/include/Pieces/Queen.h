#pragma once

#include "Piece.h"


class Queen : public Piece
{
public:
  Queen(bool is_white, int x, int y);
  virtual bool invalid_move(const PieceMove move, const ChessBoard *board) const;
  std::vector<PieceMove> get_possible_moves() const;
};