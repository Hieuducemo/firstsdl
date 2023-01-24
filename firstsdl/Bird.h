
#include <SDL.h>
#include <iostream>

#include "Pipe.h"
#include "defs.h"

class Bird
{
private:
    // creat velocity and acceleration while the fish is in action jump or fall
    float velocity;
    float acceleration;
    // A structure that contains the definition of a rectangle, with the origin at the upper left.
    SDL_Rect pos;
    // states of the fish 
    SDL_Texture* up;
    SDL_Texture* down;
    SDL_Texture* mid;
    SDL_Texture* currentRenderingTexture;
    // show the texture on the created windom 
    SDL_Renderer* renderer;

    int animationFrames;

public:
    int score;

    Bird(SDL_Texture* up, SDL_Texture* mid, SDL_Texture* down, SDL_Renderer* renderer);

    void init();
    void render();
    void update(bool jump, float elapsedTime);
    void animation();
    bool collisionDetector(Pipe* pipe);
};
