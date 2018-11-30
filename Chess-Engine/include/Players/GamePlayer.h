#pragma once
#include "Player.h"
#include "../JSON/json.hpp"
#include "ChessBoard\ChessBoard.h"

using json = nlohmann::json;

using GameMove = ChessBoard::GameMove;

class GamePlayer : public Player {
public: 
	GamePlayer(bool is_white) : Player(is_white)
	{
	}
	~GamePlayer()
	{
	}
	// Provide interface from the competition class (Player.h) to the inherit interface
	Move request_move(const std::string board_in[BOARD_SIZE][BOARD_SIZE]) {
		ChessBoard board = ChessBoard(board_in);
		GameMove gmove = request_move(board);
		// Convert gamemove to move
		Move move = gamemove_to_move(gmove, board);
		return move;
	}

	// invalid moves just get passed onto move, no special handling currently.
	Move request_move(const std::string board_in[BOARD_SIZE][BOARD_SIZE], const Move *const illegal_move) {
		return request_move(board_in);
	}

	std::string request_queening(const std::string board_in[BOARD_SIZE][BOARD_SIZE]) const {
		ChessBoard board = ChessBoard(board_in);
		return request_queening(board);
	}

	// Utilty to convert gamemove to move for competition
	Move gamemove_to_move(GameMove gmove, const ChessBoard &board) const {
		Move ret;
		ret.current_col = gmove.x;
		ret.current_row = gmove.y;
		ret.new_col = gmove.tx;
		ret.new_row = gmove.ty;
		ret.piece = board.get(gmove.x, gmove.y)->get_piece();
		return ret;
	}

	// Inherit interface for chess engine

	virtual std::string request_queening(const ChessBoard &board) const = 0;

	virtual GameMove request_move(ChessBoard &board) = 0;

	virtual json get_player_debug() const = 0;
protected:
	int valid_move_count;
};