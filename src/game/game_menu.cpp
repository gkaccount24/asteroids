#include "game_menu.h"

static int MenuID;

static game_menu* MainMenu;
static game_menu* PauseMenu;

void DestroyMenu(game_menu*& Menu)
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

void MakeMenu(game_menu* Menu, std::pair<std::string, on_click_handler>* MenuOptions, uint32_t MenuOptionCount)
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

void AddMenuOption(game_menu* Menu, std::string OptionText, on_click_handler OnClickHandler)
{
    // SDL_Texture* Texture = nullptr;
    // Texture = CreateTexture(Menu->Font, OptionText);

    if(Texture)
    {
        game_menu_option* MenuOption = new game_menu_option { };

        MenuOption->Texture = Texture;
        MenuOption->Index   = ++MenuOption->Index;
        MenuOption->Handler = OnClickHandler;

        Menu->Options.push_back(MenuOption);
    }
}