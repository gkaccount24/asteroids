#include "game_menu.h"

game_menu_option::game_menu_option() 
{
    Texture = nullptr;

    Position.X = 0.0f;
    Position.Y = 0.0f;

    Size.Width = 0;
    Size.Height = 0;
}

game_menu_option::~game_menu_option() 
{
    Destroy();
}

void game_menu_option::Destroy()
{
    Texture->Destroy();

    delete Texture;
    Texture = nullptr;
}

void game_menu_option::SetStyle(menu_text_style_index OptionStyleIndex, menu_text_style(& OptionStyles)[2])
{
    StyleIndex = OptionStyleIndex;

    Styles[static_cast<std::size_t>(menu_text_style_index::UNHOVERED)].ForegroundColor = OptionStyles[static_cast<std::size_t>(menu_text_style_index::UNHOVERED)].ForegroundColor;
    Styles[static_cast<std::size_t>(menu_text_style_index::UNHOVERED)].BackgroundColor = OptionStyles[static_cast<std::size_t>(menu_text_style_index::UNHOVERED)].BackgroundColor;
    Styles[static_cast<std::size_t>(menu_text_style_index::UNHOVERED)].Style           = OptionStyles[static_cast<std::size_t>(menu_text_style_index::UNHOVERED)].Style;
    Styles[static_cast<std::size_t>(menu_text_style_index::UNHOVERED)].Size            = OptionStyles[static_cast<std::size_t>(menu_text_style_index::UNHOVERED)].Size;

    Styles[static_cast<std::size_t>(menu_text_style_index::HOVERED)].ForegroundColor = OptionStyles[static_cast<std::size_t>(menu_text_style_index::HOVERED)].ForegroundColor;
    Styles[static_cast<std::size_t>(menu_text_style_index::HOVERED)].BackgroundColor = OptionStyles[static_cast<std::size_t>(menu_text_style_index::HOVERED)].BackgroundColor;
    Styles[static_cast<std::size_t>(menu_text_style_index::HOVERED)].Style           = OptionStyles[static_cast<std::size_t>(menu_text_style_index::HOVERED)].Style;
    Styles[static_cast<std::size_t>(menu_text_style_index::HOVERED)].Size            = OptionStyles[static_cast<std::size_t>(menu_text_style_index::HOVERED)].Size;
}

game_menu::game_menu()
{
    Font = nullptr;
    Position.X = 0;
    Position.Y = 0;
    Size.Width = 0;
    Size.Height = 0;
}

game_menu::~game_menu()
{
    Destroy();
}

void game_menu::Destroy()
{
    std::size_t Count = Options.size();

    for(std::size_t Index = 0; Index < Count; Index++)
    {
        Options[Index]->Destroy();

        delete Options[Index];
        Options[Index] = nullptr;
    }
}

void game_menu::AddOption(menu_text_style_index OptionStyleIndex, menu_text_style(& OptionStyles)[2], std::string OptionText, on_click_handler ClickHandler)
{
    game_menu_option* NewOption = new game_menu_option();

    NewOption->SetStyle(OptionStyleIndex, OptionStyles);
    NewOption->SetText(OptionText);
    NewOption->SetClickHandler(ClickHandler);

    Options.push_back(NewOption);
}