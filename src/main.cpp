#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

// Needed for reading keycodes
#include <SDL2/SDL.h>

#include <SDL.hpp>


bool running = false;


int main ()
{
    if (!SDL::Init ("SDL test app", 1280, 720))
    {
        return 1;
    }

    SDL::OnQuit ([]() -> void {
        running = false;
    });

    SDL::OnKeyUp ([](SDL_Keycode key) -> void {
        cout << "Released " << SDL::KeyName (key) << "." << endl;
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
