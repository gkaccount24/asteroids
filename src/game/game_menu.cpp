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

void game_menu::AddOption(std::string OptionText, on_click_handler Handler)
{
    game_menu_option* NewOption = new game_menu_option();

    NewOption->

}

// game_menu* CreateMenu(std::string FontKey, std::string FontPath, text_style_index StyleIndex, text_style (&Styles)[TEXT_STYLE_COUNT], std::vector<std::pair<std::string, on_click_handler>>& Options)
// {
//     game_menu* Menu = nullptr;
// 
//     if(!Options.empty())
//     {
//         std::size_t Count = Options.size();
// 
//         Menu = NewGameMenu();
// 
//         for(uint32_t Index = 0; Index < Count; Index++)
//         {
//             if(game_menu_option* Option = NewGameMenuOption(Menu))
//             {
//                 // initializing styling data
//                 Option->StyleIndex  = StyleIndex;
// 
//                 Option->Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].BackgroundColor = Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].BackgroundColor;
//                 Option->Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].ForegroundColor = Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].ForegroundColor;
//                 Option->Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].Style           = Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].Style;
//                 Option->Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].Size            = Styles[static_cast<std::size_t>(text_style_index::UNHOVERED)].Size;
//                 Option->Styles[static_cast<std::size_t>(text_style_index::HOVERED)].BackgroundColor = Styles[static_cast<std::size_t>(text_style_index::HOVERED)].BackgroundColor;
//                 Option->Styles[static_cast<std::size_t>(text_style_index::HOVERED)].ForegroundColor = Styles[static_cast<std::size_t>(text_style_index::HOVERED)].ForegroundColor;
//                 Option->Styles[static_cast<std::size_t>(text_style_index::HOVERED)].Style           = Styles[static_cast<std::size_t>(text_style_index::HOVERED)].Style;
//                 Option->Styles[static_cast<std::size_t>(text_style_index::HOVERED)].Size            = Styles[static_cast<std::size_t>(text_style_index::HOVERED)].Size;
// 
//                 // initialize text and positition/size data
//                 Option->Text        = Options[Index].first;
// 
//                 Option->Position.X  = 0.0f;
//                 Option->Position.Y  = 0.0f;
// 
//                 Option->Size.Width  = 0;
//                 Option->Size.Height = 0;
// 
//                 Menu->Options.push_back(Option);
//             }
//         }
//     }
// 
//     return Menu;
// }
// 
// void DestroyMenuOption(game_menu_option*& Option)
// {
//     if(Option)
//     {
//         DestroyTexture(Option->Texture);
// 
//         delete Option;
//         Option = nullptr;
//     }
// }
// 
// void DestroyMenu(game_menu*& Menu)
// {
//     if(Menu)
//     {
//         uint32_t Count = Menu->Options.size();
// 
//         for(uint32_t Index = 0; Index < Count; Index++)
//         {
//             DestroyMenuOption(Menu->Options[Index]);
//         }
// 
//         delete Menu;
//         Menu = nullptr;
//     }
// }