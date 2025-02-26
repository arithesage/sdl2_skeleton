#ifndef __SDL_GRAPHIC__
#define __SDL_GRAPHIC__

#include <memory>
#include <Resource.hpp>


template <typename T>
using SharedPtr = std::shared_ptr<T>;


struct SDL_Surface;
struct SDL_Texture;


class SDLGraphic : public Resource
{
    private:
        SDL_Surface* image = nullptr;
        SharedPtr<SDL_Texture> texture = nullptr;

    public:
        SDLGraphic (const char* filePath);

        void Dispose () override;
        bool IsValid () override;

        SDL_Texture* Texture ();
};

#endif