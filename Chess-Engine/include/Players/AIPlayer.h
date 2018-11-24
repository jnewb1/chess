#pragma once

#include "GamePlayer.h"
#include <atomic>


class AIPlayer : public GamePlayer
{
public:
  AIPlayer(bool is_white) : GamePlayer(is_white){
    
  }
  AIPlayer(bool is_white, int move_time_sec) : move_time_sec(move_time_sec), GamePlayer(is_white) {

  }
  ~AIPlayer()
  {
  }
  Move request_move_thread(int depth, ChessBoard board, std::atomic_bool & stop);
  Move request_move(const std::string[BOARD_SIZE][BOARD_SIZE]);
  Move request_move(const std::string[BOARD_SIZE][BOARD_SIZE], const Move *const illegal_move);
  std::string request_queening(const std::string[BOARD_SIZE][BOARD_SIZE]);
  json get_player_debug();
private:
	int move_time_sec = 60;
	int best_move_score;
	int search_depth;
	int total_moves_evaluated;
	bool move_thread_finished = true;
	bool kill_minimax = false;
};