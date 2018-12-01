#include "Players/LiChessPlayer.h"
#include "ChessBoard/ChessBoard.h"
#include "Pieces/Piece.h"

// Wait until we have a match from lichess
void LiChessPlayer::find_match() {



	match_found = true;
}

GameMove LiChessPlayer::get_move(const ChessBoard &board) {
	
}

GameMove LiChessPlayer::uci_to_gamemove(const std::string &move, const ChessBoard &board) {
	if (move.length() != 4) {
		throw std::exception("invalid_uci");
	}
	char cstart_x = move[0];
	char cstart_y = move[1];
	char cend_x = move[2];
	char cend_y = move[3];

	uint8_t start_x = cstart_x - 97;
	uint8_t start_y = cstart_y - 48;
	uint8_t end_x = cend_x - 97;
	uint8_t end_y = cend_y - 48;

	return GameMove(board.get(start_x, start_y), start_x, start_y, board.get(end_x, end_y), end_x, end_y);
}

//0,0 is the bottom left of the board
//White always starts at the bottom of the board
GameMove LiChessPlayer::request_move(ChessBoard &board)
{
	// We don't have a match on LiChess yet, get a new match.
	if (!match_found) {
		find_match();
	}
	// We already have a match, so wait for lichess move.
	return get_move();
}

//send back a string as defined by the macros above for the what the pawn should become
//can be a queen, bishop, knight or rook
std::string LiChessPlayer::request_queening(const ChessBoard &board) const
{

}

json LiChessPlayer::get_player_debug() const {

}