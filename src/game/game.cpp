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

bool LoadTexture(game* Game, std::string Key, std::string Path)
{
    if(!Path.empty())
    {
        SDL_Surface* Surface = nullptr;

        Surface = IMG_Load(Path.c_str());

        if(!Surface)
        {
            std::cout << "failed to load image: " << Path << std::endl;;
            std::cout << "IMG_GetError(): " << IMG_GetError() << std::endl;

            return false;
        }

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

        Texture->Position.X = 0;
        Texture->Position.Y = 0;
        Texture->Size.Width = Surface->w;
        Texture->Size.Height = Surface->h;
        Texture->Data = TextureData;

        Asset->Type = game_asset_type_id::TEXTURE;
        Asset->Data.Texture = Texture;
        Asset->ID = ++AssetID;
        Asset->Path = Path;

        AddAsset(Game->Assets, Key, Asset);

        SDL_DestroySurface(Surface);
        Surface = nullptr;

        return true;
    }

    return false;
}

bool LoadFont(game* Game, std::string Key, std::string Path, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor)
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
        Font->Data = FontData;

        SetRegularFontStyle(Font, FontSize, ForegroundColor, BackgroundColor, HoverColor);

        Asset->Type = game_asset_type_id::FONT;
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
    SDL_Color FontForegroundColor = SDL_Color { 0, 128, 0, SDL_ALPHA_OPAQUE    };
    SDL_Color FontBackgroundColor = SDL_Color { 0, 0, 0, SDL_ALPHA_TRANSPARENT };
    SDL_Color FontHoverColor      = SDL_Color { 0, 128, 128, SDL_ALPHA_OPAQUE  };

    LoadFont(Game, "Orbitron_Black_Font_12", "/home/nathan/Documents/asteroids/assets/Orbitron-Black.ttf", 12, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_Black_Font_18", "/home/nathan/Documents/asteroids/assets/Orbitron-Black.ttf", 18, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_Black_Font_24", "/home/nathan/Documents/asteroids/assets/Orbitron-Black.ttf", 24, FontForegroundColor, FontBackgroundColor, FontHoverColor);

    LoadFont(Game, "Orbitron_Regular_Font_12", "/home/nathan/Documents/asteroids/assets/Orbitron-Regular.ttf", 12, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_Regular_Font_18", "/home/nathan/Documents/asteroids/assets/Orbitron-Regular.ttf", 18, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_Regular_Font_24", "/home/nathan/Documents/asteroids/assets/Orbitron-Regular.ttf", 24, FontForegroundColor, FontBackgroundColor, FontHoverColor);

    LoadFont(Game, "Orbitron_Medium_Font_12", "/home/nathan/Documents/asteroids/assets/Orbitron-Medium.ttf", 12, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_Medium_Font_18", "/home/nathan/Documents/asteroids/assets/Orbitron-Medium.ttf", 18, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_Medium_Font_24", "/home/nathan/Documents/asteroids/assets/Orbitron-Medium.ttf", 24, FontForegroundColor, FontBackgroundColor, FontHoverColor);

    LoadFont(Game, "Orbitron_SemiBold_Font_12", "/home/nathan/Documents/asteroids/assets/Orbitron-SemiBold.ttf", 12, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_SemiBold_Font_18", "/home/nathan/Documents/asteroids/assets/Orbitron-SemiBold.ttf", 18, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_SemiBold_Font_24", "/home/nathan/Documents/asteroids/assets/Orbitron-SemiBold.ttf", 24, FontForegroundColor, FontBackgroundColor, FontHoverColor);

    LoadFont(Game, "Orbitron_Bold_Font_12", "/home/nathan/Documents/asteroids/assets/Orbitron-Bold.ttf", 12, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_Bold_Font_18", "/home/nathan/Documents/asteroids/assets/Orbitron-Bold.ttf", 18, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_Bold_Font_24", "/home/nathan/Documents/asteroids/assets/Orbitron-Bold.ttf", 24, FontForegroundColor, FontBackgroundColor, FontHoverColor);

    LoadFont(Game, "Orbitron_ExtraBold_Font_12", "/home/nathan/Documents/asteroids/assets/Orbitron-ExtraBold.ttf", 12, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_ExtraBold_Font_18", "/home/nathan/Documents/asteroids/assets/Orbitron-ExtraBold.ttf", 18, FontForegroundColor, FontBackgroundColor, FontHoverColor);
    LoadFont(Game, "Orbitron_ExtraBold_Font_24", "/home/nathan/Documents/asteroids/assets/Orbitron-ExtraBold.ttf", 24, FontForegroundColor, FontBackgroundColor, FontHoverColor);

    LoadTexture(Game, "UI_Textures", "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_IU.png");
    LoadTexture(Game, "Ship_Textures", "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_Ships.png");
    LoadTexture(Game, "Character_Textures", "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_Characters.png");
    LoadTexture(Game, "Background_Textures", "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_BackGrounds.png");
    LoadTexture(Game, "Projectile_Textures", "/home/nathan/Documents/asteroids/assets/SpaceShooterAssetPack_Projectiles.png");
}

void DestroyAssets(game* Game)
{
    auto Iter = std::begin(Game->Assets);
    auto End = std::end(Game->Assets);

    for(; Iter != End; Iter++)
    {
        if(Iter->second)
        {
            if(Iter->second->Type == game_asset_type_id::TEXTURE)
            {
                DestroyTexture(Iter->second->Data.Texture);

                Iter->second->Data.Texture = nullptr;
            }
            else if(Iter->second->Type == game_asset_type_id::FONT)
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

void OnSettings(game_state* GameState) { }
void OnSave(game_state* GameState) { }
void OnLoad(game_state* GameState) { }

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

void DestroyMenus(game* Game)
{
    uint32_t Count = Game->Menus.size();

    for(uint32_t Index = 0; Index < Count; Index++)
    {
        DestroyMenu(Game->Menus[Index]);
    }
}

void MakeMenus(game* Game)
{
    game_font* Font = GetFont(Game->Assets, "Orbitron_Regular_Font_18");
    game_menu* Menu = nullptr;

    std::vector<std::pair<std::string, on_click_handler>> MainMenuOptions 
    {
        { "Start Game", &OnStart },
        { "Load Game",  &OnLoad },
        { "Settings",   &OnSettings },
        { "Exit",       &OnStop }
    };

    Menu = MakeMenu(Game->Renderer, Font, MainMenuOptions);

    if(Menu)
    {
        Game->Menus.push_back(Menu);

        Menu = nullptr;
    }

    std::vector<std::pair<std::string, on_click_handler>> PauseMenuOptions 
    {
        { "Resume", &OnStart },
        { "Save",   &OnSave },
        { "Quit",   &OnQuit },
        { "Exit",   &OnStop }
    };

    Menu = MakeMenu(Game->Renderer, Font, PauseMenuOptions);

    if(Menu)
    {
        Game->Menus.push_back(Menu); 

        Menu = nullptr;
    }
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

    OnInit(Game);

    MakeMenus(Game);

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

