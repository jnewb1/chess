#include "Players/Player.h"

Player::Player(bool is_white)
{
    this->is_white = is_white;
}
Player::~Player()
{
}



std::string Player::request_queening(const std::string[BOARD_SIZE][BOARD_SIZE])
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