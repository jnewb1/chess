#include "Players/RandomPlayer.h"
#include "ChessBoard/ChessBoard.h"
#include "Pieces/Piece.h"

#include <random>
#include <iterator>
#include <ctime>

template <typename I>
I random_element(std::vector<I> v)
{
	srand(time(NULL));
	return v[rand() % v.size()];
}

//0,0 is the bottom left of the board
//White always starts at the bottom of the board
Move RandomPlayer::request_move(const std::string board_in[BOARD_SIZE][BOARD_SIZE])
{
    ChessBoard *board = new ChessBoard(board_in);
	std::vector<Move> moves(0);
	board->get_valid_moves(this->get_is_white(), moves);

	valid_move_count = moves.size();
    
	if (moves.size() < 1) {
		return Move({ "quit", 0, 0, 0, 0 });
	}
	delete board;
    return random_element(moves);

}

//Prev move was illegal, request new move
Move RandomPlayer::request_move(const std::string board_in[BOARD_SIZE][BOARD_SIZE], const Move *const illegal_move)
{
    return request_move(board_in);
}

//send back a string as defined by the macros above for the what the pawn should become
//can be a queen, bishop, knight or rook
std::string RandomPlayer::request_queening(const std::string[BOARD_SIZE][BOARD_SIZE])
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

json RandomPlayer::get_player_debug() {
	json ret;
	ret["valid_move_count"] = valid_move_count;
	return ret;
}