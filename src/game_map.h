#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <fstream>
#include <vector>
#include <string>

struct game_map
{
    std::string  TextureKey;
    std::fstream File;
};

#endif