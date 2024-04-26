#include "asset_map.h"

#define DEFAULT_MAP_CAPACITY 16

/* HASHING MACRO */
#define Hash(Number) std::hash<uint32_t> { }(Number)

asset_map::asset_map():
    TotalAssetCount(0)
{
    Initialize();
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

void asset_map::Initialize()
{
    Resize(DEFAULT_MAP_CAPACITY);
}

void asset_map::Resize(uint32_t NextTableSize)
{
    Assets.resize(NextTableSize);

    for(uint32_t Idx = 0; Idx < NextTableSize; Idx++)
    {
        map_node* Node = new map_node { nullptr, 0, nullptr };

        Assets[Idx] = Node;
    }
}

void asset_map::Rehash(uint32_t NextTableSize)
{
    std::vector<map_node*> OldAssets = std::move(Assets);

    uint32_t HashNodeCount = OldAssets.size();

    Assets.clear();

    Resize(NextTableSize);

    for(uint32_t Idx = 0; Idx < HashNodeCount; Idx++)
    {
        map_node* HashNode = OldAssets[Idx];

        if(HashNode->AssetCount > 0)
        {
            map_node* Node = OldAssets[Idx];

            while(Node)
            {
                if(Node->Asset)
                {
                    Add(Node->Asset->GetAssetID(), Node->Asset);
                }

                Node = Node->Next;
            }
        }
    }
}

void asset_map::Add(uint32_t AssetID, asset* Asset) 
{
    // fewer amount of collisions
    // occur when the load factor is lower
    if(GetLoadFactor() > 0.5f)
    {
        Rehash(GetNextTableSize());
    }

    uint32_t HashCode = Hash(AssetID) % Assets.size();
    map_node* HashNode = Assets[HashCode];

    if(HashNode->AssetCount == 0)
    {
        HashNode->Asset = Asset;
        HashNode->AssetCount++;
    }
    else if(HashNode->AssetCount > 0)
    {
        map_node* Node = Assets[HashCode];

        while(Node->Next)
            Node = Node->Next;

        // map_node* Next = new map_node { nullptr, 0, nullptr };
        // Next->Asset = Asset;
        // Node->Next = Next;

        HashNode->AssetCount++;
        TotalAssetCount++;
    }
}

void asset_map::DeleteAsset(asset*& Asset)
{
    delete Asset;
    Asset = nullptr;
}

void asset_map::Remove(uint32_t AssetID) 
{
    uint32_t HashCode = Hash(AssetID) % Assets.size();
    map_node* HashNode = Assets[HashCode];

    if(HashNode->AssetCount > 0)
    {
        map_node* Node = Assets[HashCode];
        uint32_t RemoveCount = 0;

        while(Node)
        {
            asset*& Asset = Node->Asset;

            if(Asset && Asset->GetAssetID() == AssetID)
            {
                DeleteAsset(Asset);

                TotalAssetCount--;
                RemoveCount++; 

                break;
            }

            Node = Node->Next;
        }

        HashNode->AssetCount -= RemoveCount;
    }
}

asset* asset_map::Get(uint32_t AssetID) 
{ 
    uint32_t HashCode = Hash(AssetID) % Assets.size();
    map_node* HashNode = Assets[HashCode];

    return nullptr; 
}