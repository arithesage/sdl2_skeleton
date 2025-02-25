#include <ImageSupport.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Log.hpp>
#include <FilesystemHelpers.hpp>


bool ImageSupport::ready = false;


void ImageSupport::Destroy ()
{
    if (IsReady ())
    {
        IMG_Quit ();
    }
}


void ImageSupport::Init (SDL_Renderer* renderer)
{
    if (renderer != nullptr)
    {
        if (IMG_Init (IMG_FORMATS) != IMG_FORMATS)
        {
            Log::ec ("Failed initializing SDL_image.", SDL_GetError());
        }
        else
        {
            Log::i ("Image support available.");
            ready = true;
        }
    }
}


bool ImageSupport::IsReady ()
{
    return ready;
}


SDL_Surface* ImageSupport::LoadImage (const char* filePath)
{
    SDL_Surface* loadedImage = nullptr;

    if (FSHelpers::IsFile (filePath))
    {
        loadedImage = IMG_Load (filePath);

        if (loadedImage == nullptr)
        {
            Log::e ("Failed loading image '${0}'.", { filePath });                
        }
        else
        {
            Log::i ("Loaded image '${0}'.", { filePath });
        }
    }

    return loadedImage;
}