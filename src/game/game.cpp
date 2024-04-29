#include "game.h"

static float MaxPlayerVelocity;
static float PlayerVelocity;

#define DEFAULT_PLAYER_VELOCITY 1.0f
#define DEFAULT_MAX_PLAYER_VELOCITY 2.0f

game::game():
    Window(nullptr),
    Player(nullptr)
{
    MaxPlayerVelocity = DEFAULT_PLAYER_VELOCITY;
    PlayerVelocity = DEFAULT_MAX_PLAYER_VELOCITY;
}

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
    DestroyPlayer();

    ObjectMap.Destroy();
    AssetMap.Destroy();
}

void game::DrawPlayer()
{
    if(Player)
    {
        if(Player->Starship)
        {
            uint32_t TextureID = Player->Starship->TextureID;
            game_texture* Texture = (game_texture*) AssetMap.Get(TextureID);

            Renderer.DrawTexture(Texture, Player->Starship);
        }
    }
}

void game::DrawObjects()
{
    if(!ObjectMap.Empty())
    {
        uint32_t ObjectCount = ObjectMap.Size();

        for(uint32_t Idx = 0; Idx < ObjectCount; Idx++)
        {

            // Renderer.DrawTexture(Texture, Object);
        }
    }
}

uint32_t game::SaveObject(game_object* Object)
{
    uint32_t WorldID = ObjectMap.Add(Object);

    return WorldID;
}

ship* game::MakeShip(uint32_t AssetID, 
                     int ShipX, int ShipY,
                     int ShipW, int ShipH,
                     float BaseSpeed,
                     float MaxSpeed)
{
    ship* Ship = ship::Make(AssetID, ShipX, ShipY,
                            ShipW, ShipH, BaseSpeed, 
                            MaxSpeed);
    if(Ship && Save)
    {
        uint32_t WorldID = SaveObject(Ship);

        Ship->SetWorldID(WorldID);
    }

    return Ship;
}

void game::DestroyPlayer()
{
    if(Player)
    {
        delete Player;

        Player = nullptr;
    }
}

void game::MakePlayer()
{
    DestroyPlayer();
}

void game::Update(float Dt)
{
    // std::cout << "dt: " << Dt << std::endl;

    SDL_Event Evt { };

    while(SDL_PollEvent(&Evt))
    {
        if(Evt.type == SDL_QUIT)
        {
            std::cout << "received quit event" << std::endl;

            Playing = false;
        }
        else if(Evt.type == SDL_KEYUP)
        {
            switch(Evt.key.keysym.sym)
            {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                case SDLK_DOWN:
                case SDLK_UP:
                {
                    // set playing moving state
                    // Player->Starship->Moving;

                } break;
            }
        }
        else if(Evt.type == SDL_KEYDOWN)
        {
            switch(Evt.key.keysym.sym)
            {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                case SDLK_DOWN:
                case SDLK_UP:
                {
                    // set playing moving state
                    // Player->Starship->Moving;

                } break;
            }
        }
    }

    GameKeys = SDL_GetKeyboardState(nullptr);

    UpdatePlayer(Dt);
}

void game::UpdatePlayer(float Dt)
{
    bool LeftKeyPressed = GameKeys[SDL_SCANCODE_LEFT] > 0;
    bool RightKeyPressed = GameKeys[SDL_SCANCODE_RIGHT] > 0;
    bool UpKeyPressed = GameKeys[SDL_SCANCODE_UP] > 0;
    bool DownKeyPressed = GameKeys[SDL_SCANCODE_DOWN] > 0;

    if(LeftKeyPressed) { }
    // {
    //     // Player->Starship->Rotate(RotValue);
    // }
    else if(RightKeyPressed) { }
    // { 
    //     // Player->Starship->Rotate(-RotValue);
    // }

    if(UpKeyPressed)
    {
        // scale the angle vector by the velocity scalar
        // and then add it to the xpos
        // and finally smooth it with delta time

        // Player->Starship->XPos += 100.0f * cosf(Player->Starship->Angle * (3.14159 / 180.0f)) * Dt;
        // Player->Starship->YPos += 100.0f * sinf(Player->Starship->Angle * (3.14159 / 180.0f)) * Dt;

        // std::cout << "x pos: " << Player->Starship->XPos << std::endl;
        // std::cout << "y pos: " << Player->Starship->YPos << std::endl;
    }
}

int game::Play()
{
    LoadAssets();

    // SetGameState(PLAYING);

    auto DtNow = std::chrono::system_clock::now();
    auto DtLast = DtNow;

    std::chrono::duration<float> Dt;

    while(Playing)
    {
        // We assign the current timestamp
        // to DtNow, and then using this information
        // we can find how much time elapsed between frames
        // because DtNow is Now and DtLast is the timestamp for the
        // start of the last frame
        // therefore DtNow - DtLast is delta time, or the time between frames

        DtNow = std::chrono::system_clock::now(); // start of frame
        Dt = DtNow - DtLast; // time elapsed between start of this frame and the last

        // now that we've calculated Dt, we can save the start of this frame
        // by assigning DtNow to DtLast
        DtLast = DtNow; // start of last frame gets assigned

        Update(Dt.count());

        Renderer.ClearScreen();

        DrawObjects();
        DrawPlayer();

        Renderer.SwapBuffers();
    }

    Destroy();

    return EXIT_SUCCESS;
}