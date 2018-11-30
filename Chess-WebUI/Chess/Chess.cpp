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
	UpdateServer();
	do {
		cout << "White Player" << endl;
		board->get_board(&board_str);
		move = white->request_move(board_str);
	} while (!preform_move(move, true));
	UpdateServer();
	if (board->get_game_over()) {
		return true;
	}

	do {
		cout << "Black Player" << endl;
		board->get_board(&board_str);
		move = black->request_move(board_str);
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

bool Chess::preform_move(Move move, bool is_white) {
	return preform_move(GameMove({ board->get(move.current_col, move.current_row), move.current_col, move.current_row, board->get(move.new_col, move.new_row), move.new_col, move.new_row }), is_white);
}

bool Chess::preform_move(GameMove move , bool is_white)
{
	// Preform move checking!
	std::vector<ChessBoard::GameMove> moves;
	board->get_valid_moves(is_white, moves);
	for( auto  move_f : moves){
		if (move_f == move) {
			return board->move(move);
		}
	}
	
	//return board->move(move);
	return false;
}

void Chess::play_game() {
	UpdateServer();
	while(true) {
		if (play_one_round()) {
			cout << "Game Over" << endl;
			break;
		}
	}
}

void Chess::get_board(std::string(*board_str)[BOARD_SIZE][BOARD_SIZE]) {
	board->get_board(board_str);
}