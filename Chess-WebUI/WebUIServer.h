#pragma once
#include "WebSocketServer.h"
#include "WebServer.h"
#include <string>
#include <mutex>

class WebUIServer {
public:
	WebUIServer();
	~WebUIServer();

	void UpdateBoard(const ChessBoard& board_in);
	void UpdateClientsBoard();
	void UpdateDebug(const json &debug, bool is_white);
	void UpdateClientsDebug();
	void WaitState(int min_delay);

	void Event(std::string);
private:
	const ChessBoard *board;
	WebSocketServer *wss;
	WebServer *ws;

	json white_debug;
	json black_debug;

	uint8_t game_state = Running;

	std::mutex board_mutex;

	static enum game_states {
		Paused,  // Game Paused
		Running, // Game Running
		Step     // Game Paused but Step Requested
	};
};