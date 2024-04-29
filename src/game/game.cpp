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

/* ASSET LOADING / MGMT METHODS */

bool game::LoadTexture(uint32_t AssetID, std::string AssetPath)
{
    if(!AssetPath.empty())
    {
        SDL_Surface* Surface = nullptr;

        Surface = IMG_Load(AssetPath.c_str());

        if(Surface)
        {
            SDL_Texture* TextureData = nullptr;

            TextureData = CreateTexture(Surface);

            if(!TextureData)
            {
                std::cout << "failed to load texture: " << AssetPath << std::endl;;
                std::cout << "IMG_GetError(): " << IMG_GetError() << std::endl;

                return false;
            }

            game_texture* Texture = new game_texture(AssetID, AssetPath,
                                                     TextureData, Surface->w, 
                                                     Surface->h);
            AssetMap.Add(AssetID, Texture);                

            SDL_FreeSurface(Surface);
            Surface = nullptr;

            return true;
        }
    }

    return false;
}

bool game::LoadFont(uint32_t AssetID, std::string AssetPath, int FontSize)
{
    if(!AssetPath.empty() && FontSize > 0)
    {
        TTF_Font* FontData = nullptr;

        FontData = TTF_OpenFont(AssetPath.c_str(), FontSize);

        if(!FontData)
        {
            std::cout << "failed to load font: " << AssetPath << std::endl;;
            std::cout << "TTF_GetError(): " << TTF_GetError() << std::endl;

            return false;
        }

        game_font* Font = new game_font(AssetID, AssetPath, 
                                        FontData, FontSize);
        AssetMap.Add(AssetID, Font);

        return true;
    }

    return false;
}

void game::LoadAssets()
{
    LoadFont(font_id::PressStart2P_Regular_9, "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 9);
    LoadFont(font_id::PressStart2P_Regular_12, "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 12);
    LoadFont(font_id::PressStart2P_Regular_24, "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 24);

    LoadTexture(texture_id::AsteroidGrey1, "/home/nathan/Documents/code/asteroids/assets/textures/asteroid1_grey.png");
    LoadTexture(texture_id::AsteroidGrey2, "/home/nathan/Documents/code/asteroids/assets/textures/asteroid2_grey.png");
    LoadTexture(texture_id::AsteroidBrown1, "/home/nathan/Documents/code/asteroids/assets/textures/asteroid1_brown.png");
    LoadTexture(texture_id::AsteroidBrown2, "/home/nathan/Documents/code/asteroids/assets/textures/asteroid2_brown.png");
    LoadTexture(texture_id::FlagLight, "/home/nathan/Documents/code/asteroids/assets/textures/flag.png");
    LoadTexture(texture_id::FlagDark, "/home/nathan/Documents/code/asteroids/assets/textures/flagdark.png");
    LoadTexture(texture_id::Projectile1, "/home/nathan/Documents/code/asteroids/assets/textures/projectile1.png");
    LoadTexture(texture_id::Projectile2, "/home/nathan/Documents/code/asteroids/assets/textures/projectile2.png");
    LoadTexture(texture_id::Starship, "/home/nathan/Documents/code/asteroids/assets/textures/starship.png");
    LoadTexture(texture_id::UFO, "/home/nathan/Documents/code/asteroids/assets/textures/ufodark.png");
}

/* INITIALIZATION AND 
   DESTRUCTION METHODS */
void game::Destroy()
{
    DestroyPlayer();

    ObjectMap.Destroy();
    AssetMap.Destroy();
}

/* DRAWING METHODS */
void game::DrawPlayer()
{
    if(Player)
    {
        // uint32_t TextureID    = Player->Starship->TextureID;
        // game_texture* Texture = (game_texture*) AssetMap.Get(TextureID);
        // Renderer.DrawTexture(Texture, Player->Starship);
    }
}

void game::DrawObjects()
{ }

/* CREATIONAL & DELETE METHODS */
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
    player* Player = new player();

    if(!Player)
    {
        // logging, failed to alloc 
        // memory for player object
    }
    else
    {
        uint32_t AssetID = texture_id::Starship;
        int ShipX        = 0;
        int ShipY        = 0;
        int ShipW        = 128;
        int ShipH        = 128;
        float BaseSpeed  = 100.0f;
        float MaxSpeed   = 200.0f;

        ship* PlayerShip = MakeShip(AssetID, 
                                    ShipX, ShipY, 
                                    ShipW, ShipH, 
                                    BaseSpeed, 
                                    MaxSpeed, 
                                    false);

        Player->UseShip(PlayerShip);
    }
}

ship* game::MakeShip(uint32_t AssetID, 
                     int ShipX, int ShipY,
                     int ShipW, int ShipH,
                     float BaseSpeed,
                     float MaxSpeed,
                     bool Save)
{
    ship* Ship = ship::Make(AssetID, ShipX, ShipY,
                            ShipW, ShipH, BaseSpeed, 
                            MaxSpeed);
    if(Save)
    {
        if(Ship)
        {
            uint32_t WorldID = SaveObject(Ship);

            Ship->SetWorldID(WorldID);
        }
        else
        {
            // write to logger
            // failed to save ship object
        }
    }

    return Ship;
}

/* GAME STATE MGMT METHODS */
void game::SetGameState(game_state_id NextState)
{
    if(State == game_state_id::STOPPED)
    {
        if(NextState == game_state_id::PLAYING)
        {
            State = NextState;

            Playing = true;
            Paused = false;
        }
    }
    else if(State == game_state_id::PAUSED)
    {
        if(NextState == game_state_id::PLAYING)
        {
            State = NextState;

            Paused = false;
        }
        else if(NextState == game_state_id::STOPPED)
        {
            State = NextState;

            Paused = false;
            Playing = false;
        }
    }
    else if(State == game_state_id::PLAYING)
    {
        if(NextState == game_state_id::PAUSED)
        {
            State = NextState;

            Paused = true;
        }
        else if(NextState == game_state_id::STOPPED)
        {
            State = NextState;

            Paused = false;
            Playing = false;
        }
    }
}

/* OBJECT MGMT METHODS */
uint32_t game::SaveObject(game_object* Object)
{
    uint32_t WorldID = ObjectMap.Add(Object);

    return WorldID;
}

/* EVENT MGMT METHODS */
void game::HandleEvents()
{
    SDL_Event Evt { };

    while(SDL_PollEvent(&Evt))
    {
        if(Evt.type == SDL_QUIT)
        {
            SetGameState(game_state_id::STOPPED);
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
}

/* PER FRAME UPDATE METHODS */
void game::UpdateTimer()
{
    // We assign the current timestamp
    // to DtNow, and then using this information
    // we can find how much time elapsed between frames
    // because DtNow is Now and DtLast is the timestamp for the
    // start of the last frame
    // therefore DtNow - DtLast is delta time, or the time between frames

    DtNow  = std::chrono::system_clock::now(); // start of frame
    Dt     = DtNow - DtLast; // time elapsed between start of this frame and the last

    // now that we've calculated Dt, we can save the start of this frame
    // by assigning DtNow to DtLast
    DtLast = DtNow; // start of last frame gets assigned
}

void game::UpdateKeyState()
{
    GameKeys = SDL_GetKeyboardState(&GameKeyCount);
}

void game::Update(float Dt)
{
    UpdateKeyState();

    bool LeftKeyPressed  = GameKeys[SDL_SCANCODE_LEFT]  > 0;
    bool RightKeyPressed = GameKeys[SDL_SCANCODE_RIGHT] > 0;
    bool UpKeyPressed    = GameKeys[SDL_SCANCODE_UP]    > 0;
    bool DownKeyPressed  = GameKeys[SDL_SCANCODE_DOWN]  > 0;

    // if(LeftKeyPressed) { }
    // else if(RightKeyPressed) { }
    // if(UpKeyPressed) { }
}

/* RENDERING METHODS */
SDL_Texture* game::CreateTexture(SDL_Surface* Surface)
{
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);

    return Texture;
}

void game::RenderTexture(SDL_Texture* Texture, game_object* Object)
{
    float Angle = Object->Rotation();
    
    SDL_Rect Dest 
    {
        Object->X(), Object->Y(),
        Object->W(), Object->H()
    };

    SDL_RenderCopyEx(Renderer, Texture, nullptr, 
                     &Dest, Angle, nullptr, 
                     SDL_FLIP_NONE);
}

void game::RenderTexture(game_texture* Texture, game_object* Object)
{
    RenderTexture(Texture->Data, Object);
}

void game::ClearScreen()
{
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Renderer);
}

void game::SwapBuffers()
{
    SDL_RenderPresent(Renderer);
}

/* MAIN GAME LOOP */
int game::Play()
{
    SetGameState(game_state_id::PLAYING);

    UpdateTimer();

    while(Playing)
    {
        UpdateTimer();
        HandleEvents();

        if(!Paused)
        {
            Update(Dt.count());

            // DrawObjects();
            // DrawPlayer();
        }
    }

    Destroy();

    return EXIT_SUCCESS;
}