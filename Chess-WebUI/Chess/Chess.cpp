#include "Chess.h"

#include <iostream>
#include <chrono>

#include <cassert>

using namespace std;

#define delay 50

/* 
    Play one chess round (both player moves)
    Return true when game is over
*/
bool Chess::play_one_round()
{
	Move move;
	std::string board_str[BOARD_SIZE][BOARD_SIZE];

	do {
		cout << "Black Player" << endl;
		board->get_board(&board_str);
		move = white->request_move(board_str);
		if (move.piece == "quit") {
			cout << "White Player Resigns..." << endl;
			cout << "Black Player Wins!" << endl;
			UpdateServer();
			return true;
		}
	} while (!preform_move(move, true));
	UpdateServer();
	if (board->get_game_over()) {
		return true;
	}

	do {
		cout << "White Player" << endl;
		board->get_board(&board_str);
		move = black->request_move(board_str);
		if (move.piece == "quit") {
			cout << "Black Player Resigns..." << endl;
			cout << "White Player Wins!" << endl;
			UpdateServer();
			return true;
		}
	} while (!preform_move(move, false));
	UpdateServer();
	if (board->get_game_over()) {
		return true;
	}


	return false;
}

void Chess::UpdateServer() {
	server.UpdateBoard(board);
	server.UpdateDebug(black->get_player_debug(), false);
	server.UpdateDebug(white->get_player_debug(), true);
	server.WaitState(delay);
}

bool Chess::preform_move(Move move, bool is_white)
{
	std::vector<Move> moves;
	board->get_valid_moves(is_white, moves);
	for( auto  move_f : moves){
		if (move_f.current_col == move.current_col && move_f.current_row == move.current_row &&
			move_f.new_col == move.new_col         && move_f.new_row == move.new_row) {
			return board->move(move.current_col, move.current_row, move.new_col, move.new_row);
		}

	}
	return false;
}

void Chess::play_game() {
	UpdateServer();
	while(true) {
		if (play_one_round()) {
			break;

		}
	}
}

void Chess::get_board(std::string(*board_str)[BOARD_SIZE][BOARD_SIZE]) {
	board->get_board(board_str);
}