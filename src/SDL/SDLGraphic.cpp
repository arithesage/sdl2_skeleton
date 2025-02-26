#include <SDLGraphic.hpp>

#include <SDL.hpp>
#include <Log.hpp>


void SDLGraphic::Dispose ()
{
    SDL::DestroyTexture (texture.get());
    SDL::DestroySurface (image);
}


bool SDLGraphic::IsValid ()
{
    return (image != nullptr);
}


SDL_Texture* SDLGraphic::Texture ()
{
    if (texture.get() == nullptr)
    {
        Log::i ("Preparing texture for '${0}'...", { filePath });
        SDL_Texture* loadedTexture = SDL::CreateTextureFrom (image);

        if (loadedTexture != nullptr)
        {
            texture = SharedPtr<SDL_Texture> (loadedTexture);
            Log::i ("Done.");
        }
    }

    return texture.get();
}