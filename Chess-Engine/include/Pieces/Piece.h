#pragma once
class ChessBoard;

#include <array>
#include <vector>
#include <algorithm>
#include <cctype>

#define KING_W "K"
#define QUEEN_W "Q"
#define BISHOP_W "B"
#define KNIGHT_W "KN"
#define ROOK_W "R"
#define PAWN_W "P"

#define KING_B "k"
#define QUEEN_B "q"
#define BISHOP_B "b"
#define KNIGHT_B "kn"
#define ROOK_B "r"
#define PAWN_B "p"


template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}


class Piece
{
public:
	struct PieceMove {
		int x;
		int y;
	};
	Piece(std::string piece_in, int x_in, int y_in, int eval_val_in) : piece(piece_in), x(x_in), y(y_in), eval_value(eval_val_in) {}
	~Piece() {};

	// Invalid Moves for All Pieces
	bool invalid_move_all(const PieceMove move, const ChessBoard *board) const;

	bool invalid_move_no_hop(const PieceMove move, const ChessBoard *board) const;

	// Invalid Moves for Most Pieces
	bool invalid_move_most(const PieceMove move, const ChessBoard *board) const;

	// An override if the move is not legal for all pieces but is legal for this piece
	virtual bool invalid_move(const PieceMove move, const ChessBoard *board) const = 0;

	bool is_white() const
	{
		bool white = std::isupper(piece[0]);
		return white;
	}

	bool is_empty() const {
		if (piece == "") {
			return true;
		}
		return false;
	}

	std::string get_piece() const
	{
		return piece;
	}

	void set(int x_in, int y_in) {
		this->x = x_in;
		this->y = y_in;
	}

	double get_eval() const {
		return eval_value +pos_eval();
	}
	
	double pos_eval() const {
		if (!is_white()) {
			return pos_value[x][7-y];
		}
		return pos_value[x][y];
	}

	int getx() {
		return this->x;
	}
	int gety() {
		return this->y;
	}
  // Get a list of all valid moves this piece could make.
  std::vector<PieceMove> get_valid_moves(const ChessBoard *board) const;

  // Get a list of possible moves this piece could make (not neccesarily valid, ex outside of board bounds)
  virtual std::vector<PieceMove> get_possible_moves() const = 0;

private:

protected:
	std::string piece;
  int x;
  int y;
  int eval_value = 0;
  std::array<std::array<double, 8>, 8> pos_value;
};