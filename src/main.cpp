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

    SDL::OnQuit ([]() -> void {
        running = false;
    });

    running = true;

    while (running)
    {
        SDL::CheckForEvents ();

        SDL::ClearWindow ();
        SDL::RefreshWindow ();
    }

    SDL::Shutdown ();

    return 0;
}
