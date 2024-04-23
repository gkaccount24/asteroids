#include "game.h"

game::game():
    Window(nullptr),
    Renderer(nullptr),
    Player(new starship())
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

void game::LoadFont(std::string Key, std::string Path, int PtSize)
{
    if(!Key.empty() && !Path.empty() && PtSize > 0)
    {
        bool Found = Fonts.find(Key) != std::end(Fonts);

        if(!Found)
        {
            if(TTF_Font* FontData = TTF_OpenFont(Path.c_str(), PtSize))
            {
                if(gfont* Font = new gfont(FontData, Path, PtSize))
                {
                    Fonts.insert(std::make_pair(Key, Font));
                }
                else
                {
                    TTF_CloseFont(FontData);

                    FontData = nullptr;
                }
            }
        }
    }
}

void game::LoadTexture(std::string Key, std::string Path, SDL_Renderer* Renderer)
{
    if(!Key.empty() && !Path.empty())
    {
        bool Found = Textures.find(Key) != std::end(Textures);

        if(!Found)
        {
            if(SDL_Surface* Surface = IMG_Load(Path.c_str()))
            {
                if(SDL_Texture* TextureData = SDL_CreateTextureFromSurface(Renderer, Surface))
                {
                    if(texture* Texture = new texture(TextureData, Path, Surface->w, Surface->h))
                    {
                        Textures.insert(std::make_pair(Key, Texture));
                    }
                    else
                    {
                        SDL_DestroyTexture(TextureData);
                        TextureData = nullptr;
                    }
                }

                SDL_FreeSurface(Surface);
                Surface = nullptr;
            }
        }
    }
}

void game::LoadAssets()
{
    LoadFont("PressStart2P-Regular-6", "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 6);
    LoadFont("PressStart2P-Regular-9", "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 9);
    LoadFont("PressStart2P-Regular-12", "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 12);

    LoadTexture("space", "/home/nathan/Documents/code/asteroids/assets/textures/space.png", Renderer);
    LoadTexture("starship", "/home/nathan/Documents/code/asteroids/assets/textures/starship.png", Renderer);
    LoadTexture("ufodark", "/home/nathan/Documents/code/asteroids/assets/textures/ufodark.png", Renderer);
    LoadTexture("asteroid1_grey", "/home/nathan/Documents/code/asteroids/assets/textures/asteroid1_grey.png", Renderer);
    LoadTexture("asteroid2_grey", "/home/nathan/Documents/code/asteroids/assets/textures/asteroid2_grey.png", Renderer);
    LoadTexture("asteroid1_brown", "/home/nathan/Documents/code/asteroids/assets/textures/asteroid1_brown.png", Renderer);
    LoadTexture("asteroid2_brown", "/home/nathan/Documents/code/asteroids/assets/textures/asteroid2_brown.png", Renderer);
    LoadTexture("projectile1", "/home/nathan/Documents/code/asteroids/assets/textures/projectile1.png", Renderer);
    LoadTexture("projectile2", "/home/nathan/Documents/code/asteroids/assets/textures/projectile2.png", Renderer);
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

            switch(Object->GetTypeID())
            {
                case space_object_id::AsteroidGrey1:
                {
                    // do stuff here
                    break;
                }
                case space_object_id::AsteroidGrey2:
                {
                    // do stuff here
                    break;
                }
                case space_object_id::AsteroidBrown1:
                {
                    // do stuff here
                    break;
                }
                case space_object_id::AsteroidBrown2:
                {
                    // do stuff here
                    break;
                }
                case space_object_id::FlagLight:
                {
                    // do stuff here
                    break;
                }
                case space_object_id::FlagDark:
                {
                    // do stuff here
                    break;
                }
                case space_object_id::Projectile1:
                {
                    // do stuff here
                    break;
                }
                case space_object_id::Projectile2:
                {
                    // do stuff here
                    break;
                }
                case space_object_id::Starship:
                {
                    // do stuff here
                    break;
                }
                case space_object_id::UFO:
                {
                    // do stuff here
                    break;
                }
            }
        }
    }
}

int game::Play()
{
    ObjectMap.Insert(starship());
    ObjectMap.Insert(starship());
    ObjectMap.Insert(starship());

    ObjectMap.Remove(2);

    ObjectMap.Insert(starship());
    ObjectMap.Insert(starship());

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