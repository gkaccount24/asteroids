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

private:
    asset_map(asset_map&& Map) = delete;
    asset_map(const asset_map& Map) = delete;

public:
    void Add(uint32_t AssetID, asset* Asset);
    void Remove(uint32_t AssetID);
    asset* Get(uint32_t AssetID);

    /* OPERATOR OVERLOADS */
public:
    asset* operator[](uint32_t Index);

private:
    void Initialize();
    void DeleteAsset(asset*& Asset);

    void Rehash(uint32_t NextTableSize);
    void Resize(uint32_t NextTableSize);

public:
    inline uint32_t GetTotalAssetCount() const { return TotalAssetCount; }

private:
    inline float GetLoadFactor() const { return TotalAssetCount / Assets.size(); }
    inline uint32_t GetNextTableSize() const { return Assets.size() * 2; }

private:
    std::vector<map_node*> Assets;
    uint32_t               TotalAssetCount;
};

#endif