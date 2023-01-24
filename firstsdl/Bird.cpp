#include "Bird.h"
//first i wanted to demo flappy bird game so i named it was bird, but then i changed image into a fish to make something different. 
void Bird::init()
{
    //the first fish's shape is middle 
    currentRenderingTexture = mid;
    animationFrames = 0;
    score = 0;
// v = 0 , a = 0 
    velocity = 0.0f;
    acceleration = 0.0f;
// started location of the fish
    pos.x = WIDTH / 3 - 32;
    pos.y = HEIGHT / 2;
    pos.w = BIRD_WIDTH;
    pos.h = BIRD_HEIGHT;
}
//creat the fish 
Bird::Bird(SDL_Texture* up, SDL_Texture* mid, SDL_Texture* down, SDL_Renderer* renderer) : up(up), mid(mid), down(down), renderer(renderer)
{
    init();
}

void Bird::update(bool jump, float elapsedTime)
{
    elapsedTime *= 5;
    //when press action key, the fish heading up 
    if (jump)
    {
        acceleration = 0.0f;
        velocity = -GRAVITY;
    }
    else
        //falling down 
    {
        acceleration += GRAVITY * elapsedTime;
    }
// fall till a = g 
    if (acceleration >= GRAVITY)
        acceleration = GRAVITY;
//physic: v = a*t
// s(pos.y) = v*t
    velocity += acceleration * elapsedTime;
    pos.y += velocity * elapsedTime;
}
//working with collision
bool Bird::collisionDetector(Pipe* pipe)
{
    // net
    if (pipe->top_dst.x <= pos.x + pos.w && pipe->top_dst.x + PIPE_WIDTH >= pos.x + pos.w)
        if (pos.y < pipe->top_dst.y + pipe->top_dst.h || pos.y + pos.h > pipe->bottom_dst.y)
            return true;

    // ground
    if (pos.y + pos.h > HEIGHT - GROUND_HEIGHT)
        return true;

    // ceiling
    if (pos.y < 0)
        return true;
// if there is no collision, plus 1 point 
    if (!pipe->passed && pipe->top_dst.x + PIPE_WIDTH < pos.x)
    {
        pipe->passed = true;
        score++;
    }

    return false;
}

void Bird::render()
{
    animation();
//when v = 0 the fish will be his middle state
    if (velocity == 0)
        //these value for state connect with velocity i borrowed from the internet 
        SDL_RenderCopy(renderer, mid, NULL, &pos);
    else if (velocity < 50)
        SDL_RenderCopyEx(renderer, currentRenderingTexture, NULL, &pos, -30.0, NULL, SDL_FLIP_NONE);
    else if (velocity >= 50 && velocity < 200)
        SDL_RenderCopyEx(renderer, currentRenderingTexture, NULL, &pos, 30.0, NULL, SDL_FLIP_NONE);
    else if (velocity >= 200)
        SDL_RenderCopyEx(renderer, mid, NULL, &pos, 90.0, NULL, SDL_FLIP_NONE);

}

void Bird::animation()
{
    animationFrames++;
//making the fish waving 
    if (animationFrames == 5)
        currentRenderingTexture = down;
    else if (animationFrames == 15)
        currentRenderingTexture = mid;
    else if (animationFrames == 20)
    {
        animationFrames = 0;
        currentRenderingTexture = up;
    }
}
