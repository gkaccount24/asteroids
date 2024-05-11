#include "game.h"

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

    Game->WindowWidth = 1024;
    Game->WindowHeight = 768;
    Game->WindowFlags = 0;

    Game->Window = SDL_CreateWindow("Asteroids", Game->WindowWidth, Game->WindowHeight, Game->WindowFlags);
    
    if(!Game->Window)
    {
        std::cout << "Error Message: " << SDL_GetError() << std::endl;
        std::cout << "failed to make game window."       << std::endl;

        // SetErrorState(game_error_code::GFX_FAILED_TO_CREATE_WINDOW, SDL_GetError());

        return false;
    }

    Game->Renderer = SDL_CreateRenderer(Game->Window, nullptr, 0);

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

bool LoadAssets(game* Game)
{
    std::vector<asset_load*> AssetsToLoad
    {
        new asset_load { "Orbitron_Font",       "/home/nathan/Documents/asteroids/assets/Orbitron-Regular.ttf",                  game_asset_type::FONT, asset_load::font { 12, TTF_STYLE_NORMAL } },
        new asset_load { "UI_Textures",         "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_IU.png",          game_asset_type::TEXTURE },
        new asset_load { "Ship_Textures",       "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_Ships.png",       game_asset_type::TEXTURE },
        new asset_load { "Character_Textures",  "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_Characters.png",  game_asset_type::TEXTURE },
        new asset_load { "Background_Textures", "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_BackGrounds.png", game_asset_type::TEXTURE },
        new asset_load { "Projectile_Textures", "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_Projectiles.png", game_asset_type::TEXTURE }
    };

    std::size_t AssetCount = AssetsToLoad.size();

    for(std::size_t Index = 0; Index < AssetCount; Index++)
    {
        game_asset* Asset = nullptr;

        std::string Key = AssetsToLoad[Index]->Key;
        std::string Path = AssetsToLoad[Index]->Path;

        if(AssetsToLoad[Index]->Type == game_asset_type::FONT)
        {
            int FontStyle = AssetsToLoad[Index]->ForFont.Style;
            int FontSize = AssetsToLoad[Index]->ForFont.Size;

            Asset = LoadFont(FontStyle, FontSize, Path);
        }
        else if(AssetsToLoad[Index]->Type == game_asset_type::TEXTURE)
        {
            Asset = LoadTexture(Game->Renderer, Path);
        }

        if(!Asset)
        {
            std::cout << "Failed to load asset: " << Key  << std::endl;
            std::cout << "Asset path: "           << Path << std::endl;

            break;
        }

        AddAsset(Game->Assets, Key, Asset);
    }
}

void DestroyAssets(game* Game)
{
    auto Iter = std::begin(Game->Assets);
    auto End = std::end(Game->Assets);

    for(; Iter != End; Iter++)
    {
        if(Iter->second)
        {
            if(Iter->second->Type == game_asset_type::TEXTURE)
            {
                DestroyTexture(Iter->second->Data.Texture);

                Iter->second->Data.Texture = nullptr;
            }
            else if(Iter->second->Type == game_asset_type::FONT)
            {
                DestroyFont(Iter->second->Data.Font);

                Iter->second->Data.Font= nullptr;
            }

            delete Iter->second;

            Iter->second = nullptr;
        }
    }
}

void OnConstruct(game* Game)
{
    // INITIALIZE ALL THE GAME DATA HERE
    Game->Window = nullptr;
    Game->Renderer = nullptr;
    Game->WindowWidth = 0;
    Game->WindowHeight = 0;
    Game->WindowFlags = 0;

    Game->State.LastStateID = game_state_id::NONE;
    Game->State.StateID = game_state_id::AT_START_MENU;

    Game->State.LastErrorCode = game_error_code::NONE;
    Game->State.LastErrorMessage = "OK";

    Game->State.MouseX = 0.0f;
    Game->State.MouseY = 0.0f;
    Game->State.MouseButtonState = 0;

    Game->State.LeftMouseButtonPressed = false;
    Game->State.MiddleMouseButtonPressed = false;
    Game->State.RightMouseButtonPressed = false;

    Game->State.GameKeyCount = 0;
    Game->State.GameKeys = nullptr;

    Game->State.KeyUp = false;
    Game->State.KeyDown = false;
}

void OnInit(game* Game)
{
    // asset_manifest* Manifest =  LoadAssetManifest();
    // LoadAssets(Game, Manifest);

    LoadAssets(Game);
}

uint32_t AddObject(game_object_map* Map, game_object* Object)
{
    if(!Map->FreeObjectEntries.empty())
    {
        auto Entry = Map->Entries.at(Map->FreeObjectEntries.back());

        if(Entry)
        {
            delete Entry;

            Entry = nullptr;
        }

        Entry = Object;

        Map->FreeObjectEntries.pop_back();

        return Entry->WorldID;
    }
    else
    {
        auto Entry = Map->Entries[++ObjectID] = Object;

        return ObjectID;
    }
}

void FreeObject(game_object_map* Map, game_object* Object)
{
    auto Entry = Map->Entries.find(Object->WorldID);

    if(Entry != std::end(Map->Entries))
    {
        Map->FreeObjectEntries.push_back(Object->WorldID);

        if(Entry->second)
        {
            delete Entry->second;

            Entry->second = nullptr;
        }
    }
}

uint32_t SaveObject(game* Game, game_object* Object)
{
    uint32_t WorldID = AddObject(&Game->ObjectMap, Object);

    return WorldID;
}

void OnStart(game_state* GameState) 
{
    if(GameState->StateID == game_state_id::AT_START_MENU)
    {
        GameState->LastStateID = GameState->StateID;
        GameState->StateID = game_state_id::PLAYING;
    }
}

void OnPause(game_state* GameState) 
{
    if(GameState->StateID == game_state_id::PLAYING)
    {
        GameState->LastStateID = GameState->StateID;
        GameState->StateID = game_state_id::PAUSED;
    }
}

void OnStop(game_state* GameState) 
{
    if(GameState->StateID == game_state_id::AT_START_MENU ||
       GameState->StateID == game_state_id::PLAYING || 
       GameState->StateID == game_state_id::PAUSED)
    {
        GameState->LastStateID = GameState->StateID;
        GameState->StateID = game_state_id::STOPPED;
    }
}

void OnQuit(game_state* GameState) 
{
    if(GameState->StateID == game_state_id::PAUSED)
    {
        GameState->LastStateID = GameState->StateID;
        GameState->StateID = game_state_id::AT_START_MENU;
    }
}

void OnKeyUp(game_state* GameState) 
{
    GameState->KeyDown = false;
    GameState->KeyUp = true;
}

void OnKeyDown(game_state* GameState) 
{
    GameState->KeyDown = true;
    GameState->KeyUp = false;
}

void OnSettings(game_state* GameState) { }
void OnSave(game_state* GameState) { }
void OnLoad(game_state* GameState) { }

void DestroyMenus(game* Game)
{
    uint32_t Count = Game->Menus.size();

    for(uint32_t Index = 0; Index < Count; Index++)
    {
        game_menu*& Menu = Game->Menus[Index];

        DestroyMenu(Menu);
    }
}

void CreateMenus(game* Game)
{
    // game_font* Font = GetFont(Game->Assets, "Orbitron_Regular_Font_18");
    // game_menu* Menu = nullptr;
    // std::vector<std::pair<std::string, on_click_handler>> MainMenuOptions 
    // {
    //     { "Start Game", &OnStart },
    //     { "Load Game",  &OnLoad },
    //     { "Settings",   &OnSettings },
    //     { "Exit",       &OnStop }
    // };
    // Menu = MakeMenu(Game->Renderer, Font, MainMenuOptions);
    // if(Menu)
    // {
    //     Game->Menus.push_back(Menu);
    //     Menu = nullptr;
    // }
    // std::vector<std::pair<std::string, on_click_handler>> PauseMenuOptions 
    // {
    //     { "Resume", &OnStart },
    //     { "Save",   &OnSave },
    //     { "Quit",   &OnQuit },
    //     { "Exit",   &OnStop }
    // };
    // Menu = MakeMenu(Game->Renderer, Font, PauseMenuOptions);
    // if(Menu)
    // {
    //     Game->Menus.push_back(Menu); 
    //     Menu = nullptr;
    // }
}

void AddBackground(game* Game, uint32_t TextureID, int TileWidth, int TileHeight, int XOffset, int YOffset)
{
    game_background* Background = new game_background();

    Background->Size.Width = TileWidth;
    Background->Size.Height = TileHeight;
    Background->XOffset = XOffset;
    Background->YOffset = YOffset;
}

void AddPlayer(game* Game, vec2d Position, size Size, speed Speed)
{
    game_player* Player = new game_player { };
    game_object* Ship = MakeShip(Game->Assets, Position, Size, Speed);

    if(!Ship)
    {
        std::cout << "failed to make player ship" << std::endl;

        return;
    }

    AssignShip(Player, Ship);

    Game->Players.push_back(Player);
}

bool InitGame(game* Game)
{
    if(!InitGfx(Game))
    {
        std::cout << "gfx initialization failed..." << std::endl;

        return false;
    }

    // prepare for initialization
    OnInit(Game);

    // start initialization
    CreateMenus(Game);

    return true;
}

void DestroyGame(game* Game)
{
    DestroyMenus(Game);
    DestroyAssets(Game);

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
    OnConstruct(Game);

    if(!InitGame(Game))
    {
        std::cout << "game initialization failed..." << std::endl;

        return -1;
    }

    PlayGame(Game);

    return EXIT_SUCCESS;
}

void UpdateMenu(game_menu* Menu, int WindowWidth, int WindowHeight)
{
    Menu->Size.Width = WindowWidth * 0.5f;
    Menu->Size.Height = WindowHeight * 0.5f;

    float XPos = (WindowWidth / 2.0f) - (Menu->Size.Width / 2.0f);
    float YPos = (WindowHeight / 2.0f) - (Menu->Size.Height / 2.0f);

    Menu->Position.X = XPos;
    Menu->Position.Y = YPos;

    std::size_t OptionCount = Menu->Options.size();

    for(std::size_t Index = 0; Index < OptionCount; Index++)
    {
        float MenuWidth = Menu->Size.Width;
        float MenuHeight = Menu->Size.Height;

        float Width = Menu->Options[Index]->Texture->Size.Width;
        float Height = Menu->Options[Index]->Texture->Size.Height;

        float PositionX = Menu->Position.X;
        float PositionY = Menu->Position.Y;

        Menu->Options[Index]->Size.Width = Width;
        Menu->Options[Index]->Size.Height = Height;

        Menu->Options[Index]->Position.X = ((MenuWidth - Width) / 2.0f) + PositionX;
        Menu->Options[Index]->Position.Y = Height * Index + PositionY;
    }
}

void DrawMenuOption(SDL_Renderer* Renderer, game_menu_option* MenuOption, SDL_Color Color)
{
    SDL_Texture* Texture = MenuOption->Texture->Data;

    SDL_FRect SourceRECT 
    {
        MenuOption->Texture->Position.X,
        MenuOption->Texture->Position.Y,

        static_cast<float>(MenuOption->Texture->Size.Width),
        static_cast<float>(MenuOption->Texture->Size.Height)
    };

    SDL_FRect DestRECT
    {
        MenuOption->Position.X,
        MenuOption->Position.Y,

        static_cast<float>(MenuOption->Size.Width),
        static_cast<float>(MenuOption->Size.Height)
    };

    Draw(Renderer, Texture, SourceRECT, DestRECT, 0.0, Color);
}

void DrawMenu(SDL_Renderer* Renderer, game_menu* Menu) 
{
    std::size_t Count = Menu->Options.size();

    for(std::size_t Index = 0; Index < Count; Index++)
    {
        game_menu_option* MenuOption = Menu->Options[Index];

        SDL_Texture* Texture = MenuOption->Texture->Data;
        SDL_Color Color = Menu->Font->Style.Colors[(int) MenuOption->ColorIndex];

        SDL_FRect SourceRECT 
        {
            MenuOption->Texture->Position.X,
            MenuOption->Texture->Position.Y,

            static_cast<float>(MenuOption->Texture->Size.Width),
            static_cast<float>(MenuOption->Texture->Size.Height)
        };

        SDL_FRect DestRECT
        {
            MenuOption->Position.X,
            MenuOption->Position.Y,

            static_cast<float>(MenuOption->Size.Width),
            static_cast<float>(MenuOption->Size.Height)
        };

        Draw(Renderer, Texture, SourceRECT, DestRECT, 0.0, Color);
    }
}

void HandleEvents(game* Game)
{
    SDL_Event Evt { };

    while(SDL_PollEvent(&Evt))
    {
        if(Evt.type == SDL_EVENT_QUIT)
        {
            OnQuit(&Game->State);

            break;
        }

        else if(Evt.type == SDL_EVENT_MOUSE_MOTION)
        {
            if(Game->State.StateID == game_state_id::AT_START_MENU) 
            {
                game_menu* Menu = Game->Menus[(int) game_menu_state_ids::AT_START_MENU];

                int MenuEndX = Menu->Position.X + Menu->Size.Width;
                int MenuEndY = Menu->Position.Y + Menu->Size.Height;

                int MenuStartX = Menu->Position.X;
                int MenuStartY = Menu->Position.Y;

                if(Evt.motion.x >= MenuStartX && Evt.motion.x <= MenuEndX &&
                   Evt.motion.y >= MenuStartY && Evt.motion.y <= MenuEndY)
                {
                    std::size_t OptionCount = Menu->Options.size();

                    for(std::size_t Index = 0; Index < OptionCount; Index++)
                    {
                        MenuEndX = Menu->Options[Index]->Position.X + Menu->Options[Index]->Size.Width;
                        MenuEndY = Menu->Options[Index]->Position.Y + Menu->Options[Index]->Size.Height;

                        MenuStartX = Menu->Options[Index]->Position.X;
                        MenuStartY = Menu->Options[Index]->Position.Y;

                        if(Evt.motion.x >= MenuStartX && Evt.motion.x <= MenuEndX &&
                           Evt.motion.y >= MenuStartY && Evt.motion.y <= MenuEndY)
                        {
                            Menu->Options[Index]->ColorIndex = font_color_index::HOVERED;

                            break;
                        }
                        else
                        {
                            Menu->Options[Index]->ColorIndex = font_color_index::FOREGROUND;
                        }
                    }
                }
            }

            break;
        }
        else if(Evt.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {

            break;
        }
        else if(Evt.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {

            break;
        }
        else if(Evt.type == SDL_EVENT_KEY_UP)
        {
            switch(Evt.key.keysym.sym)
            {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                case SDLK_DOWN:
                case SDLK_UP:
                {
                    OnKeyUp(&Game->State);

                    break;
                }
            }
        }
        else if(Evt.type == SDL_EVENT_KEY_DOWN)
        {
            switch(Evt.key.keysym.sym)
            {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                case SDLK_DOWN:
                case SDLK_UP:
                {
                    OnKeyDown(&Game->State);

                    break;
                }
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
    Game->DtNow = std::chrono::system_clock::now(); // start of frame
    Game->Dt = Game->DtNow - Game->DtLast; // time elapsed between start of this frame and the last

    // now that we've calculated Dt, we can save the start of this frame
    // by assigning DtNow to DtLast
    Game->DtLast = Game->DtNow; // start of last frame gets assigned
}

void UpdateWindowSize(game* Game)
{
    SDL_GetWindowSize(Game->Window, &Game->WindowWidth, &Game->WindowHeight);
}

void UpdateKeyState(game* Game)
{
    Game->State.GameKeys = SDL_GetKeyboardState(&Game->State.GameKeyCount);
}

void UpdateMouseState(game* Game)
{
    Game->State.MouseButtonState = SDL_GetMouseState(&Game->State.MouseX, &Game->State.MouseY);

    Game->State.LeftMouseButtonPressed = (Game->State.MouseButtonState & SDL_BUTTON_LMASK) > 0;
    Game->State.MiddleMouseButtonPressed = (Game->State.MouseButtonState & SDL_BUTTON_MMASK) > 0;
    Game->State.RightMouseButtonPressed = (Game->State.MouseButtonState & SDL_BUTTON_RMASK) > 0;
}

void Update(game* Game, float Dt)
{
    UpdateWindowSize(Game);
    UpdateMouseState(Game);
    UpdateKeyState(Game);

    if(Game->State.LeftMouseButtonPressed) { }
    else if(Game->State.MiddleMouseButtonPressed) { }
    else if(Game->State.RightMouseButtonPressed) { }

    bool LeftKeyPressed = Game->State.GameKeys[SDL_SCANCODE_LEFT] > 0;
    bool RightKeyPressed = Game->State.GameKeys[SDL_SCANCODE_RIGHT] > 0;
    bool UpKeyPressed = Game->State.GameKeys[SDL_SCANCODE_UP] > 0;
}

void DrawBackground() { }
void DrawShip(ship* Ship) { }
void DrawPlayers() { }
void DrawObjects() { }

int PlayGame(game* Game)
{
    SDL_Color Background = SDL_Color { 0, 0, 0, SDL_ALPHA_OPAQUE };

    UpdateTimer(Game);

    while(Game->State.StateID != game_state_id::STOPPED)
    {
        UpdateTimer(Game);
        HandleEvents(Game);

        ClearScreen(Game->Renderer, Background);

        DrawBackground();

        if(Game->State.StateID == game_state_id::AT_START_MENU)
        {
            game_menu* Menu = Game->Menus[(int) game_menu_state_ids::AT_START_MENU];

            UpdateMenu(Menu, Game->WindowWidth, Game->WindowHeight);
            DrawMenu(Game->Renderer, Menu);
        }
        else if(Game->State.StateID == game_state_id::PAUSED)
        {
            game_menu* Menu = Game->Menus[(int) game_menu_state_ids::PAUSED];

            UpdateMenu(Menu, Game->WindowWidth, Game->WindowHeight);
            DrawMenu(Game->Renderer, Menu);
        }
        else if(Game->State.StateID == game_state_id::PLAYING)
        {
            Update(Game, Game->Dt.count());

            DrawPlayers();
            DrawObjects();
        }
        
        SwapBuffers(Game->Renderer);
    }

    DestroyGame(Game);

    return EXIT_SUCCESS;
}

