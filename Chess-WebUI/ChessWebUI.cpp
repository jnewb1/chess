#include "Chess\Chess.h"
#include "WebUIServer.h"

class ChessWebUI : public Chess{
public:
	ChessWebUI() : Chess(std::bind(&ChessWebUI::OnUpdate, this)) {}

private:
	void OnUpdate() {
		ui.UpdateBoard(board_state);
		ui.UpdateClientsBoard();
		ui.UpdateDebug(white_debug, true);
		ui.UpdateDebug(black_debug, false);
		ui.UpdateClientsDebug();
	}
	WebUIServer ui;
};

int main()
{
	ChessWebUI game;
	game.play_game();
}