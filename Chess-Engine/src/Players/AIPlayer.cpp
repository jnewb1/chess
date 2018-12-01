#include "Players/AIPlayer.h"
#include "ChessBoard/ChessBoard.h"
#include "Pieces/Piece.h"

#include <vector>
#include <future>
#include <iostream>


int evaluate_board(const ChessBoard &board, bool is_white) {
	double boardValue = 0;
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			Piece *cur_piece = board.get(x, y);
			if (cur_piece->is_empty()) {
				continue;
			}
			//white is maximizing player, if piece is white, add the value, if black, add the negative value.
			double piece_val = cur_piece->get_eval() * (cur_piece->is_white() ? 1 : -1);
			boardValue += piece_val;
		}
	}
	return boardValue;
}

int minimax(int depth, int orig_depth, ChessBoard &board, bool isMaximisingPlayer, GameMove &final_move, int alpha, int beta, const std::atomic_bool & stop) {
	if (stop) {
		throw std::runtime_error("timeout");
	}
	if (depth == 0) {
		return evaluate_board(board, isMaximisingPlayer);
	}
	std::vector<GameMove> moves(0);
	board.get_valid_moves(isMaximisingPlayer, moves);

	//Maximizing Player
	if (isMaximisingPlayer) {
		int bestMoveScore = -1000000;
		for (auto move : moves) {
			// Make move and evaluate it
			board.move(move);

			int score = minimax(depth - 1, orig_depth, board, !isMaximisingPlayer, final_move, alpha, beta, stop);
			if (score > bestMoveScore) {
				bestMoveScore = score;
				if (depth == orig_depth) {
					final_move = move;
				}
			}
			// UNDO MOVE HERE - create a gamemove struct with piece taking and piece moving with x and y
			board.undo_move(move);
			alpha = std::max(alpha, bestMoveScore);
			if (beta <= alpha) {
				break;
			}
		}
		return bestMoveScore;

	}
	//Minimizing Player
	else {
		int bestMoveScore = 1000000;
		for (auto move : moves) {
			// Make move and evaluate it
			board.move(move);
			int score = minimax(depth - 1, orig_depth, board, !isMaximisingPlayer, final_move, alpha, beta, stop);
			if (score < bestMoveScore) {
				bestMoveScore = score;
				if (depth == orig_depth) {
					final_move = move;
				}
			}
			// UNDO MOVE HERE
			board.undo_move(move);
			beta = std::min(beta, bestMoveScore);
			if (beta <= alpha) {
				break;
			}
		}
		return bestMoveScore;
	}
}

std::pair<GameMove, int> AIPlayer::request_move_thread(int depth, ChessBoard &board, const std::atomic_bool & stop) {
	GameMove final_move;
	int alpha = -1000000;
	int beta   = 1000000;
	ChessBoard board2(board);

	int score = minimax(depth, depth, board2, get_is_white(), final_move, alpha, beta, stop);
	if (stop) {
		score = -999;
	}
	return std::pair<GameMove, int>(final_move, score);
}

//0,0 is the bottom left of the board
//White always starts at the bottom of the board
GameMove AIPlayer::request_move(ChessBoard &board)
{
	int move_time = move_time_sec;
	auto t_start = std::chrono::high_resolution_clock::now();

	GameMove cur_move;
	int cur_depth = 2;

	std::atomic_bool quit_thread = false;
	while(true) {

		std::future<std::pair<GameMove, int>> move = std::async(std::launch::async, &AIPlayer::request_move_thread, this, cur_depth, std::ref(board), std::ref(quit_thread));
		auto t_end = std::chrono::high_resolution_clock::now();
		double remaining_sec = move_time-std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(t_end - t_start)).count();

		if (move.wait_for(std::chrono::seconds(1)*(remaining_sec - 2)) == std::future_status::timeout)
		{
			quit_thread = true;
			break;
		}
		else {
			std::pair<GameMove, int> move_info = move.get();
			cur_move = move_info.first;
			best_move_score = move_info.second;
		}

		cur_depth+=2;
		
	}
	search_depth = cur_depth;

	return cur_move;
}

//send back a string as defined by the macros above for the what the pawn should become
//can be a queen, bishop, knight or rook
std::string AIPlayer::request_queening(const ChessBoard &board) const
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

json AIPlayer::get_player_debug() const {
	json ret;
	ret["best_move_score"] = best_move_score;
	ret["search_depth"] = search_depth;
	return ret;
}