#include <Terminal.hpp>

// Needed for reading keycodes
#include <SDL2/SDL.h>

#include <SDL.hpp>
#include <FontSupport.hpp>
#include <ImageSupport.hpp>

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

    SDL::OnKey ([](bool pressed, SDL_Keycode key) -> void {
        if (pressed)
        {
            cout << "Pressing ";
        }
        else
        {
            cout << "Released ";
        }

        cout << SDL::KeyName (key) << "." << endl;
    });


    FontSupport::Init (SDL::Renderer ());
    ImageSupport::Init (SDL::Renderer ());
    
    SDL_Surface* img = ImageSupport::LoadImage ("res/img/coin.png");

    if (img != nullptr)
    {
        SDL::DestroySurface (img);
    }

    running = true;

    while (running)
    {
        SDL::CheckForEvents ();

        SDL::ClearWindow ();
        SDL::RefreshWindow ();
    }

    if (FontSupport::IsReady ())
    {
        FontSupport::Destroy ();
    }
    
    if (ImageSupport::IsReady ())
    {
        ImageSupport::Destroy ();
    
    }

    SDL::Shutdown ();

    return 0;
}
