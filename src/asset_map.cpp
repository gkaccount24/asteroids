#include "asset_map.h"

#define DEFAULT_MAP_CAPACITY 16

asset_map::asset_map() 
{
    Assets.resize(DEFAULT_MAP_CAPACITY);

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

    if(AssetID < BucketCount)
    {
        if(Assets[AssetID]->AssetCount == 0)
        {
            Assets[AssetID]->Asset = Asset;
            Assets[AssetID]->AssetCount++;
        }
    }
}

void asset_map::Remove(uint32_t AssetID) 
{

}

asset* asset_map::Get(uint32_t AssetID) 
{ 
    return nullptr; 
}