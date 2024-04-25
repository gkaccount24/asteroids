#include "asset_map.h"

#define DEFAULT_MAP_CAPACITY 16

/* HASHING FUNCTION */

uint32_t Hash(uint32_t Value, uint32_t Capacity)
{
    return Value % Capacity;
}

asset_map::asset_map():
    Capacity(DEFAULT_MAP_CAPACITY)
{
    Assets.resize(Capacity);
}

asset_map::~asset_map() 
{
    uint32_t BucketCount = Assets.size();

    for(uint32_t Idx = 0; Idx < BucketCount; Idx++)
    {
        delete Assets[Idx]->Asset;
        Assets[Idx]->Asset = nullptr;

        delete Assets[Idx];
        Assets[Idx] = nullptr;
    }
}

void asset_map::Add(uint32_t AssetID, asset* Asset) 
{
    uint32_t BucketCount = Assets.size();
    uint32_t HashCode = Hash(AssetID, Capacity);

    if(Assets[HashCode]->AssetCount == 0)
    {
        Assets[HashCode]->Asset = Asset;
        Assets[HashCode]->AssetCount++;
    }
}

void asset_map::Remove(uint32_t AssetID) 
{
    uint32_t BucketCount = Assets.size();
    uint32_t HashCode = Hash(AssetID, Capacity);

    if(Assets[HashCode]->AssetCount > 0)
    {

    }
}

asset* asset_map::Get(uint32_t AssetID) 
{ 
    uint32_t HashCode = Hash(AssetID, Capacity);
    return nullptr; 
}