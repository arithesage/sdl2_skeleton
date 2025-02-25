#ifndef __SDL_GRAPHIC__
#define __SDL_GRAPHIC__

#include <Resource.hpp>


struct SDL_Surface;
struct SDL_Texture;


class SDLGraphic : public Resource
{
    private:
        SDL_Surface* surface = nullptr;
        SDL_Texture* texture = nullptr;

    public:
        SDLGraphic (const char* filePath);

        void Dispose () override;
        bool IsValid () override;        
};

#endif