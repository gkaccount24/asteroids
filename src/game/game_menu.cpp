#include "game_menu.h"

static int MenuID;

game_menu* CreateMenu(text_style_index StyleIndex, text_style (&Styles)[TEXT_STYLE_COUNT], std::vector<std::pair<std::string, on_click_handler>>& Options)
{
    game_menu* Menu = nullptr;

    if(!Options.empty())
    {
        std::size_t Count = Options.size();

        Menu = new game_menu { };

        if(!Menu)
        {
            std::cout << "memory allocation failed..." << std::endl;

            return nullptr;
        }

        Menu->MenuID = ++MenuID;

        for(uint32_t Index = 0; Index < Count; Index++)
        {
            game_menu_option* Option = new game_menu_option { };

            if(!Option)
            {
                DestroyMenu(Menu);

                break;
            }

            Option->Text = new game_text { };

            if(!Option->Text)
            {
                DestroyMenu(Menu);

                break;
            }

            Option->Text->StyleIndex  = StyleIndex;

            Option->Text->Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].BackgroundColor = Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].BackgroundColor;
            Option->Text->Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].ForegroundColor = Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].ForegroundColor;
            Option->Text->Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].Style           = Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].Style;
            Option->Text->Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].Size            = Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].Size;

            Option->Text->Styles[static_cast<std::size_t>(text_style_index::HOVERED)].BackgroundColor = Styles[static_cast<std::size_t>(text_style_index::HOVERED)].BackgroundColor;
            Option->Text->Styles[static_cast<std::size_t>(text_style_index::HOVERED)].ForegroundColor = Styles[static_cast<std::size_t>(text_style_index::HOVERED)].ForegroundColor;
            Option->Text->Styles[static_cast<std::size_t>(text_style_index::HOVERED)].Style           = Styles[static_cast<std::size_t>(text_style_index::HOVERED)].Style;
            Option->Text->Styles[static_cast<std::size_t>(text_style_index::HOVERED)].Size            = Styles[static_cast<std::size_t>(text_style_index::HOVERED)].Size;

            Option->Text->StringData  = Options[Index].first;
            Option->Text->Position.X  = 0.0f;
            Option->Text->Position.Y  = 0.0f;
            Option->Text->Size.Width  = 0;
            Option->Text->Size.Height = 0;

            Menu->Options.push_back(Option);
        }
    }

    return Menu;
}

void DestroyMenuOption(game_menu_option*& Option)
{
    if(Option)
    {
        DestroyText(Option->Text);

        delete Option;
        Option = nullptr;
    }
}

void DestroyMenu(game_menu*& Menu)
{
    if(Menu)
    {
        uint32_t Count = Menu->Options.size();

        for(uint32_t Index = 0; Index < Count; Index++)
        {
            DestroyMenuOption(Menu->Options[Index]);
        }

        delete Menu;
        Menu = nullptr;
    }
}