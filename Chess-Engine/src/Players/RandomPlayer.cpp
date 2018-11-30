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
GameMove RandomPlayer::request_move(ChessBoard &board)
{
	std::vector<GameMove> moves(0);
	board.get_valid_moves(this->get_is_white(), moves);

	valid_move_count = moves.size();
    
	if (moves.size() < 1) {
		return GameMove();
	}
    return random_element(moves);
}

//send back a string as defined by the macros above for the what the pawn should become
//can be a queen, bishop, knight or rook
std::string RandomPlayer::request_queening(const ChessBoard &board) const
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

json RandomPlayer::get_player_debug() const {
	json ret;
	ret["valid_move_count"] = valid_move_count;
	return ret;
}