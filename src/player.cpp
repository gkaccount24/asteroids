#include "player.h"

player::player():
    Starship(nullptr)
{ }

player::player(starship* PlayerStarship):
    Starship(PlayerStarship)
{ }

player::~player()
{
    if(Starship)
    {
        delete Starship;
        Starship = nullptr;
    }
}

// void player::CenterPlayer(SDL_Window* Window)
// {
//     int WindowW = 0;
//     int WindowH = 0;
// 
//     SDL_GetWindowSize(Window, &WindowW, &WindowH);
// 
//     Player->Object.XPos = (WindowW / 2) - (Player->Object.Width / 2);
//     Player->Object.YPos = (WindowH / 2) - (Player->Object.Height / 2);
// }
// 
// void player::Draw(SDL_Renderer* Renderer, SDL_Texture* Texture)
// {
//     SDL_Rect Rect 
//     {
//         Player->Object.XPos, 
//         Player->Object.YPos,
//         Player->Object.Width, 
//         Player->Object.Height
//     };
// 
//     SDL_RenderCopyEx(Renderer, Texture, nullptr, &Rect, Player->Object.Angle, nullptr, SDL_FLIP_NONE);
// }

