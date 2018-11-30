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
  std::pair<GameMove, int> request_move_thread(int depth, ChessBoard &board, const std::atomic_bool & stop);
  virtual std::string request_queening(const ChessBoard &board) const;
  virtual GameMove request_move(ChessBoard &board);
  virtual json get_player_debug() const;
private:
	int move_time_sec = 60;
	int best_move_score;
	int search_depth;
	int total_moves_evaluated;
	bool move_thread_finished = true;
	bool kill_minimax = false;
};