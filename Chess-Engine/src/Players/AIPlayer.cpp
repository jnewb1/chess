#include "Players/AIPlayer.h"
#include "ChessBoard/ChessBoard.h"
#include "Pieces/Piece.h"

#include <vector>
#include <future>
#include <iostream>


int evaluate_board(const ChessBoard &board) {
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

int minimax(int depth, int orig_depth, ChessBoard board, bool isMaximisingPlayer, Move &final_move, int alpha, int beta, std::atomic_bool & stop) {
	if (stop) {
		throw std::runtime_error("timeout");
	}
	
	if (depth == 0) {
		int score = evaluate_board(board);
		return score;
	}
	std::vector<Move> moves(0);
	board.get_valid_moves(isMaximisingPlayer, moves);

	if (moves.size() == 0 && depth == orig_depth) {
		//No valid moves... we have to quit :(
		final_move = Move({ "quit", 0, 0, 0, 0 });
		return 0;
	}
	if (moves.size() == 0) {
		return evaluate_board(board);
	}

	//Maximizing Player
	if (isMaximisingPlayer) {
		int bestMoveScore = -99999999;
		for (auto move : moves) {
			ChessBoard board2 = board;
			// Make move and evaluate it
			board2.move(move.current_col, move.current_row, move.new_col, move.new_row);
			int score = minimax(depth - 1, orig_depth, board2, !isMaximisingPlayer, final_move, alpha, beta, stop);
			if (score > bestMoveScore) {
				bestMoveScore = score;
				if (depth == orig_depth) {
					final_move = move;
				}
			}
			// UNDOING MOVES DOES NOT WORK. IT WILL NOT BRING BACK PIECES THAT HAVE BEEN OVERWRITEEN
			// Undo Move
			alpha = std::max(alpha, bestMoveScore);
			if (beta <= alpha) {
				break;
			}
		}
		return bestMoveScore;

	}
	//Minimizing Player
	else {
		int bestMoveScore = 99999999;
		for (auto move : moves) {
			ChessBoard board2 = board;
			// Make move and evaluate it
			board2.move(move.current_col, move.current_row, move.new_col, move.new_row);
			int score = minimax(depth - 1, orig_depth, board2, !isMaximisingPlayer, final_move, alpha, beta, stop);
			if (score < bestMoveScore) {
				bestMoveScore = score;
				if (depth == orig_depth) {
					final_move = move;
				}
			}
			// UNDOING MOVES DOES NOT WORK. IT WILL NOT BRING BACK PIECES THAT HAVE BEEN OVERWRITEEN
			// Undo Move
			beta = std::min(beta, bestMoveScore);
			if (beta <= alpha) {
				break;
			}
		}
		return bestMoveScore;
	}
}

Move AIPlayer::request_move_thread(int depth, ChessBoard board, std::atomic_bool & stop) {
	Move move ={ "quit", 0,0,0,0 };
	int alpha = -9999999;
	int beta = 9999999;
	int score = minimax(depth, depth, board, get_is_white(), move, alpha, beta, stop);
	best_move_score = score;
	return move;
}

//0,0 is the bottom left of the board
//White always starts at the bottom of the board
Move AIPlayer::request_move(const std::string board_in[BOARD_SIZE][BOARD_SIZE])
{
	int move_time = move_time_sec;
	auto t_start = std::chrono::high_resolution_clock::now();

	ChessBoard board = ChessBoard(board_in);
	//Move move = request_move_thread(4, *board);

	Move cur_move;
	int cur_depth = 1;

	std::atomic_bool quit_thread = false;
	while(true) {

		std::future<Move> move = std::async(std::launch::async, &AIPlayer::request_move_thread, this, cur_depth, board, std::ref(quit_thread));
		auto t_end = std::chrono::high_resolution_clock::now();
		double remaining_sec = move_time-std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(t_end - t_start)).count();

		if (move.wait_for(std::chrono::seconds(1)*(remaining_sec - 2)) == std::future_status::timeout)
		{
			quit_thread = true;
			try
			{
				cur_move = move.get();
			}
			catch (const std::runtime_error & ex)
			{
				
			}
			break;
		}
		else {
			cur_move = move.get();
		}

		cur_depth++;
		
	}
	search_depth = cur_depth;

	return cur_move;
}

//Prev move was illegal, request new move
Move AIPlayer::request_move(const std::string board_in[BOARD_SIZE][BOARD_SIZE], const Move *const illegal_move)
{
    return request_move(board_in);
}

//send back a string as defined by the macros above for the what the pawn should become
//can be a queen, bishop, knight or rook
std::string AIPlayer::request_queening(const std::string[BOARD_SIZE][BOARD_SIZE])
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

json AIPlayer::get_player_debug() {
	json ret;
	ret["best_move_score"] = best_move_score;
	ret["search_depth"] = search_depth;
	return ret;
}