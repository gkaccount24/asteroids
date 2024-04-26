#include "asset_map.h"

#define DEFAULT_MAP_CAPACITY 16

/* HASHING MACRO */
#define Hash(Number) std::hash<uint32_t> { }(Number)

asset_map::asset_map():
    Capacity(DEFAULT_MAP_CAPACITY)
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
    Assets.resize(Capacity);

    for(uint32_t Idx = 0; Idx < Capacity; Idx++)
    {
        map_node* Node = new map_node { nullptr, 0, nullptr };

        Assets[Idx] = Node;
    }
}

void asset_map::Add(uint32_t AssetID, asset* Asset) 
{
    if(GetLoadFactor() > 0.75f)
    {
        // expand table
        // rehash
    }

    uint32_t HashCode = Hash(AssetID) % Capacity;
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

        map_node* Next = new map_node { nullptr, 0, nullptr };

        Next->Asset = Asset;
        Node->Next = Next;

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
    uint32_t HashCode = Hash(AssetID) % Capacity;
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
    uint32_t HashCode = Hash(AssetID) % Capacity;
    map_node* HashNode = Assets[HashCode];



    return nullptr; 
}