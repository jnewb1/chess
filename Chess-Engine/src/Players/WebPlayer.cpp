#include "Players/WebPlayer.h"
#include "Pieces/Piece.h"

GameMove WebPlayer::request_move(ChessBoard &board)
{
	this->board = ChessBoard(board);
	move_ready = false;
	while (!move_ready) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	move_ready = false;

	return cur_move;
}

static json moves_to_json(std::vector<GameMove> &moves) {
	json ret;
	for (auto GameMove : moves) {
		json move_json;
		move_json["cur_x"] = GameMove.x;
		move_json["cur_y"] = GameMove.y;
		move_json["new_x"] = GameMove.tx;
		move_json["new_y"] = GameMove.ty;
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
		std::vector<ChessBoard::GameMove> moves;

		int x = recieve["data"]["cur_x"];
		int y = recieve["data"]["cur_y"];

		std::vector<Piece::PieceMove> pmoves = board.get(x, y)->get_valid_moves(board);
		for (auto pmove : pmoves) {
			moves.push_back(GameMove({ board.get(x, y), x, y, board.get(pmove.x, pmove.y), pmove.x, pmove.y }));
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
		cur_move = GameMove({board.get(x, y), x, y, board.get(nx, ny), nx, ny});
		move_ready = true;
	}
}

std::string WebPlayer::request_queening(const ChessBoard &board) const
{
	if (get_is_white())
	{
		return QUEEN_W;
	}
	else
	{
		return QUEEN_B;
	}
}

json WebPlayer::get_player_debug() const{
	json ret;
	return ret;
}