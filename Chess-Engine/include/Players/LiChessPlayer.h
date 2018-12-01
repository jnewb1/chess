#pragma once
#pragma once

#include "GamePlayer.h"
#include "WebAPI.h"


class LiChessPlayer : public GamePlayer
{
public:
	LiChessPlayer(bool is_white) : GamePlayer(is_white) {
	}
	~LiChessPlayer()
	{
	}

	virtual std::string request_queening(const ChessBoard &board) const;
	virtual GameMove request_move(ChessBoard &board);
	virtual json get_player_debug() const;

	void find_match();
	GameMove uci_to_gamemove(const std::string &move, const ChessBoard &board);
	GameMove get_move(const ChessBoard &board);
private:
	bool match_found = false;
	std::string lichess_api_key = "ZIG2W5D6vPZbMfuX";
	WebAPI api_client;
};

