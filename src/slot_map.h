#ifndef SLOT_MAP_H
#define SLOT_MAP_H

#include "node.h"

#include <vector>
#include <cstdint>

template<typename t>
class slot_map 
{
    struct slot
    {
        uint32_t ID;
        t*       Data;
    };

public:

    slot_map():
        Free(nullptr),
        FreeCount(0),
        SlotCapacity(0)
    { }

    ~slot_map()
    {
        Destroy();
    }

public:

    inline uint32_t Size() const { return Slots.size(); }
    inline bool IsEmpty() const { return Free == nullptr; }
    inline uint32_t FreeSize() const { return FreeCount; }
    inline uint32_t Capacity() const { return SlotCapacity; }

public:

    t* At(uint32_t Idx) 
    {
        t* Data = nullptr;

        if(!Slots.empty() && Idx < Slots.size())
        {
            if(Slots[Idx]->ID > 0)
            {
                Data = Slots[Idx]->Data;
            }
        }

        return Data;
    }

public:

    uint32_t Insert(t&& Value)
    {
        if(Free) 
        {
            uint32_t SlotID = Free->Idx;

            *Slots[SlotID]->Data = std::forward<t>(Value);
            Slots[SlotID]->ID = SlotID;

            PopFree();

            return SlotID;
        }
        else
        {
            uint32_t SlotID = Slots.size();

            slot* Slot = new slot { 
                ++SlotID, 
                new t(std::forward<t>(Value))
            };

            Slots.push_back(Slot);

            SlotCapacity++;

            return SlotID;
        }

        return 0;
    }

    void Remove(uint32_t Idx)
    {
        if(Idx >= 0 && Idx < Slots.size())
        {
            Invalidate(Slots[Idx]);
            AddToFree(Idx);
        }
    }

    void Destroy()
    {
        uint32_t Count = Slots.size();

        for(uint32_t Idx = 0; Idx < Count; Idx++)
        {
            if(Slots[Idx]->Data)
            {
                delete Slots[Idx]->Data;
                Slots[Idx]->Data = nullptr;

                delete Slots[Idx];
                Slots[Idx] = nullptr;
            }
        }

        if(Free)
        {
            node* Node = Free;

            while(Node)
            {
                node* Next = Node->Next;

                delete Node;
                Node = nullptr;

                Node = Next;
            }
        }

        SlotCapacity = 0;
        Free = nullptr;
    }

    void Clear() 
    {
        uint32_t Count = Slots.size();

        for(uint32_t Idx = 0; Idx < Count; Idx++)
        {
            Invalidate(Slots[Idx]);
            AddToFree(Idx);
        }
    }

private:

    void PopFree()
    {
        if(Free)
        {
            node* Next = nullptr;

            if(Free->Next)
            {
                Next = Free->Next;
            }

            delete Free;
            Free = Next;

            FreeCount--;
        }
    }

    void AddToFree(uint32_t Idx)
    {
        if(node* Node = new node { nullptr, 0 })
        {
            Node->Idx = Idx;
            Node->Next = Free;

            Free = Node;

            FreeCount++;
        }
    }

    void Invalidate(slot* Slot)
    {
        if(Slot)
        {
            Slot->Data->Reset();
            Slot->ID = 0;
        }
    }

private:
    node*              Free;
    uint32_t           FreeCount;
    uint32_t           SlotCapacity;
    std::vector<slot*> Slots;
};

#endif