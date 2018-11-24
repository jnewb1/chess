#pragma once

#include "AIPlayer.h"
#include "RandomPlayer.h"
#include "WebPlayer.h"

class PlayerFactory
{
  public:
    GamePlayer *Create(std::string type, bool is_white)
    {
        if (type == "AI")
        {
            return new AIPlayer(is_white);
        }
		if (type == "AI_Fast")
		{
			return new AIPlayer(is_white, 10);
		}
        if (type == "Random")
        {
            return new RandomPlayer(is_white);
        }
		if (type == "Web") {
			return new WebPlayer(is_white);
		}
        return nullptr;
    }
};
