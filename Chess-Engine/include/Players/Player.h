#pragma once

#include <string>

#define BOARD_SIZE 8

#define KING_W "K"
#define QUEEN_W "Q"
#define BISHOP_W "B"
#define KNIGHT_W "KN"
#define ROOK_W "R"
#define PAWN_W "P"

#define KING_B "k"
#define QUEEN_B "q"
#define BISHOP_B "b"
#define KNIGHT_B "kn"
#define ROOK_B "r"
#define PAWN_B "p"

struct Move
{
	std::string piece;

	int current_row;
	int current_col;

	int new_row;
	int new_col;
};

class Player
{
  public:
	Player(bool is_white);
	~Player();

	//0,0 is the bottom left of the board
	//White always starts at the bottom of the board
	virtual Move request_move(const std::string[BOARD_SIZE][BOARD_SIZE]) = 0;

	//Prev ChessBoard::GameMove was illegal, request new ChessBoard::GameMove
	virtual Move request_move(const std::string[BOARD_SIZE][BOARD_SIZE], const Move *const illegal_move) = 0;

	//send back a string as defined by the macros above for the what the pawn should become
	//can be a queen, bishop, knight or rook
	std::string request_queening(const std::string[BOARD_SIZE][BOARD_SIZE]);

	bool get_is_white() const
	{
		return is_white;
	}

  private:
	bool is_white = false;
};

//You have 1 minute to make return a ChessBoard::GameMove, or else you lose automatically
