#include "Game.h"
#include "defs.h"
#undef main

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
//creat a new windom with the name flabby fish and with the given width and height in defs.h
    Game game("Flappy fish", WIDTH, HEIGHT);

    game.Start();
    
    return 0;
}
