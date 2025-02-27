#ifndef __SDL_SYSTEMS__
#define __SDL_SYSTEMS__

#include <SDL2/SDL.h>

#include <FunctionPointers.hpp>
#include <Listener.hpp>
#include <Event.hpp>

#ifdef __SDL_USE_RESOURCE_POOL__
    #ifndef __RESOURCE_POOL__
    #include <Pool.hpp>
    #endif
#endif


struct SDL_Color;
struct SDL_Renderer;
struct SDL_Window;

#ifdef __SDL_USE_RESOURCE_POOL__
    class SDLGraphic;
#endif


class SDLEventListener : public Listener
{
    protected:
        virtual void onQuit () = 0;

    public:
        void _Notify () override;
};


class SDLKeyListener : public Listener2P<bool, SDL_Keycode>
{
    protected:
        virtual void onKeyPressed (SDL_Keycode key) = 0;
        virtual void onKeyRelease (SDL_Keycode key) = 0;

    public:
        void _Notify (bool status, SDL_Keycode key) override;
};


class SDLKeyEvent : public Event2P<bool, SDL_Keycode>
{

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

        static SDLKeyEvent onKey;
        static SDLQuitEvent onQuit;
        static FuncPtrP2<bool, SDL_Keycode> onKeyCallback;
        static FuncPtr onQuitCallback;

    #ifdef __SDL_USE_RESOURCE_POOL__
        static Pool<SDLGraphic> graphics;
    #endif

    public:
        static bool Init (const char* windowTitle,
                          int width,
                          int height);

        static void Shutdown ();

        static void ClearWindow ();
        static void CheckForEvents ();
        static SDL_Texture* CreateTextureFrom (SDL_Surface* surface);
        static void DestroySurface (SDL_Surface* surface);
        static void DestroyTexture (SDL_Texture* texture);
        static SDL_Texture* LoadTexture (const char* filePath);
        static void OnKey (SDLKeyListener* listener);
        static void OnKey (FuncPtrP2<bool, SDL_Keycode> callback);
        static void OnQuit (FuncPtr callback);
        static void OnQuit (SDLEventListener* listener);
        static const char* KeyName (SDL_Keycode key);
        static void RefreshWindow ();
        static SDL_Renderer* Renderer ();
        static void SetClearColor (SDL_Color color);
        static SDL_Window* Window ();
};

#endif