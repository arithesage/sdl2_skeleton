#ifndef __SDL_IMAGE_SUPPORT__
#define __SDL_IMAGE_SUPPORT__


struct SDL_Renderer;
struct SDL_Surface;


class ImageSupport
{
    private:
        static bool ready;
                
    public:
        static void Init (SDL_Renderer* renderer);
        static void Destroy ();
        static bool IsReady ();


        static SDL_Surface* LoadImage (const char* filePath);
};

#endif