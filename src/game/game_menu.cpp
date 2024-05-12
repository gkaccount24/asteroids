#include "game_menu.h"

static int MenuID;

game_menu* CreateMenu(SDL_Renderer* Renderer, game_font* Font, text_style_index StyleIndex, text_style(& Styles)[TEXT_STYLE_COUNT], std::vector<std::pair<std::string, on_click_handler>>& Options)
{
    uint32_t Count = Options.size();

    if(Count > 0)
    {
        game_menu* Menu = new game_menu { };

        if(!Menu)
        {
            std::cout << "memory allocation failed..." << std::endl;

            return nullptr;
        }

        Menu->MenuID = ++MenuID;
        Menu->Font   = Font;

        for(uint32_t Index = 0; Index < Count; Index++)
        {
            game_texture* Texture = RenderText(Renderer, Font, StyleIndex, Styles, Options[Index].first);

            if(!Texture)
            {
                std::cout << "Failed to render menu option text..." << std::endl;

                DestroyMenu(Menu);
                
                break;
            }

            game_menu_option* Option = new game_menu_option { };

            // struct game_menu_option 
            // {
            //     game_text*       Text;
            //     on_click_handler OnClick;
            // };

            if(!Option)
            {
                DestroyMenu(Menu);

                break;
            }

            Option->Text = new game_text { };

            Option->Text->Style[static_cast<uint32_t>(text_style_index::UNHOVERED)].BackgroundColor = Styles[static_cast<uint32_t>(text_style_index::UNHOVERED)].BackgroundColor;
            Option->Text->Style[static_cast<uint32_t>(text_style_index::UNHOVERED)].ForegroundColor = Styles[static_cast<uint32_t>(text_style_index::UNHOVERED)].ForegroundColor;
            Option->Text->Style[static_cast<uint32_t>(text_style_index::UNHOVERED)].Style           = Styles[static_cast<uint32_t>(text_style_index::UNHOVERED)].Style;
            Option->Text->Style[static_cast<uint32_t>(text_style_index::UNHOVERED)].Size            = Styles[static_cast<uint32_t>(text_style_index::UNHOVERED)].Size;

            Option->Text->Style[static_cast<uint32_t>(text_style_index::HOVERED)].BackgroundColor = Styles[static_cast<uint32_t>(text_style_index::HOVERED)].BackgroundColor;
            Option->Text->Style[static_cast<uint32_t>(text_style_index::HOVERED)].ForegroundColor = Styles[static_cast<uint32_t>(text_style_index::HOVERED)].ForegroundColor;
            Option->Text->Style[static_cast<uint32_t>(text_style_index::HOVERED)].Style           = Styles[static_cast<uint32_t>(text_style_index::HOVERED)].Style;
            Option->Text->Style[static_cast<uint32_t>(text_style_index::HOVERED)].Size            = Styles[static_cast<uint32_t>(text_style_index::HOVERED)].Size;

            Option->Text->StyleIndex  = StyleIndex;
            Option->Text->Texture     = Texture;
            Option->Text->StringData  = Options[Index].first;
            Option->Text->Position.X  = 0.0f;
            Option->Text->Position.Y  = 0.0f;
            Option->Text->Size.Width  = 0;
            Option->Text->Size.Height = 0;

            Menu->Options.push_back(Option);
        }

        return Menu;
    }

    return nullptr;
}

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