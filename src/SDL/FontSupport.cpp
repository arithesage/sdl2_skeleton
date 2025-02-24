#include <FontSupport.hpp>

#include <SDL2/SDL.h>

#include <Log.hpp>
#include <FilesystemHelpers.hpp>


const char* FontSupport::DEFAULT_FONTS_PATH = "res/fonts/";
const char* FontSupport::DEFAULT_FONT = "Roboto-Regular.ttf";
const int FontSupport::DEFAULT_FONT_SIZE = 16;

TTF_Font* FontSupport::defaultFont = nullptr;
SDL_Renderer* FontSupport::renderer = nullptr;

bool FontSupport::ready = false;
List<const char*> FontSupport::fontsPaths;


void FontSupport::Init (SDL_Renderer* renderer)
{
    if (TTF_Init () < 0)
    {
        Log::ec ("Failed initializing SDL_ttf.", SDL_GetError());
    }
    else
    {
        Log::i ("TrueType font support available.");
        LoadFont ("default", DEFAULT_FONT, DEFAULT_FONT_SIZE);

        ready = true;
    }
}


void FontSupport::Destroy ()
{
    if (IsReady ())
    {
        TTF_Quit ();
    }
}


bool FontSupport::IsReady ()
{
    return ready;
}


void FontSupport::AddFontPath (const char* path)
{
    if (FSHelpers::IsFile (path))
    {
        fontsPaths.push_back (path);

        Log::i ("Added ${0} to font search paths.", {path});
    }
}


TTF_Font* FontSupport::LoadFont (const char* name, 
                                 const char* fontFileName, 
                                 int size)
{
    TTF_Font* loadedFont = nullptr;

    String fullFontPath = FSHelpers::MakePath ({DEFAULT_FONTS_PATH, fontFileName});
    
    if (FSHelpers::IsFile (fullFontPath))
    {
        loadedFont = TTF_OpenFont (fullFontPath.c_str(), size);
        Log::i ("Loaded font '${0}'.", { fullFontPath.c_str() });
    }
    else
    {
        for (const char* path : fontsPaths)
        {
            fullFontPath = FSHelpers::MakePath ({path, fontFileName});

            if (FSHelpers::IsFile (fullFontPath))
            {
                loadedFont = TTF_OpenFont (fullFontPath.c_str(), size);
                Log::i ("Loaded font '${0}'.", { fullFontPath.c_str() });
                break;
            }
        }
    }
        
    return loadedFont;
}