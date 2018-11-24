#pragma once

#include <string>
#include <mutex>

#include "JSON/json.hpp"
#include "Players/Player.h"

using json = nlohmann::json;

#define BOARD_SIZE 8

class Piece;

class ChessBoard
{
public:
  ChessBoard();
  ~ChessBoard();
  ChessBoard(const std::string board_in[BOARD_SIZE][BOARD_SIZE]);
  ChessBoard(const ChessBoard &board_in);
  void set(int x, int y, Piece *set);
  Piece *get(int x, int y) const;
  bool move(int old_x, int old_y, int new_x, int new_y);
  void get_board(std::string (*board_str)[BOARD_SIZE][BOARD_SIZE]);
  void print_board();
  void print_board_file();
  std::string print_board_list();
  json get_board_json();
  void CheckQueening();
  void get_valid_moves(bool is_white, std::vector<Move> &moves);
  bool get_game_over();

private:
  Piece *board[BOARD_SIZE][BOARD_SIZE];
  std::mutex board_mutex;

};