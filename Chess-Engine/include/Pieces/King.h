#pragma once

#include "Piece.h"



class King : public Piece
{
public:
  King(bool is_white, int x, int y);
  virtual bool invalid_move(const Move move, const ChessBoard *board)  const;
  std::vector<Move> get_possible_moves()  const;
};