#ifndef __SDL_SPRITE__
#define __SDL_SPRITE__

struct SDL_Rect;
struct SDL_Texture;


/**
 * A sprite is anything 2D you can draw
 */
class Sprite
{
    protected:
        SDL_Rect* rect = nullptr;
        SDL_Texture* texture = nullptr;

    public:
        Sprite ();
        ~Sprite ();

        void SetCoords (int x, int y);
        void SetGraphic (SDL_Texture* texture);

        int X ();
        int Y ();
        
        int Width ();
        int Height ();
};

#endif