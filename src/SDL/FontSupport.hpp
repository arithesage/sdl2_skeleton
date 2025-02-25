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
        
        /**
         * Loads a font from the resources folder.
         * The default path is 'res/fonts'.
         * You can add more paths for searching.
         * 
         * @param filename The font file name, without path.
         * @param size The size of the loaded font.
         * 
         * @returns A pointer to the loaded font.
         */
        static TTF_Font* LoadFont (const char* fileName, int size);

        /**
         * Loads a font from anywhere.
         * 
         * As opposite with LoadFont function, this one requires
         * the font full path.
         */
        static TTF_Font* LoadExternalFont (const char* filePath, int size);
};

#endif