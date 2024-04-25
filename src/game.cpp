#include "game.h"

game::game():
    Window(nullptr),
    Renderer(nullptr)
{ }

game::~game()
{
    if(Renderer)
    {
        SDL_DestroyRenderer(Renderer);

        Renderer = nullptr;
    }

    if(Window)
    {
        SDL_DestroyWindow(Window);

        Window = nullptr;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool game::InitSDL() 
{
    int Result = 0;

    Result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    if(!IsGood(Result))
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to initialize library: SDL" << std::endl;

        return false;
    }

    int Flags = IMG_INIT_JPG | IMG_INIT_PNG;

    Result = IMG_Init(Flags);

    if((Result & Flags) != Flags)
    {
        std::cout << "Error Message: " << IMG_GetError()       << std::endl;
        std::cout << "failed to initialize library: SDL_image" << std::endl;

        return false;
    }

    Result = TTF_Init();

    if(!IsGood(Result))
    {
        std::cout << "Error Message: " << TTF_GetError()     << std::endl;
        std::cout << "failed to initialize library: SDL_ttf" << std::endl;

        return false;
    }

    Window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, 
                                                    SDL_WINDOWPOS_UNDEFINED, 
                                                    1024, 768, SDL_WINDOW_SHOWN);
    
    if(!Window)
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to make game window."       << std::endl;

        return false;
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    if(!Renderer)
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to make game renderer."     << std::endl;

        return false;
    }

    return true;
}

void game::ClearScreen()
{
    Uint8 RValue = 0; // Map.Background.r;
    Uint8 GValue = 0; // Map.Background.g;
    Uint8 BValue = 0; // Map.Background.b;

    Uint8 Opacity = SDL_ALPHA_OPAQUE;

    SDL_SetRenderDrawColor(Renderer, RValue, GValue, BValue, Opacity);
    SDL_RenderClear(Renderer);
}

void game::DrawObjects()
{
    if(!ObjectMap.IsEmpty())
    {
        uint32_t ObjectCount = ObjectMap.Size();

        for(uint32_t Idx = 0; Idx < ObjectCount; Idx++)
        {
            space_object* Object = ObjectMap.At(Idx);

        }
    }
}

int game::Play()
{
    ObjectMap.Insert(starship(100, 100, 128, 128));
    ObjectMap.Insert(starship(300, 300, 128, 128));

    bool Playing = true;

    while(Playing)
    {
        SDL_Event Evt { };

        while(SDL_PollEvent(&Evt))
        {
            if(Evt.type == SDL_QUIT)
            {
                std::cout << "received quit event" << std::endl;

                Playing = false;
            }
        }

        ClearScreen();
        DrawObjects();

        SDL_RenderPresent(Renderer);
    }

    return EXIT_SUCCESS;
}