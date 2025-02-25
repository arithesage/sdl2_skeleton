#include <SDLGraphic.hpp>

#include <SDL.hpp>


void SDLGraphic::Dispose ()
{
    SDL::DestroyTexture (texture);
    SDL::DestroySurface (surface);
}


bool SDLGraphic::IsValid ()
{
    return (surface != nullptr);
}