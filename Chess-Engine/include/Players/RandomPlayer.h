#pragma once

#include "GamePlayer.h"


class RandomPlayer : public GamePlayer
{
public:
  RandomPlayer(bool is_white) : GamePlayer(is_white)
  {
  }
  ~RandomPlayer()
  {
  }
  virtual std::string request_queening(const ChessBoard &board) const;
  virtual GameMove request_move(ChessBoard &board);
  virtual json get_player_debug() const;
  json get_player_debug();
};