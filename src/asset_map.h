#ifndef ASSET_MAP_H
#define ASSET_MAP_H

#include "asset.h"

#include <string>
#include <vector>
#include <cstdint>

struct map_node 
{
    asset*    Asset;
    uint32_t  AssetCount;
    map_node* Next;
};

class asset_map 
{

public:
    asset_map();
    ~asset_map();

public:
    void Add(uint32_t AssetID, asset* Asset);
    void Remove(uint32_t AssetID);
    asset* Get(uint32_t AssetID);

private:
    std::vector<map_node*> Assets;

};

#endif