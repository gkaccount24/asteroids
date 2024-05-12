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

void OnStart() 
{
    // if(GameState->StateID == game_state_id::AT_START_MENU)
    // {
    //     GameState->LastStateID = GameState->StateID;
    //     GameState->StateID = game_state_id::PLAYING;
    // }
}

void OnPause() 
{
    // if(GameState->StateID == game_state_id::PLAYING)
    // {
    //     GameState->LastStateID = GameState->StateID;
    //     GameState->StateID = game_state_id::PAUSED;
    // }
}

void OnStop() 
{
    // if(GameState->StateID == game_state_id::AT_START_MENU ||
    //    GameState->StateID == game_state_id::PLAYING || 
    //    GameState->StateID == game_state_id::PAUSED)
    // {
    //     GameState->LastStateID = GameState->StateID;
    //     GameState->StateID = game_state_id::STOPPED;
    // }
}

void OnSettings() { }
void OnSave() { }
void OnLoad() { }

void OnQuit() 
{
    // if(GameState->StateID == game_state_id::PAUSED)
    // {
    //     GameState->LastStateID = GameState->StateID;
    //     GameState->StateID = game_state_id::AT_START_MENU;
    // }
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

bool PrepareToLoadTextureAssets(game* Game, std::vector<asset_load*>& AssetsToLoad)
{
    AssetsToLoad.push_back(new asset_load { game_asset_type::TEXTURE, "UI_Textures",         "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_IU.png"          });
    AssetsToLoad.push_back(new asset_load { game_asset_type::TEXTURE, "Ship_Textures",       "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_Ships.png"       });
    AssetsToLoad.push_back(new asset_load { game_asset_type::TEXTURE, "Character_Textures",  "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_Characters.png"  });
    AssetsToLoad.push_back(new asset_load { game_asset_type::TEXTURE, "Background_Textures", "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_BackGrounds.png" });
    AssetsToLoad.push_back(new asset_load { game_asset_type::TEXTURE, "Projectile_Textures", "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_Projectiles.png" });

    return true;
}

void PrepareToLoadSoundAssets(game* Game, std::vector<asset_load*>& AssetsToLoad)
{

}

bool PrepareToLoadFontAssetForMenu(game* Game, game_menu* Menu)
{
    asset_load* AssetLoad = new asset_load { };

    // AssetLoad->Key  = "Orbitron-Regular_Font";
    // AssetLoad->Path = "/home/nathan/Documents/asteroids/assets/Orbitron-Regular.ttf";

    AssetsToLoad.push_back(AssetLoad);

    // Game->Menus.push_back(std::make_pair("Orbitron_Font", StartMenu));
    // game_menu* PauseMenu = CreateMenu(StyleIndex, Styles, StartMenuOptions);
    // if(!PauseMenu)
    // {
    //     std::cout << "failed to create pause menu..." << std::endl;
    //     return false;
    // }
    // Game->Menus.push_back(std::make_pair("Orbitron_Font", PauseMenu));

    return true;
}

bool PrepareToLoadMenuAssets(game* Game, std::vector<asset_load*>& AssetsToLoad)
{
    // typedef std::vector<std::pair<std::string, on_click_handler>> menu_option_list;
    // typedef std::vector<std::pair<asset_info, menu_option_list&>> menu_list;
    // menu_option_list StartMenuOptions
    // {
    //     { "Start Game", &OnStart    },
    //     { "Load Game",  &OnLoad     },
    //     { "Settings",   &OnSettings },
    //     { "Exit",       &OnStop     }
    // };
    // menu_option_list PauseMenuOptions
    // {
    //     { "Resume", &OnStart },
    //     { "Save",   &OnSave  },
    //     { "Quit",   &OnQuit  },
    //     { "Exit",   &OnStop  }
    // };
    // menu_list Menus;

    text_style_index StyleIndex      = text_style_index::UNHOVERED;

    SDL_Color ForegroundColor        = SDL_Color { 0, 128, 0, SDL_ALPHA_OPAQUE      };
    SDL_Color BackgroundColor        = SDL_Color { 0,   0, 0, SDL_ALPHA_TRANSPARENT };
    SDL_Color HoveredForegroundColor = SDL_Color { 0, 128, 0, SDL_ALPHA_OPAQUE      };
    SDL_Color HoveredBackgroundColor = SDL_Color { 0,   0, 0, SDL_ALPHA_TRANSPARENT };

    int Style = TTF_STYLE_NORMAL;
    int Size  = 12;

    text_style Styles[TEXT_STYLE_COUNT] 
    {
        text_style { ForegroundColor,        BackgroundColor,        Style, Size },
        text_style { HoveredForegroundColor, HoveredBackgroundColor, Style, Size }
    };

    std::size_t MenuCount = 0; // Menus.size();

    for(std::size_t Index = 0; Index < MenuCount; Index++)
    {
        game_menu* Menu = CreateMenu(StyleIndex, Styles, 0);

        // if(!Menu)
        // {
        //     std::cout << "failed to create menu..." << std::endl;
        //     break;
        // }
    }
}

bool PrepareForAssetLoading(game* Game)
{
    // PrepareMenusForAssetLoading(Game);

    return true;
}

void LoadAssets(game* Game)
{
    std::vector<asset_load*> AssetsToLoad;

    // PrepareToLoadFontAssets(Game, AssetsToLoad);
    PrepareToLoadTextureAssets(Game, AssetsToLoad);
    PrepareToLoadSoundAssets(Game, AssetsToLoad);

    std::size_t AssetCount = AssetsToLoad.size();

    for(std::size_t Index = 0; Index < AssetCount; Index++)
    {
        game_asset* Asset = nullptr;

        std::string Key = AssetsToLoad[Index]->Key;
        std::string Path = AssetsToLoad[Index]->Path;

        if(AssetsToLoad[Index]->Type == game_asset_type::FONT)
        {
            int FontStyle = AssetsToLoad[Index]->Font.Style;
            int FontSize = AssetsToLoad[Index]->Font.Size;

            if(Asset = LoadFont(FontStyle, FontSize, Path))
            {
                // do something with this font handle
                // like create menus or something
                // if that is the font assets
                // purpose

            }
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

void DestroyMenus(game* Game)
{
    std::size_t Count = Game->Menus.size();

    for(std::size_t Index = 0; Index < Count; Index++)
    {
        game_menu*& Menu = Game->Menus[Index];

        DestroyMenu(Menu);
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
    PrepareForAssetLoading(Game);
    LoadAssets(Game);
}

uint32_t AddObject(game_object_map* Map, game_object* Object)
{
    // if(!Map->FreeObjectEntries.empty())
    // {
    //     auto Entry = Map->Entries.at(Map->FreeObjectEntries.back());

    //     if(Entry)
    //     {
    //         delete Entry;

    //         Entry = nullptr;
    //     }

    //     Entry = Object;

    //     Map->FreeObjectEntries.pop_back();

    //     return Entry->WorldID;
    // }
    // else
    // {
    //     auto Entry = Map->Entries[++ObjectID] = Object;

    //     return ObjectID;
    // }

    return 0;
}

void FreeObject(game_object_map* Map, game_object* Object)
{
    // auto Entry = Map->Entries.find(Object->WorldID);

    // if(Entry != std::end(Map->Entries))
    // {
    //     Map->FreeObjectEntries.push_back(Object->WorldID);

    //     if(Entry->second)
    //     {
    //         delete Entry->second;

    //         Entry->second = nullptr;
    //     }
    // }
}

// uint32_t SaveObject(game* Game, game_object* Object)
// {
//     uint32_t WorldID = AddObject(&Game->ObjectMap, Object);
// 
//     return WorldID;
// }


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

        // float Width = Menu->Options[Index];
        // float Height = Menu->Options[Index];

        float PositionX = Menu->Position.X;
        float PositionY = Menu->Position.Y;

        // Menu->Options[Index]->Size.Width = Width;
        // Menu->Options[Index]->Size.Height = Height;
        // Menu->Options[Index]->Position.X = ((MenuWidth - Width) / 2.0f) + PositionX;
        // Menu->Options[Index]->Position.Y = Height * Index + PositionY;
    }
}

void DrawMenuOption(SDL_Renderer* Renderer, game_menu_option* MenuOption, SDL_Color Color)
{
    SDL_Texture* Texture = MenuOption->Text->Texture->Handle;

    SDL_FRect SourceRECT 
    {
        MenuOption->Text->Texture->Position.X,
        MenuOption->Text->Texture->Position.Y,

        static_cast<float>(MenuOption->Text->Texture->Size.Width),
        static_cast<float>(MenuOption->Text->Texture->Size.Height)
    };

    SDL_FRect DestRECT
    {
        MenuOption->Text->Texture->Position.X,
        MenuOption->Text->Texture->Position.Y,

        static_cast<float>(MenuOption->Text->Texture->Size.Width),
        static_cast<float>(MenuOption->Text->Texture->Size.Height)
    };

    // Draw(Renderer, Texture, SourceRECT, DestRECT, 0.0, Color);
}

void DrawMenu(SDL_Renderer* Renderer, game_menu* Menu) 
{
    std::size_t Count = Menu->Options.size();

    for(std::size_t Index = 0; Index < Count; Index++)
    {
        game_menu_option* MenuOption = Menu->Options[Index];
        SDL_Texture* TextureHandle   = MenuOption->Text->Texture->Handle;
        SDL_Color Color              = MenuOption->Text->Styles[(int) MenuOption->Text->StyleIndex].ForegroundColor;

        SDL_FRect SourceRECT 
        {
            0, //MenuOption->Texture->Position.X,
            0, //MenuOption->Texture->Position.Y,

            0, //static_cast<float>(MenuOption->Texture->Size.Width),
            0, //static_cast<float>(MenuOption->Texture->Size.Height)
        };

        SDL_FRect DestRECT
        {
            0, //MenuOption->Position.X,
            0, //MenuOption->Position.Y,

            0, //static_cast<float>(MenuOption->Size.Width),
            0, //static_cast<float>(MenuOption->Size.Height)
        };

        // Draw(Renderer, Texture, SourceRECT, DestRECT, 0.0, Color);
    }
}

void HandleEvents(game* Game)
{
    SDL_Event Evt { };

    while(SDL_PollEvent(&Evt))
    {
        if(Evt.type == SDL_EVENT_QUIT)
        {
            // OnQuit(&Game->State);

            break;
        }

        else if(Evt.type == SDL_EVENT_MOUSE_MOTION)
        {
            if(Game->State.StateID == game_state_id::AT_START_MENU) 
            {
                game_menu* Menu = Game->Menus[0];

                int MenuEndX = 0; // Menu->Position.X + Menu->Size.Width;
                int MenuEndY = 0; // Menu->Position.Y + Menu->Size.Height;

                int MenuStartX = 0; // Menu->Position.X;
                int MenuStartY = 0; // Menu->Position.Y;

                if(Evt.motion.x >= MenuStartX && Evt.motion.x <= MenuEndX &&
                   Evt.motion.y >= MenuStartY && Evt.motion.y <= MenuEndY)
                {
                    std::size_t OptionCount = Menu->Options.size();

                    for(std::size_t Index = 0; Index < OptionCount; Index++)
                    {
                        // MenuEndX = Menu->Options[Index]->Position.X + Menu->Options[Index]->Size.Width;
                        // MenuEndY = Menu->Options[Index]->Position.Y + Menu->Options[Index]->Size.Height;

                        // MenuStartX = Menu->Options[Index]->Position.X;
                        // MenuStartY = Menu->Options[Index]->Position.Y;

                        if(Evt.motion.x >= MenuStartX && Evt.motion.x <= MenuEndX &&
                           Evt.motion.y >= MenuStartY && Evt.motion.y <= MenuEndY)
                        {
                            // Menu->Options[Index]->ColorIndex = font_color_index::HOVERED;

                            break;
                        }
                        else
                        {
                            // Menu->Options[Index]->ColorIndex = font_color_index::FOREGROUND;
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
            game_menu* Menu = Game->Menus[0];

            UpdateMenu(Menu, Game->WindowWidth, Game->WindowHeight);
            DrawMenu(Game->Renderer, Menu);
        }
        else if(Game->State.StateID == game_state_id::PAUSED)
        {
            game_menu* Menu = Game->Menus[1];

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

