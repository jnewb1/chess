#pragma once

#include "GamePlayer.h"
#include "WebSocketServer.h"
#include "WebServer.h"


class WebPlayer : public GamePlayer
{
public:
	void Event(std::string msg);

	WebPlayer(bool is_white) : GamePlayer(is_white),  wss(new WebSocketServer(9090, std::bind(&WebPlayer::Event, this, std::placeholders::_1))) {
	}
	~WebPlayer()
	{
	}

	virtual std::string request_queening(const ChessBoard &board) const;
	virtual GameMove request_move(ChessBoard &board);
	virtual json get_player_debug() const;
private:
	WebSocketServer *wss;
	bool move_ready = false;
	ChessBoard::GameMove cur_move;
	ChessBoard board;
};

