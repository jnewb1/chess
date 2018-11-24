#pragma once

#include "ChessBoard/ChessBoard.h"
#include "Players/PlayerFactory.h"
#include "../GameServer.h"


#include "ChessBoard/BoardDefinitions.h"

class Chess
{
public:
  Chess()
  {
    std::string board_in[BOARD_SIZE][BOARD_SIZE];
    board_default(board_in);
    board = new ChessBoard(board_in);
    PlayerFactory factory;
    black = factory.Create("AI_Fast", false);
    white = factory.Create("AI_Fast", true);
  }
  bool play_one_round();
  void play_game();
  void get_board(std::string(*board_str)[BOARD_SIZE][BOARD_SIZE]);
  bool preform_move(Move move, bool is_white);
  void UpdateServer();

private:

  ChessBoard *board;
  GameServer server;
  GamePlayer* black;
  GamePlayer* white;
};