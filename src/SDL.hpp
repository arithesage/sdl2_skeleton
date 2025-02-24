#ifndef __SDL_SYSTEMS__
#define __SDL_SYSTEMS__

#include <SDL2/SDL.h>

#include <FunctionPointers.hpp>
#include <Listener.hpp>
#include <Event.hpp>

struct SDL_Color;
struct SDL_Renderer;
struct SDL_Window;


class SDLEventListener : public Listener
{
    protected:
        virtual void onQuit () = 0;

    public:
        void _Notify () override;
};


class SDLQuitEvent : public Event
{

};




class SDL
{
    private:
        static SDL_Event event;
        static SDL_Renderer* renderer;
        static SDL_Window* window;

        static SDLQuitEvent onQuit;
        static FuncPtr onQuitCallback;

    public:
        static bool Init (const char* windowTitle,
                          int width,
                          int height);

        static void Shutdown ();

        static void ClearWindow ();
        static void CheckForEvents ();
        static void OnQuit (FuncPtr callback);
        static void OnQuit (SDLEventListener* listener);
        static void RefreshWindow ();
        static SDL_Renderer* Renderer ();
        static void SetClearColor (SDL_Color color);
        static SDL_Window* Window ();
};

#endif