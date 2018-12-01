#include "ChessBoard/ChessBoard.h"
#include <iostream>
#include <fstream>




ChessBoard::ChessBoard(const ChessBoard &board_in) {
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			Piece* piece_in = board_in.get(x, y);
			board[x][y] = factory.Create(piece_in);
		}
	}
}

ChessBoard & ChessBoard::operator=(const ChessBoard & other)
{
	if (this != &other) {
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			for (int y = 0; y < BOARD_SIZE; y++)
			{
				Piece* piece_in = other.get(x, y);
				board[x][y] = factory.Create(piece_in);
			}
		}
	}
	return *this;
}

ChessBoard::ChessBoard()
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            
            board[x][y] = factory.Create(empty, x, y);
        }
    }
}

ChessBoard::~ChessBoard() {
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			delete board[x][y];
		}
	}
}

ChessBoard::ChessBoard(const std::string board_in[BOARD_SIZE][BOARD_SIZE])
{
	PieceFactory factory;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
		{
            board[x][y] = factory.Create(board_in[x][y], x, y);
        }
    }
}
void ChessBoard::set(int x, int y, Piece *set)
{
    board[x][y] = set;
}

void ChessBoard::set(Piece *set)
{
	this->set(set->getx(), set->gety(), set);
}

Piece *ChessBoard::get(int x, int y) const
{
	return board[x][y];
}
/*
	Preform a move
		- Moves a piece to its new position
*/
bool ChessBoard::move(GameMove &move) {
	set(move.x, move.y, factory.Create(empty, move.x, move.y));
	set(move.tx, move.ty, move.p);
	move.p->set(move.tx, move.ty);
	CheckQueening();
	return true;
}
/*
	Undo a move.
		- Moves a piece back to its original position
		- Moves the piece that was taken into its original position
*/
bool ChessBoard::undo_move(GameMove &move)
{
	// signal that the move was undone so the piece isn't deleted
	move.undone = true;
	// Delete the empty square we created in the place of the piece
	delete get(move.x, move.y);
	// Move piece to original position
	set(move.x, move.y, move.p);
	move.p->set(move.x, move.y);
	// Move the taken piece back to its position
	set(move.tx, move.ty, move.tp);
	move.tp->set(move.tx, move.ty);
	return false;
}

void ChessBoard::CheckQueening(){
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		if (board[x][7]->get_piece() == pawn_w) {
			set(x, 7, new Queen(true, x, 7));
		}
		if (board[x][0]->get_piece() == pawn_b) {
			set(x, 0, new Queen(false, x, 0));
		}
		
	}
}

void ChessBoard::get_valid_moves(bool is_white, std::vector<GameMove> &moves) const {
	if (get_game_over()) {
		return;
	}
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			Piece *cur_piece = get(x, y);
			if (cur_piece->is_empty()) {
				continue;
			}
			int our_piece1 = cur_piece->is_white();
			int our_piece2 = is_white;
			bool our_piece = (our_piece1 == our_piece2);
			if (our_piece)
			{

				std::vector<Piece::PieceMove> piece_valid_moves = cur_piece->get_valid_moves(*this);
				
				for (auto piece_move : piece_valid_moves) {
					moves.push_back (GameMove(cur_piece, cur_piece->getx(), cur_piece->gety(), get(piece_move.x, piece_move.y), piece_move.x, piece_move.y));
				}
			}
		}
	}
}

bool ChessBoard::get_game_over() const
{
	bool found_b_king = false;
	bool found_w_king = false;
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (get(x, y)->get_piece() == king_b) {
				found_b_king = true;
			}
			if (get(x, y)->get_piece() == king_w) {
				found_w_king = true;
			}
			if (found_b_king && found_w_king) {
				return false;
			}
		}
	}
	return true;
}

bool ChessBoard::get_winner_white() const
{
	bool found_b_king = false;
	bool found_w_king = false;
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (get(x, y)->get_piece() == king_b) {
				found_b_king = true;
			}
			if (get(x, y)->get_piece() == king_w) {
				found_w_king = true;
			}
		}
	}
	return found_w_king && !found_b_king;
}

bool ChessBoard::get_winner_black() const
{
	bool found_b_king = false;
	bool found_w_king = false;
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (get(x, y)->get_piece() == king_b) {
				found_b_king = true;
			}
			if (get(x, y)->get_piece() == king_w) {
				found_w_king = true;
			}
		}
	}
	return !found_w_king && found_b_king;
}

void ChessBoard::get_board(std::string (*board_str)[BOARD_SIZE][BOARD_SIZE]) const
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            (*board_str)[x][y] = get(x, y)->get_piece();
        }
    }
}

bool replaceAll(std::string &s, const std::string &search, const std::string &replace) {
	for (size_t pos = 0; ; pos += replace.length()) {
		// Locate the substring to replace
		pos = s.find(search, pos);
		if (pos == std::string::npos) break;
		// Replace by erasing and inserting
		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
	return false;
}

json ChessBoard::get_board_json() const {
	json ret;
	std::vector<std::string> board_list;
	ret["type"] = "board";
	for (int y = BOARD_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			board_list.push_back(std::string(1, board[x][y]->get_piece()));
		}
	}
	ret = json(board_list);

	return ret;
}