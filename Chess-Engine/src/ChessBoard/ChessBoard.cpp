#include "ChessBoard/ChessBoard.h"
#include <iostream>
#include <fstream>

#include "Pieces/PieceFactory.h"


ChessBoard::ChessBoard(const ChessBoard &board_in) {
	PieceFactory factory;
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			Piece* piece_in = board_in.get(x, y);
			board[x][y] = factory.Create(piece_in);
		}
	}
}

ChessBoard::ChessBoard()
{
	PieceFactory factory;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            
            board[x][y] = factory.Create("", x, y);
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
	//delete board[x][y];
    board[x][y] = set;
}

Piece *ChessBoard::get(int x, int y) const
{
	return board[x][y];
}

bool ChessBoard::move(int old_x, int old_y, int new_x, int new_y) {
	PieceFactory factory;
	Piece* moving_piece = get(old_x, old_y);
	if (moving_piece->is_empty()) {
		return false;
	}
	moving_piece->set(new_x, new_y);
	//delete board[old_x][old_y];
	set(old_x, old_y, factory.Create("", old_x, old_y));
	delete board[new_x][new_y];
	set(new_x, new_y, moving_piece);
	CheckQueening();
	return true;
}

void ChessBoard::CheckQueening() {
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		if (board[x][7]->get_piece() == PAWN_W) {
			set(x, 7, new Queen(true, x, 7));
		}
		if (board[x][0]->get_piece() == PAWN_B) {
			set(x, 0, new Queen(false, x, 0));
		}
		
	}
}

void ChessBoard::get_valid_moves(bool is_white, std::vector<Move> &moves) {
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
				std::vector<Move> piece_valid_moves = cur_piece->get_valid_moves(this);
				moves.insert(moves.end(), piece_valid_moves.begin(), piece_valid_moves.end());
			}
		}
	}
}

bool ChessBoard::get_game_over()
{
	bool found_b_king = false;
	bool found_w_king = false;
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (get(x, y)->get_piece() == KING_B) {
				found_b_king = true;
			}
			if (get(x, y)->get_piece() == KING_W) {
				found_w_king = true;
			}
			if (found_b_king && found_w_king) {
				return false;
			}
		}
	}
	return true;
}

void ChessBoard::get_board(std::string (*board_str)[BOARD_SIZE][BOARD_SIZE])
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            (*board_str)[x][y] = get(x, y)->get_piece();
        }
    }
}

void ChessBoard::print_board()
{
 
    for (int y = BOARD_SIZE-1; y >= 0; y--)
    {
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			Piece* piece = get(x, y);
			std::string piece_str;
			if (piece->is_empty()) {
				piece_str = " ";
			}
			else{
				piece_str = get(x, y)->get_piece();
			}
			printf("%*s", 2, piece_str.c_str());
            
        }
		std::cout << std::endl;
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

std::string ChessBoard::print_board_list() {
	std::string ret;
	for (int y = BOARD_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (get(x, y)->is_empty()) {
				ret.append(" ,");
			}
			else {
				ret.append(get(x, y)->get_piece() + ",");
			}
			
		}
	}
	ret.pop_back();
	return ret;
}

json ChessBoard::get_board_json() {
	json ret;
	std::vector<std::string> board_list;
	ret["type"] = "board";
	for (int y = BOARD_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			board_list.push_back(board[x][y]->get_piece());
		}
	}
	ret = json(board_list);

	return ret;
}

void ChessBoard::print_board_file() {
	/*
	std::ifstream f("chess_sample.html");
	std::string chessboard_str((std::istreambuf_iterator<char>(f)),
		std::istreambuf_iterator<char>());
	std::string chessboard = "<!--CHESSBOARD-->";
	bool black = false;
	for (int y = BOARD_SIZE - 1; y >= 0; y--)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{

			Piece* piece = get(x, y);
			std::string type;
			if (piece->is_empty()) {
				type = " ";
			}
			else {
				type = get(x, y)->get_piece();
			}
			std::string cur_piece;
			if (type == KNIGHT_B)
			{
				cur_piece = "&#9822;";
			}
			if (type == KNIGHT_W)
			{
				cur_piece = "&#9816;";
			}
			if (type == PAWN_B)
			{
				cur_piece = "&#9823;";
			}
			if (type == PAWN_W)
			{
				cur_piece = "&#9817;";
			}
			if (type == KING_B)
			{
				cur_piece = "&#9818;";
			}
			if (type == KING_W)
			{
				cur_piece = "&#9812;";
			}
			if (type == ROOK_B)
			{
				cur_piece = "&#9820;";
			}
			if (type == ROOK_W)
			{
				cur_piece = "&#9814;";
			}
			if (type == BISHOP_B)
			{
				cur_piece = "&#9821;";
			}
			if (type == BISHOP_W)
			{
				cur_piece = "&#9815;";
			}
			if (type == QUEEN_B)
			{
				cur_piece = "&#9819;";
			}
			if (type == QUEEN_W)
			{
				cur_piece = "&#9813;";
			}
			if (type == "") {
				cur_piece = " ";
			}
			std::string color = (black ? "black" : "white");
			chessboard.append("<div class=\"" + color + "\">" + cur_piece + "</div>");

			black = !black;

		}
		black = !black;
	}
	replaceAll(chessboard_str, "<!--CHESSBOARD-->", chessboard);
	std::ofstream of("chess.html");
	of << chessboard_str;
	*/
}