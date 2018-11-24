#include "Players/WebPlayer.h"
#include "Pieces/Piece.h"

Move WebPlayer::request_move(const std::string board_in[BOARD_SIZE][BOARD_SIZE])
{
	move_ready = false;
	board = new ChessBoard(board_in);
	while (!move_ready) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	move_ready = false;
	cur_move.piece = board_in[cur_move.current_col][cur_move.current_row];

	return cur_move;
}



Move WebPlayer::request_move(const std::string board_in[BOARD_SIZE][BOARD_SIZE], const Move *const illegal_move)
{

	return request_move(board_in);
}

static json moves_to_json(std::vector<Move> &moves) {
	json ret;
	for (auto move : moves) {
		json move_json;
		move_json["cur_x"] = move.current_col;
		move_json["cur_y"] = move.current_row;
		move_json["new_x"] = move.new_col;
		move_json["new_y"] = move.new_row;
		ret.push_back(move_json);

	}
	return ret;
}


// Handle new event from webserver
void WebPlayer::Event(std::string msg) {
	json recieve = json::parse(msg);
	if (recieve["type"] == "get_moves") {
		json send;
		send["type"] = "get_move_data";
		std::vector<Move> moves;

		int x = recieve["data"]["cur_x"];
		int y = recieve["data"]["cur_y"];
		if (board) {
			moves = board->get(x, y)->get_valid_moves(board);

		}

		send["data"] = moves_to_json(moves);
		wss->send_msg(send.dump());
	}
	if (recieve["type"] == "send_move") {
		json move_json = json::parse(msg);
		int x, y, nx, ny;

		x = move_json["data"]["cur_x"];
		y = move_json["data"]["cur_y"];
		nx = move_json["data"]["new_x"];
		ny = move_json["data"]["new_y"];
		cur_move = Move({ " ", y, x, ny, nx });
		move_ready = true;
	}
}

json WebPlayer::get_player_debug() {
	json ret;
	return ret;
}