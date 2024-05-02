#include "game.h"

game::game()
{
    OnConstruct();
}

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

bool game::InitGfx() 
{
    int Result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    if(!IsGood(Result))
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to initialize library: SDL" << std::endl;

        SetErrorState(game_error_code::GFX_INITIALIZATION_FAILED, SDL_GetError());

        return false;
    }

    int Flags = IMG_INIT_JPG | IMG_INIT_PNG;

    Result = IMG_Init(Flags);

    if((Result & Flags) != Flags)
    {
        std::cout << "Error Message: " << IMG_GetError()       << std::endl;
        std::cout << "failed to initialize library: SDL_image" << std::endl;

        SetErrorState(game_error_code::GFX_INITIALIZATION_FAILED, IMG_GetError());

        return false;
    }

    Result = TTF_Init();

    if(!IsGood(Result))
    {
        std::cout << "Error Message: " << TTF_GetError()     << std::endl;
        std::cout << "failed to initialize library: SDL_ttf" << std::endl;

        SetErrorState(game_error_code::GFX_INITIALIZATION_FAILED, TTF_GetError());

        return false;
    }

    Window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, 
                                            SDL_WINDOWPOS_UNDEFINED, 
                                            1024, 768, SDL_WINDOW_SHOWN);
    
    if(!Window)
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to make game window."       << std::endl;

        SetErrorState(game_error_code::GFX_FAILED_TO_CREATE_WINDOW, SDL_GetError());

        return false;
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    if(!Renderer)
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to make game renderer."     << std::endl;

        SetErrorState(game_error_code::GFX_FAILED_TO_CREATE_RENDERER, SDL_GetError());

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

            game_texture* Texture = new game_texture(AssetID, 
                                                     AssetPath,
                                                     TextureData, 
                                                     Surface->w, 
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

        game_font* Font = new game_font(AssetID, 
                                        AssetPath, 
                                        FontData, 
                                        FontSize);
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

    LoadTexture(texture_id::Space, "/home/nathan/Documents/code/asteroids/assets/textures/space.png");
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

/* ERROR STATE MGMT METHODS */
void game::SetErrorState(game_error_code GameLastErrorCode, 
                         std::string GameLastErrorMessage)
{
    LastErrorCode    = GameLastErrorCode;
    LastErrorMessage = GameLastErrorMessage;
}

bool game::HasErrorState() const
{
    return LastErrorCode != game_error_code::NONE;
}

/* INITIALIZATION AND 
   DESTRUCTION METHODS */

void game::SetGameState(game_state_id NextState)
{
    State = NextState;
}

bool game::Init()
{
    if(!InitGfx())
    {
        std::cout << "gfx initialization failed..." << std::endl;

        return false;
    }

    OnInit();

    MakeBackground();
    MakePlayer();

    SetGameState(game_state_id::AT_START_MENU);

    return true;
}

void game::Destroy()
{
    DestroyBackground();
    DestroyPlayer();

    ObjectMap.Destroy();
    AssetMap.Destroy();
}

int game::Run()
{
    if(!Init())
    {
        std::cout << "game initialization failed..." << std::endl;

        return (int) LastErrorCode;
    }

    Play();

    return EXIT_SUCCESS;
}

/* DRAWING METHODS */
void game::DrawShip(ship* Ship)
{
    game_texture* Texture = (game_texture*) AssetMap.Get(Ship->GetAssetID());

    RenderTexture(Texture, Ship);
}

void game::DrawBackground()
{
    // game_texture* Texture = Background.Texture;

    // int ColCount = WindowW / Background.Width;
    // int RowCount = WindowH / Background.Height;

    // for(uint32_t RowIdx = 0; RowIdx < RowCount; RowIdx++)
    // {
    //     int Y = Background.Height * RowIdx;

    //     for(uint32_t ColIdx = 0; ColIdx < ColCount; ColIdx++)
    //     {
    //         int X = Background.Width * ColIdx;

    //         SDL_Rect Dest 
    //         {
    //             X, Y,

    //             Background.Width,
    //             Background.Height
    //         };

    //         RenderTexture(Texture->GetData(), Dest);
    //     }
    // }
}

void game::DrawMenu(game_menu* Menu)
{
    uint32_t Count = Menu->Options.size();

    for(uint32_t Index = 0; Index < Count; Index++)
    {
        Menu->Options[Index].

    }
}

void game::DrawPlayer()
{
    DrawShip(Player->GetShip());
}

void game::DrawObjects()
{ }

/* CREATIONAL & DELETE METHODS */
void game::DestroyBackground()
{
    if(Background)
    {
        delete Background;

        Background = nullptr;
    }
}

void game::DestroyPlayer()
{
    if(Player)
    {
        delete Player;

        Player = nullptr;
    }
}

void game::DestroyMenu(game_menu*& Menu)
{
    if(Menu)
    {
        uint32_t OptionCount = Menu->Options.size();

        for(uint32_t Index = 0; Index < OptionCount; Index++)
        {
            delete Menu->Options[Index];

            Menu->Options[Index] = nullptr;
        }

        delete Menu;

        Menu = nullptr;
    }
}

void game::MakeMenu(game_menu* Menu, std::pair<std::string, on_click_handler>* MenuOptions, uint32_t MenuOptionCount)
{
    for(uint32_t OptionIndex = 0; 
        OptionIndex < MenuOptionCount; 
        OptionIndex++)
    {
        CreateTexture(nullptr, MenuOptions[OptionIndex].first);

        AddMenuOption(MainMenu, 
                      OptionIndex, 
                      MenuOptions[OptionIndex].first, 
                      MenuOptions[OptionIndex].second);
    }
}

void game::AddMenuOption(game_menu* Menu, uint32_t OptionIndex, std::string OptionText, on_click_handler OnClickHandler)
{
    SDL_Texture* Texture = nullptr;

    Texture = CreateTexture(Menu->Font, OptionText);

    if(Texture)
    {
        game_menu_option* MenuOption = new game_menu_option { };

        MenuOption->Texture = Texture;
        MenuOption->Index   = OptionIndex;
        MenuOption->Text    = std::move(OptionText);
        MenuOption->Handler = OnClickHandler;

        Menu->Options.push_back(MenuOption);
    }
}

void game::MakePauseMenu()
{
    DestroyMenu(PauseMenu);

    PauseMenu         = new game_menu();
    PauseMenu->MenuID = ++game::GlobalMenuID;

    uint32_t MenuOptionCount = 4;

    std::pair<std::string, on_click_handler> MenuOptions[]
    {
        { "Resume", &game::OnStart },
        { "Save",   &game::OnSave  },
        { "Quit",   &game::OnQuit  },
        { "Exit",   &game::OnExit  }
    };

    MakeMenu(PauseMenu, MenuOptions, MenuOptionCount); 
}

void game::MakeMainMenu()
{
    DestroyMenu(MainMenu);

    MainMenu         = new game_menu();
    MainMenu->MenuID = ++game::GlobalMenuID;

    uint32_t MenuOptionCount = 4;

    std::pair<std::string, on_click_handler> MenuOptions[]
    {
        { "Start Game", &game::OnStart    },
        { "Load Game",  &game::OnLoad     },
        { "Settings",   &game::OnSettings },
        { "Exit",       &game::OnExit     }
    };

    MakeMenu(MainMenu, MenuOptions, MenuOptionCount); 
}

void game::MakeBackground()
{
    DestroyBackground();

    Background = new game_background();

    Background->Size.W = 128;
    Background->Size.H = 128;

    Background->XOffset = 0;
    Background->YOffset = 0;

    uint32_t AssetID = texture_id::Space;
    Background->Texture = (game_texture*) AssetMap.Get(AssetID);
}

void game::MakePlayer()
{
    DestroyPlayer();

    Player = new player();

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
        float BaseSpeed  = 250.0f;
        float MaxSpeed   = 300.0f;

        ship* PlayerShip = MakeShip(AssetID, 
                                    ShipX, ShipY, 
                                    ShipW, ShipH, 
                                    BaseSpeed, 
                                    MaxSpeed, 
                                    false);
        if(!PlayerShip)
        {
            // logging, failed to alloc 
            // memory for player ship object
        }

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
        uint32_t WorldID = SaveObject(Ship);

        Ship->SetWorldID(WorldID);
    }

    return Ship;
}

/* OBJECT MGMT METHODS */
uint32_t game::SaveObject(game_object* Object)
{
    uint32_t WorldID = ObjectMap.Add(Object);

    return WorldID;
}

/* EVENT HANDLING Methods */
void game::OnConstruct()
{
    Window = nullptr;
    Renderer = nullptr;

    WindowW = 0;
    WindowH = 0;

    Background = nullptr;
    Player = nullptr;

    GameKeyCount = 0;
    GameKeys = nullptr;

    LastErrorCode = game_error_code::NONE;
    LastErrorMessage = "";

    // std::chrono::time_point<std::chrono::system_clock> DtNow;
    // std::chrono::time_point<std::chrono::system_clock> DtLast;
    // std::chrono::duration<float>                       Dt;
}

void game::OnInit()
{
    LoadAssets();
}

void game::OnSettings()
{ }

void game::OnQuit()
{ }

void game::OnSave()
{ }

void game::OnLoad()
{ }

void game::OnExit()
{ }

void game::OnStart()
{ }

void game::OnPause()
{ }

void game::OnStop()
{ }

/* EVENT MGMT METHODS */
void game::HandleEvents()
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

void game::UpdateWindowSize()
{
    SDL_GetWindowSize(Window, 
                      &WindowW, 
                      &WindowH);
}

void game::UpdateKeyState()
{
    GameKeys = SDL_GetKeyboardState(&GameKeyCount);
}

void game::Update(float Dt)
{
    UpdateWindowSize();
    UpdateKeyState();

    bool LeftKeyPressed  = GameKeys[SDL_SCANCODE_LEFT]  > 0;
    bool RightKeyPressed = GameKeys[SDL_SCANCODE_RIGHT] > 0;
    bool UpKeyPressed    = GameKeys[SDL_SCANCODE_UP]    > 0;

    if(LeftKeyPressed) 
    {
        Player->GetShip()->Rotate(TO_RADIANS(1.0f));
    }
    else if(RightKeyPressed) 
    {
        Player->GetShip()->Rotate(TO_RADIANS(-1.0f));
    }

    if(UpKeyPressed)
    {
        Player->GetShip()->Move(Dt);
    }
}

/* RENDERING METHODS */
SDL_Texture* game::CreateTexture(SDL_Surface* Surface)
{
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);

    return Texture;
}

SDL_Texture* game::CreateTexture(game_font* Font, std::string Text)
{
    SDL_Texture* Texture = nullptr;

    TTF_Font* Data = Font->Data;
    SDL_Color Color = Font->Color;

    SDL_Surface* Surface = TTF_RenderText_Solid(Data, Text.c_str(), Color);

    if(!Surface)
    {
        // log occurrence, 
        // report or notify user
        return nullptr;
    }

    Texture = CreateTexture(Surface);

    return Texture;
}

void game::RenderTexture(SDL_Texture* Texture, game_object* Object)
{
    float Angle = Object->Rotation();
    
    SDL_Rect Dest 
    {
        Object->X(),
        Object->Y(),
        Object->W(),
        Object->H()
    };

    RenderTexture(Texture, Dest, Angle);
}

void game::RenderTexture(SDL_Texture* Texture, SDL_Rect Dest, float Angle)
{
    SDL_RenderCopyEx(Renderer, Texture, nullptr, 
                     &Dest, Angle, nullptr, 
                     SDL_FLIP_NONE);
}

void game::RenderTexture(game_texture* Texture, game_object* Object)
{
    RenderTexture(Texture->GetData(), Object);
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
    UpdateTimer();

    while(true)
    {
        UpdateTimer();
        HandleEvents();
        ClearScreen();

        DrawBackground();

        if(!true)
        {
            if(!true)
            {
                Update(Dt.count());

                DrawPlayer();
            }
            else
            {
                DrawMenu(PauseMenu);
            }
        }
        else
        {
            DrawMenu(MainMenu);
        }

        SwapBuffers();
    }

    Destroy();

    return EXIT_SUCCESS;
}