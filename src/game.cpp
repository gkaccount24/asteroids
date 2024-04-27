#include "game.h"

game::game():
    Window(nullptr)
{ }

game::~game()
{
    Renderer.Destroy();

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

    if(!Renderer.Create(Window))
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to make game renderer."     << std::endl;

        return false;
    }

    return true;
}

void game::LoadAssets()
{
    asset_loader Loader(Renderer);

    Loader.LoadFont(font_id::PressStart2P_Regular_9, AssetMap, "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 9);
    Loader.LoadFont(font_id::PressStart2P_Regular_12, AssetMap, "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 12);
    Loader.LoadFont(font_id::PressStart2P_Regular_24, AssetMap, "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 24);

    Loader.LoadTexture(texture_id::AsteroidGrey1, AssetMap, "/home/nathan/Documents/code/asteroids/assets/textures/asteroid1_grey.png");
    Loader.LoadTexture(texture_id::AsteroidGrey2, AssetMap, "/home/nathan/Documents/code/asteroids/assets/textures/asteroid2_grey.png");
    Loader.LoadTexture(texture_id::AsteroidBrown1, AssetMap, "/home/nathan/Documents/code/asteroids/assets/textures/asteroid1_brown.png");
    Loader.LoadTexture(texture_id::AsteroidBrown2, AssetMap, "/home/nathan/Documents/code/asteroids/assets/textures/asteroid2_brown.png");
    Loader.LoadTexture(texture_id::FlagLight, AssetMap, "/home/nathan/Documents/code/asteroids/assets/textures/flag.png");
    Loader.LoadTexture(texture_id::FlagDark, AssetMap, "/home/nathan/Documents/code/asteroids/assets/textures/flagdark.png");
    Loader.LoadTexture(texture_id::Projectile1, AssetMap, "/home/nathan/Documents/code/asteroids/assets/textures/projectile1.png");
    Loader.LoadTexture(texture_id::Projectile2, AssetMap, "/home/nathan/Documents/code/asteroids/assets/textures/projectile2.png");
    Loader.LoadTexture(texture_id::Starship, AssetMap, "/home/nathan/Documents/code/asteroids/assets/textures/starship.png");
    Loader.LoadTexture(texture_id::UFO, AssetMap, "/home/nathan/Documents/code/asteroids/assets/textures/ufodark.png");
}

void game::Destroy()
{
    ObjectMap.Destroy();
    AssetMap.Destroy();
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
    LoadAssets();

    int WindowWidth = 0;

    SDL_GetWindowSize(Window, &WindowWidth, nullptr);

    for(uint32_t RowIdx = 0; RowIdx < 3; RowIdx++)
    {
        for(uint32_t ColIdx = 0; ColIdx < (WindowWidth / 128); ColIdx++)
        {
            ObjectMap.Insert(starship((ColIdx + 1) * 128, 128, 128, 128));
        }
    }

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

        Renderer.ClearScreen();

        DrawObjects();

        Renderer.SwapBuffers();
    }

    Destroy();

    return EXIT_SUCCESS;
}