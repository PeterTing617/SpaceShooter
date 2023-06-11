#include "Game.h"

int main()
{
    Game* game = Game::sharedInstance();
    game->run();

    return 0;
};
