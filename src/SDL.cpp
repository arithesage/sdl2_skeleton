#include <SDL.hpp>

#include <Log.hpp>


void SDLEventListener::_Notify ()
{
    onQuit ();
}


void SDLKeyListener::_Notify (bool status, SDL_Keycode key)
{
    if (status == true)
    {
        onKeyPressed (key);
    }
    else
    {
        onKeyRelease (key);
    }
}




SDL_Event SDL::event;

SDLKeyEvent SDL::onKey;
SDLQuitEvent SDL::onQuit;
FuncPtrP1<SDL_Keycode> SDL::onKeyUpCallback = nullptr;
FuncPtr SDL::onQuitCallback = nullptr;
SDL_Renderer* SDL::renderer = nullptr;
SDL_Window* SDL::window = nullptr;


bool SDL::Init (const char* windowTitle,
                int width,
                int height)
{
    if (SDL_Init (SDL_INIT_EVERYTHING) < 0)
    {
        Log::ec ("Failed initializing SDL.", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow (
        windowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        Log::ec ("Failed creating window.", SDL_GetError ());
        return false;
    }

    renderer = SDL_CreateRenderer (
        window, 
        -1,
        SDL_RENDERER_ACCELERATED | 
        SDL_RENDERER_PRESENTVSYNC |
        SDL_RENDERER_TARGETTEXTURE
    );

    if (renderer == nullptr)
    {
        Log::ec ("Failed creating renderer.", SDL_GetError ());
        return false;
    }

    return true;
}


void SDL::Shutdown ()
{
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    SDL_Quit ();
}


void SDL::ClearWindow ()
{
    SDL_RenderClear (renderer);
}


void SDL::CheckForEvents ()
{
    SDL_PollEvent (&event);

    if (event.type == SDL_QUIT)
    {
        if (onQuitCallback != nullptr)
        {
            onQuitCallback ();
        }

        onQuit.Fire ();
    }

    if (event.type == SDL_KEYUP)
    {
        if (onKeyUpCallback != nullptr)
        {
            onKeyUpCallback (event.key.keysym.sym);
        }

        //onKeyUp.Fire (event.key.keysim.sym);
    }
}


void SDL::OnKeyUp (FuncPtrP1<SDL_Keycode> callback)
{
    if (callback != nullptr)
    {
        onKeyUpCallback = callback;
    }
}


void SDL::OnQuit (FuncPtr callback)
{
    if (callback != nullptr)
    {
        onQuitCallback = callback;
    }
}


void SDL::OnQuit (SDLEventListener* listener)
{
    if (listener != nullptr)
    {
        onQuit.Subscribe (listener);
    }
}


const char* SDL::KeyName (SDL_Keycode key)
{
    return SDL_GetKeyName (key);
}


void SDL::RefreshWindow ()
{
    SDL_RenderPresent (renderer);
}


SDL_Renderer* SDL::Renderer ()
{
    return renderer;
}


void SDL::SetClearColor (SDL_Color color)
{
    SDL_SetRenderDrawColor (renderer, color.r, color.g, color.b, color.a);
}


SDL_Window* SDL::Window ()
{
    return window;
}
