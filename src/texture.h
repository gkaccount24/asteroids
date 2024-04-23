#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

#include <string>

class texture 
{

public:

    texture(SDL_Texture* TextureData, std::string TexturePath, int Width, int Height);
    ~texture();

private:

    SDL_Texture* Data;

    std::string  Path;
    int          Width;
    int          Height;
};

// SDL_Texture* GetTextureData(std::unordered_map<std::string, texture*>& Textures, std::string Key)
// {
//     auto Entry = Textures.find(Key);
// 
//     if(Entry != std::end(Textures))
//     {
//         return Entry->second->Data;
//     }
// 
//     return nullptr;
// }

#endif