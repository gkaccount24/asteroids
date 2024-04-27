#include "object_map.h"

object_map::object_map():
    Free(nullptr),
    FreeCount(0),
    SlotCapacity(0)
{ }

object_map::~object_map()
{
    Destroy();
}

uint32_t object_map::Size() const 
{ 
    uint32_t Value = Slots.size(); 

    return Value;
}

bool object_map::Empty() const 
{ 
    bool Value = FreeCount == Slots.size(); 

    return Value;
}

uint32_t object_map::FreeSize() const 
{ 
    return FreeCount; 
}

uint32_t object_map::Capacity() const 
{ 
    return SlotCapacity; 
}

space_object* object_map::Get(uint32_t Idx) 
{
    space_object* Data = nullptr;

    if(!Slots.empty() && Idx < Slots.size())
    {
        if(Slots[Idx]->ID > 0)
        {
            Data = Slots[Idx]->Data;
        }
    }

    return Data;
}

uint32_t object_map::Add(space_object* Value)
{
    if(Value)
    {
        if(Free) 
        {
            uint32_t SlotID = Free->Idx;

            Slots[SlotID]->Data = Value;
            Slots[SlotID]->ID = SlotID;

            PopFree();

            return SlotID;
        }
        else
        {
            uint32_t SlotID = Slots.size();

            slot* Slot = new slot { 
                ++SlotID, 
                Value
            };

            Slots.push_back(Slot);

            SlotCapacity++;

            return SlotID;
        }
    }

    return 0;
}

void object_map::Remove(uint32_t Idx)
{
    if(Idx >= 0 && Idx < Slots.size())
    {
        Invalidate(Slots[Idx]);
        AddToFree(Idx);
    }
}

void object_map::Destroy()
{
    uint32_t Count = Slots.size();

    for(uint32_t Idx = 0; Idx < Count; Idx++)
    {
        if(Slots[Idx])
        {
            if(Slots[Idx]->Data)
            {
                delete Slots[Idx]->Data;
                Slots[Idx]->Data = nullptr;

                delete Slots[Idx];
                Slots[Idx] = nullptr;
            }
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

void object_map::Clear() 
{
    uint32_t Count = Slots.size();

    for(uint32_t Idx = 0; Idx < Count; Idx++)
    {
        Invalidate(Slots[Idx]);
        AddToFree(Idx);
    }
}

void object_map::PopFree()
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

void object_map::AddToFree(uint32_t Idx)
{
    if(node* Node = new node { nullptr, 0 })
    {
        Node->Idx = Idx;
        Node->Next = Free;

        Free = Node;

        FreeCount++;
    }
}

void object_map::Invalidate(slot* Slot)
{
    if(Slot)
    {
        Slot->Data->Reset();
        Slot->ID = 0;
    }
}