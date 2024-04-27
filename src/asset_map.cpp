#include "asset_map.h"

#define DEFAULT_MAP_CAPACITY 16

/* HASHING MACRO */
#define Hash(Number) std::hash<uint32_t> { }((Number))

asset_map::asset_map():
    TotalAssetCount(0)
{
    Initialize();
}

asset_map::~asset_map() 
{
    Destroy();
}

void asset_map::Initialize()
{
    Resize(DEFAULT_MAP_CAPACITY);
}

void asset_map::Destroy()
{
    uint32_t HashNodeCount = Assets.size();

    for(uint32_t Idx = 0; Idx < HashNodeCount; Idx++)
    {
        map_node* HashNode = Assets[Idx];

        if(HashNode->AssetCount > 0)
        {
            map_node* Node = Assets[Idx];

            while(Node)
            {
                if(Node->Asset)
                {
                    asset*& Asset = HashNode->Asset;

                    DeleteAsset(Asset);
                }

                Node = Node->Next;
            }
        }
    }
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

    for(uint32_t Idx = 0; Idx < HashNodeCount; Idx++)
    {
        map_node* Node = OldAssets[Idx];

        while(Node)
        {
            delete Node;
            Node = nullptr;
        }
    }
}

void asset_map::Add(uint32_t AssetID, asset* Asset) 
{
    if(Asset)
    {
        // fewer amount of collisions
        // occur when the load factor is lower
        if(GetLoadFactor() > 0.5f)
        {
            uint32_t NextTableSize = GetNextTableSize();

            Rehash(NextTableSize);
        }

        uint32_t HashCode = Hash(AssetID) % Assets.size();
        map_node* HashNode = Assets[HashCode];

        if(HashNode->AssetCount == 0)
        {
            HashNode->Asset = Asset;
            HashNode->AssetCount++;

            TotalAssetCount++;
        }
        else if(HashNode->AssetCount >= 1)
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

        while(Node)
        {
            asset*& Asset = Node->Asset;

            if(Asset && Asset->GetAssetID() == AssetID)
            {
                DeleteAsset(Asset);

                HashNode->AssetCount--;
                TotalAssetCount--;

                break;
            }

            Node = Node->Next;
        }
    }
}

asset* asset_map::Get(uint32_t AssetID) 
{ 
    uint32_t HashCode = Hash(AssetID) % Assets.size();

    map_node* HashNode = Assets[HashCode];

    asset* Asset = nullptr;

    if(HashNode->AssetCount > 0)
    {
        if(HashNode->Asset && HashNode->Asset->GetAssetID() == AssetID)
        {
            Asset = HashNode->Asset;
        }
        else
        {
            map_node* Node = HashNode->Next;

            while(Node)
            {
                if(Node->Asset && Node->Asset->GetAssetID() == AssetID)
                {
                    Asset = Node->Asset;

                    break;
                }
            }
        }
    }

    return Asset;
}

asset* asset_map::operator[](uint32_t AssetID)
{
    uint32_t HashCode = Hash(AssetID) % Assets.size();

    map_node* Node = Assets[HashCode];

    while(Node)
    {
        asset* Asset = Node->Asset;

        if(Asset->GetAssetID() == AssetID)
        {
            return Asset;
        }

        Node = Node->Next;
    }

    return nullptr;
}