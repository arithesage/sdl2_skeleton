#include <Sprite.hpp>

#include <SDL2/SDL.h>

#include <SDL.hpp>


Sprite::Sprite ()
{
    rect = new SDL_Rect ();
}


Sprite::~Sprite ()
{
    if (rect != nullptr)
    {
        delete rect;
    }

    SDL::DestroyTexture (texture);    
}


void Sprite::SetCoords (int x, int y)
{
    rect->x = x;
    rect->y = y;
}


void Sprite::SetGraphic (SDL_Texture* texture)
{
    if (texture != nullptr)
    {
        this->texture = texture;
    }
}


int Sprite::X ()
{
    return rect->x;
}


int Sprite::Y ()
{
    return rect->y;
}


int Sprite::Width ()
{
    return rect->w;
}


int Sprite::Height ()
{
    return rect->h;
}