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
  Move request_move(const std::string[BOARD_SIZE][BOARD_SIZE]);
  Move request_move(const std::string[BOARD_SIZE][BOARD_SIZE], const Move *const illegal_move);
  std::string request_queening(const std::string[BOARD_SIZE][BOARD_SIZE]);
  json get_player_debug();
};