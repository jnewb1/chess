#pragma once

#include <string>
#include <mutex>

#include "JSON/json.hpp"
#include "Players/Player.h"

#include "Pieces/PieceFactory.h"

using json = nlohmann::json;

#define BOARD_SIZE 8

class Piece;

class ChessBoard
{
public:
	class GameMove {
	public:
		friend class ChessBoard;
		GameMove(Piece* pi, int xi, int yi, Piece* tpi, int txi, int tyi) : p(pi), x(xi), y(yi), tp(tpi), tx(txi), ty(tyi) {

		}
		GameMove(Piece* pi, int xi, int yi, int txi, int tyi) : GameMove(pi, xi, yi, nullptr, txi, tyi) {

		}
		GameMove(Piece* pi, Piece* tpi) : GameMove(pi, pi->getx(), pi->gety(), tpi, tpi->getx(), tpi->gety()) {

		}
		GameMove() : GameMove(nullptr, 0, 0, nullptr, 0, 0) {}
		~GameMove() {
			if (!undone) {
					//delete tp;
			}
		}

		bool operator==(const GameMove& rhs) const{
			return x == rhs.x && y == rhs.y && tx == rhs.tx && ty == rhs.ty;
		}
		int x;
		int y;

		int tx;
		int ty;
	private:
		// Piece to be moved, and its current x,y location
		Piece* p;

		// Piece to be taken, and its current x,y location (if its empty it doesn't really matter)
		Piece* tp;


		// Move was undone, so we shouldn't delete the taken piece.
		bool undone = false;


	};
  ChessBoard();
  ~ChessBoard();
  ChessBoard(const std::string board_in[BOARD_SIZE][BOARD_SIZE]);
  ChessBoard(const ChessBoard &board_in);
  ChessBoard& operator=(const ChessBoard& other);
  void set(int x, int y, Piece *set);
  void set(Piece * set);
  Piece *get(int x, int y) const;
  bool move(GameMove &move);
  bool undo_move(GameMove &move);
  void get_board(std::string (*board_str)[BOARD_SIZE][BOARD_SIZE]) const;
  json get_board_json() const;
  void CheckQueening();
  void get_valid_moves(bool is_white, std::vector<GameMove> &moves) const;
  bool get_game_over() const;
  bool get_winner_white() const;
  bool get_winner_black() const;

private:
  Piece *board[BOARD_SIZE][BOARD_SIZE];
  std::mutex board_mutex;
  PieceFactory factory;
};