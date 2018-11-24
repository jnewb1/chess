#pragma once

#include "Piece.h"

class Empty : public Piece
{
public:
  Empty(int x, int y);
  virtual bool invalid_move(const Move move, const ChessBoard *board)  const;
  std::vector<Move> get_possible_moves()  const;
};