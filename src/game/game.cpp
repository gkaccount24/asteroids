#include "game.h"

static uint32_t AssetID;
static uint32_t ObjectID;

bool InitGfx(game* Game) 
{
    int Result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    if(!IsGood(Result))
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to initialize library: SDL" << std::endl;

        // SetErrorState(game_error_code::GFX_INITIALIZATION_FAILED, SDL_GetError());

        return false;
    }

    int Flags = IMG_INIT_JPG | IMG_INIT_PNG;

    Result = IMG_Init(Flags);

    if((Result & Flags) != Flags)
    {
        std::cout << "Error Message: " << IMG_GetError()       << std::endl;
        std::cout << "failed to initialize library: SDL_image" << std::endl;

        // SetErrorState(game_error_code::GFX_INITIALIZATION_FAILED, IMG_GetError());

        return false;
    }

    Result = TTF_Init();

    if(!IsGood(Result))
    {
        std::cout << "Error Message: " << TTF_GetError()     << std::endl;
        std::cout << "failed to initialize library: SDL_ttf" << std::endl;

        // SetErrorState(game_error_code::GFX_INITIALIZATION_FAILED, TTF_GetError());

        return false;
    }

    Game->Window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                    1024, 768, SDL_WINDOW_SHOWN);
    
    if(!Game->Window)
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to make game window."       << std::endl;

        // SetErrorState(game_error_code::GFX_FAILED_TO_CREATE_WINDOW, SDL_GetError());

        return false;
    }

    Game->Renderer = SDL_CreateRenderer(Game->Window, -1, SDL_RENDERER_ACCELERATED);

    if(!Game->Renderer)
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to make game renderer."     << std::endl;

        // SetErrorState(game_error_code::GFX_FAILED_TO_CREATE_RENDERER, SDL_GetError());

        return false;
    }

    return true;
}

void AddAsset(std::unordered_map<std::string, game_asset*>& Assets, std::string Key, game_asset* Asset)
{
    if(!Key.empty())
    {
        auto Entry = Assets.find(Key);

        if(Asset && Entry == std::end(Assets))
        {
            Assets[Key] = Asset;
        }
    }
}

bool LoadTexture(game* Game, std::string Key, std::string Path)
{
    if(!Path.empty())
    {
        SDL_Surface* Surface = nullptr;

        Surface = IMG_Load(Path.c_str());

        if(Surface)
        {
            SDL_Texture* TextureData = nullptr;

            TextureData = CreateTexture(Game->Renderer, Surface);

            if(!TextureData)
            {
                std::cout << "failed to load texture: " << Path << std::endl;;
                std::cout << "IMG_GetError(): " << IMG_GetError() << std::endl;

                return false;
            }

            game_asset* Asset = new game_asset { };
            game_texture* Texture = new game_texture { };

            Asset->Data.Texture = Texture;

            Asset->ID = ++AssetID;
            Asset->Path = Path;

            AddAsset(Game->Assets, Key, Asset);

            SDL_FreeSurface(Surface);
            Surface = nullptr;

            return true;
        }
    }

    return false;
}

bool LoadFont(game* Game, std::string Key, std::string Path, int FontSize)
{
    if(!Path.empty() && FontSize > 0)
    {
        TTF_Font* FontData = nullptr;

        FontData = TTF_OpenFont(Path.c_str(), FontSize);

        if(!FontData)
        {
            std::cout << "failed to load font: " << Path << std::endl;;
            std::cout << "TTF_GetError(): " << TTF_GetError() << std::endl;

            return false;
        }

        game_asset* Asset = new game_asset { };
        game_font* Font = new game_font { };

        Asset->Data.Font = Font;
        Asset->ID = ++AssetID;
        Asset->Path = Path;

        AddAsset(Game->Assets, Key, Asset);

        return true;
    }

    return false;
}

void LoadAssets(game* Game)
{
    LoadFont(Game, "", "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 9);
    LoadFont(Game, "", "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 12);
    LoadFont(Game, "", "/home/nathan/Documents/code/asteroids/assets/fonts/PressStart2P-Regular.ttf", 24);

    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/space.png");
    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/asteroid1_grey.png");
    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/asteroid2_grey.png");
    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/asteroid1_brown.png");
    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/asteroid2_brown.png");
    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/flag.png");
    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/flagdark.png");
    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/projectile1.png");
    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/projectile2.png");
    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/starship.png");
    LoadTexture(Game, "", "/home/nathan/Documents/code/asteroids/assets/textures/ufodark.png");
}

void OnConstruct(game* Game)
{
    Game->Window = nullptr;
    Game->Renderer = nullptr;

    Game->WindowW = 0;
    Game->WindowH = 0;
}

void OnInit(game* Game)
{
    LoadAssets(Game);
}

void MakePauseMenu(game* Game)
{
    DestroyMenu(PauseMenu);

    PauseMenu         = new game_menu();
    PauseMenu->MenuID = ++MenuID;

    uint32_t MenuOptionCount = 4;

    std::pair<std::string, on_click_handler> MenuOptions[]
    {
        { "Resume", &OnStart },
        { "Save",   &OnSave  },
        { "Quit",   &OnQuit  },
        { "Exit",   &OnExit  }
    };

    MakeMenu(PauseMenu, MenuOptions, MenuOptionCount); 
}

void MakeMainMenu(game* Game)
{
    DestroyMenu(MainMenu);

    MainMenu         = new game_menu();
    MainMenu->MenuID = ++MenuID;

    uint32_t MenuOptionCount = 4;

    std::pair<std::string, on_click_handler> MenuOptions[]
    {
        { "Start Game", &OnStart    },
        { "Load Game",  &OnLoad     },
        { "Settings",   &OnSettings },
        { "Exit",       &OnExit     }
    };

    MakeMenu(MainMenu, MenuOptions, MenuOptionCount); 
}

void OccupyObjectEntry()
{

}

uint32_t AddObject(game_object_map* Map, game_object* Object)
{
    if(!Map->FreeObjectEntries.empty())
    {
        auto Entry = Map->Entries.at(Map->FreeObjectEntries.back());

        OccupyObjectEntry();

        Map->FreeObjectEntries.pop_back();

        return Entry->WorldID;
    }
    else
    {
        auto Entry = Map->Entries[++ObjectID] = Object;

        return ObjectID;
    }
}

void FreeObject(game_object_map* ObjectMap, game_object* Object)
{

}

uint32_t SaveObject(game* Game, game_object* Object)
{
    uint32_t WorldID = AddObject(&Game->ObjectMap, Object);

    return WorldID;
}

bool InitGame(game* Game)
{
    if(!InitGfx(Game))
    {
        std::cout << "gfx initialization failed..." << std::endl;

        return false;
    }

    OnInit(Game);

    return true;
}

void DestroyGame(game* Game)
{
    // DestroyBackground();
    // DestroyPlayer();
    // ObjectMap.Destroy();
    // AssetMap.Destroy();

    if(Game->Renderer)
    {
        SDL_DestroyRenderer(Game->Renderer);

        Game->Renderer = nullptr;
    }

    if(Game->Window)
    {
        SDL_DestroyWindow(Game->Window);

        Game->Window = nullptr;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int RunGame(game* Game)
{
    if(!InitGame(Game))
    {
        std::cout << "game initialization failed..." << std::endl;

        return -1;
    }

    PlayGame(Game);

    return EXIT_SUCCESS;
}

/* DRAWING METHODS */
void DrawShip(ship* Ship) { }
void DrawBackground() { }
void DrawMenu(game_menu* Menu) { }
void DrawPlayer() { }
void DrawObjects() { }

void AddBackground(game* Game, uint32_t TextureID, int TileW, int TileH, int XOffset, int YOffset)
{
    game_background* Background = new game_background();

    if(!Background)
    {
        // logging, failed to alloc 
        // memory for player object
    }
    else
    {
        Background->Size.W = TileW;
        Background->Size.H = TileH;

        Background->XOffset = XOffset;
        Background->YOffset = YOffset;

        // Game->Backgrounds.push_back(Background);
    }
}

void AddPlayer(game* Game, int XPos, int YPos, 
               int Width, int Height,
               float BaseSpeed,
               float MaxSpeed)
{
    game_player* Player = new game_player { };

    if(!Player)
    {
        // logging, failed to alloc 
        // memory for player object
    }
    else
    {
        int ShipX        = XPos;
        int ShipY        = YPos;
        int ShipW        = Width;
        int ShipH        = Height;

        float BaseSpeed  = BaseSpeed;
        float MaxSpeed   = MaxSpeed;

        // ship* PlayerShip = MakeShip(AssetID, ShipX, ShipY, 
        //                             ShipW, ShipH, BaseSpeed, 
        //                             MaxSpeed, false);

        // if(!PlayerShip)
        // {
        //     // logging, failed to alloc 
        //     // memory for player ship object
        // }

        // AddObject(Game->ObjectMap);
        // Player->UseShip(PlayerShip);
        // Game->Players.push_back(Player);
    }
}

void OnSettings() { }
void OnQuit() { }
void OnSave() { }
void OnLoad() { }
void OnExit() { }
void OnStart() { }
void OnPause() { }
void OnStop() { }

void HandleEvents(game* Game)
{
    SDL_Event Evt { };

    while(SDL_PollEvent(&Evt))
    {
        if(Evt.type == SDL_QUIT)
        {

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

void UpdateTimer(game* Game)
{
    // We assign the current timestamp
    // to DtNow, and then using this information
    // we can find how much time elapsed between frames
    // because DtNow is Now and DtLast is the timestamp for the
    // start of the last frame
    // therefore DtNow - DtLast is delta time, or the time between frames
    Game->DtNow  = std::chrono::system_clock::now(); // start of frame
    Game->Dt     = Game->DtNow - Game->DtLast; // time elapsed between start of this frame and the last

    // now that we've calculated Dt, we can save the start of this frame
    // by assigning DtNow to DtLast
    Game->DtLast = Game->DtNow; // start of last frame gets assigned
}

void UpdateWindowSize(game* Game)
{
    SDL_GetWindowSize(Game->Window, 
                      &Game->WindowW, 
                      &Game->WindowH);
}

void Update(game* Game, float Dt)
{
    UpdateWindowSize();
    UpdateKeyState();

    // bool LeftKeyPressed  = GameKeys[SDL_SCANCODE_LEFT]  > 0;
    // bool RightKeyPressed = GameKeys[SDL_SCANCODE_RIGHT] > 0;
    // bool UpKeyPressed    = GameKeys[SDL_SCANCODE_UP]    > 0;

    if(LeftKeyPressed) 
    {
        // Player->GetShip()
        //       ->Rotate(TO_RADIANS(1.0f));
    }
    else if(RightKeyPressed) 
    {
        // Player->GetShip()
        //       ->Rotate(TO_RADIANS(-1.0f));
    }

    if(UpKeyPressed)
    {
        // Player->GetShip()
        //       ->Move(Dt);
    }
}

void ClearScreen(game* Game)
{
    SDL_SetRenderDrawColor(Game->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Game->Renderer);
}

void SwapBuffers(game* Game)
{
    SDL_RenderPresent(Game->Renderer);
}

int Play(game* Game)
{
    UpdateTimer();

    while(true)
    {
        UpdateTimer(Game);
        HandleEvents(Game);

        // ClearScreen();

        if(!true)
        {
            if(!true)
            {
                Update(Game, Game->Dt.count());

                DrawPlayer();
            }
        }

        SwapBuffers();
    }

    DestroyGame(Game);

    return EXIT_SUCCESS;
}

