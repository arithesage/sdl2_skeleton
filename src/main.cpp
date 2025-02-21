#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

#include <SDL.hpp>

bool running = false;


int main ()
{
    if (SDL::Init ("SDL test app", 1280, 720))
    {
        return 1;
    }

    while (running)
    {
        SDL::ClearWindow ();
        SDL::RefreshWindow ();
    }

    SDL::Shutdown ();

    return 0;
}
