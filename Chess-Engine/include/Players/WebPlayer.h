#pragma once

#include "GamePlayer.h"
#include "WebSocketServer.h"
#include "WebServer.h"


class WebPlayer : public GamePlayer
{
public:
	void Event(std::string msg);

	WebPlayer(bool is_white) : GamePlayer(is_white),  wss(new WebSocketServer(9090, std::bind(&WebPlayer::Event, this, std::placeholders::_1))) {
		board = nullptr;
	}
	~WebPlayer()
	{
	}

	Move request_move(const std::string[BOARD_SIZE][BOARD_SIZE]);
	Move request_move(const std::string board_in[BOARD_SIZE][BOARD_SIZE], const Move * const illegal_move);
	std::string request_queening(const std::string[BOARD_SIZE][BOARD_SIZE]);
	json get_player_debug();
private:
	WebSocketServer *wss;
	bool move_ready = false;
	Move cur_move;
};

