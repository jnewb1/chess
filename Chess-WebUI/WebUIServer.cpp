#include "ChessBoard\ChessBoard.h"
#include "WebUIServer.h"

WebUIServer::WebUIServer() : board(new ChessBoard()), ws(new WebServer(80, "./WebInterface")), wss(new WebSocketServer(8080,
																								std::bind(&WebUIServer::Event, this, std::placeholders::_1))) {

}

WebUIServer::~WebUIServer() {
	
}

// Handle new event from webserver
void WebUIServer::Event(std::string msg) {
	if (msg == "play") {
		game_state = Running;
	}
	if (msg == "pause") {
		game_state = Paused;
	}
	if (msg == "step") {
		game_state = Step;
	}
}

// Update local board data copy
void WebUIServer::UpdateBoard(const ChessBoard& board_in) {
	board_mutex.lock();
	board = &board_in;
	board_mutex.unlock();
	UpdateClientsBoard();
}

// Sends board update to all clients
void WebUIServer::UpdateClientsBoard() {
	board_mutex.lock();
	json send;
	send["type"] = "board";
	send["board"] = board->get_board_json();
	wss->send_msg(send.dump());
	board_mutex.unlock();
}

// Update local debug data copy
void WebUIServer::UpdateDebug(const json &debug, bool is_white) {
	if (is_white) {
		white_debug["debug"] = debug;
	}
	else {
		black_debug["debug"] = debug;
	}
	UpdateClientsDebug();
}

// Sends debug update to all clients
void WebUIServer::UpdateClientsDebug() {
	json send;
	send["type"] = "debug";
	send["whitedebug"] = white_debug;
	send["blackdebug"] = black_debug;
	wss->send_msg(send.dump());
}

void WebUIServer::WaitState(int min_delay) {
	std::this_thread::sleep_for(std::chrono::milliseconds(min_delay));
	while (game_state != Running) {
		if (game_state == Step) {
			game_state = Paused;
			return;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		UpdateClientsBoard();
	}
}