#include <SDL2/SDL.h>

#include <iostream>

using std::cerr;
using std::cout;
using std::endl;


SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;


int main ()
{
    if (!SDL_Init (SDL_INIT_EVERYTHING))
    {
        cerr << "SDL failed initializing: " << SDL_GetError () << endl;
        return 1;
    }


    window = SDL_CreateWindow ("SDL test app", SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                1280, 720);

    if (window == nullptr)
    {
        cerr << "Window creation failed: " << SDL_GetError () << endl;
        return 1;
    }

    cout << "SDL initialized.\n";

    delete window;

    SDL_Quit ();

    cout << "SDL shut off.\n";

    return 0;
}
