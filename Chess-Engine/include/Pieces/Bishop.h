#pragma once

#include "Piece.h"



class Bishop : public Piece
{
public:
  Bishop(bool is_white, int x, int y);
  virtual bool invalid_move(const Move move, const ChessBoard *board)  const;
  std::vector<Move> get_possible_moves()  const;
};