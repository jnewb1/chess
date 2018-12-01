#pragma once

#include "ChessBoard/ChessBoard.h"
#include "Players/PlayerFactory.h"

#include "ChessBoard/BoardDefinitions.h"

class Chess
{
public:
  Chess(std::function<void()> on_update_in) : on_update(on_update_in)
  {
    std::string board_in[BOARD_SIZE][BOARD_SIZE];
    board_default(board_in);
    board = new ChessBoard(board_in);

    black = factory.Create("AI_Fast", false);
    white = factory.Create("Web", true);
  }
  bool play_one_round();
  void play_game();
  void get_board(std::string(*board_str)[BOARD_SIZE][BOARD_SIZE]);
  bool preform_move(ChessBoard::GameMove move, bool is_white);
  void GameStateUpdate();

  bool preform_move(Move move, bool is_white);

protected:
	ChessBoard board_state;
	json white_debug;
	json black_debug;
private:
  std::function<void()> on_update;
  ChessBoard *board;
  GamePlayer* black;
  GamePlayer* white;

  PlayerFactory factory;
};