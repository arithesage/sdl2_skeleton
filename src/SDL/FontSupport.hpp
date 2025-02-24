#ifndef __SDL_FONT_SUPPORT__
#define __SDL_FONT_SUPPORT__

#include <SDL2/SDL_ttf.h>


struct SDL_Renderer;
struct SDL_Texture;


#ifndef __TYPES__
    #include <iostream>
    #include <vector>

    using String = std::string;

    template <typename T>
    using List = std::vector<T>;
#endif


class FontSupport
{
    private:
        static const char* DEFAULT_FONTS_PATH;
        static const char* DEFAULT_FONT;
        static const int DEFAULT_FONT_SIZE;

        static TTF_Font* defaultFont;
        static SDL_Renderer* renderer;

        static bool ready;
        static List<const char*> fontsPaths;

    public:
        static void Init (SDL_Renderer* renderer);        
        static void Destroy ();
        static bool IsReady ();

        static void AddFontPath (const char* path);

        static TTF_Font* LoadFont (const char* name, const char* filePath, int size);
};

#endif