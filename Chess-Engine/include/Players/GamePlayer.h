#pragma once
#include "Player.h"
#include "../JSON/json.hpp"

using json = nlohmann::json;

class ChessBoard;

class GamePlayer : public Player {
public: 
	GamePlayer(bool is_white) : Player(is_white)
	{
	}
	~GamePlayer()
	{
	}

	virtual json get_player_debug() = 0;
protected:
	int valid_move_count;
	ChessBoard * board;

};