#include "ChessBoard/BoardDefinitions.h"

void board_default(std::string board[BOARD_SIZE][BOARD_SIZE])
{
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			board[x][y] = "";
		}
	}
	
	board[0][0] = ROOK_W;
	board[7][0] = ROOK_W;
	
	board[0][7] = ROOK_B;
	board[7][7] = ROOK_B;

	board[1][0] = KNIGHT_W;
	board[6][0] = KNIGHT_W;

	board[1][7] = KNIGHT_B;
	board[6][7] = KNIGHT_B;

	board[4][0] = KING_W;
	board[4][7] = KING_B;

	board[3][0] = QUEEN_W;
	board[3][7] = QUEEN_B;

	board[2][0] = BISHOP_W;
	board[5][0] = BISHOP_W;

	board[2][7] = BISHOP_B;
	board[5][7] = BISHOP_B;
	
	board[0][1] = PAWN_W;
	board[1][1] = PAWN_W;
	board[2][1] = PAWN_W;
	board[3][1] = PAWN_W;
	board[4][1] = PAWN_W;
	board[5][1] = PAWN_W;
	board[6][1] = PAWN_W;
	board[7][1] = PAWN_W;
	
	board[0][6] = PAWN_B;
	board[1][6] = PAWN_B;
	board[2][6] = PAWN_B;
	board[3][6] = PAWN_B;
	board[4][6] = PAWN_B;
	board[5][6] = PAWN_B;
	board[6][6] = PAWN_B;
	board[7][6] = PAWN_B;
	
	

}