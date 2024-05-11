#include "game_menu.h"

static int MenuID;

void DestroyMenu(game_menu*& Menu)
{
    if(Menu)
    {
        uint32_t Count = Menu->Options.size();

        for(uint32_t Index = 0; Index < Count; Index++)
        {
            if(Menu->Options[Index])
            {
                delete Menu->Options[Index];
                Menu->Options[Index] = nullptr;
            }
        }

        delete Menu;
        Menu = nullptr;
    }
}

game_menu* MakeMenu(SDL_Renderer* Renderer, game_font* Font, std::vector<std::pair<std::string, on_click_handler>>& Options)
{
    SDL_assert(Renderer);

    uint32_t Count = Options.size();

    if(Font && Count > 0)
    {
        game_menu* Menu = new game_menu { };

        if(!Menu)
        {
            return nullptr;
        }

        Menu->Font = Font;
        Menu->MenuID = ++MenuID;

        for(uint32_t Index = 0; Index < Count; Index++)
        {
            game_texture* Texture = nullptr;

            Texture = RenderText(Renderer, Menu->Font, Options[Index].first);

            if(Texture)
            {
                game_menu_option* Option = new game_menu_option { };

                if(!Option)
                {
                    DestroyMenu(Menu);

                    break;
                }

                Option->Handler = Options[Index].second;
                Option->Text = Options[Index].first;
                Option->Index = Index;
                Option->Texture = Texture;

                Menu->Options.push_back(Option);
            }
        }

        return Menu;
    }

    return nullptr;
}