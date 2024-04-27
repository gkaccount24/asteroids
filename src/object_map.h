#ifndef object_map_H
#define object_map_H

#include "node.h"
#include "space_object.h"

#include <vector>
#include <cstdint>

class object_map 
{
    struct slot
    {
        uint32_t      ID;
        space_object* Data;
    };

public:
    object_map();
    ~object_map();

public:
    uint32_t Size() const;
    bool Empty() const;
    uint32_t FreeSize() const;
    uint32_t Capacity() const;

public:
    void Remove(uint32_t Idx);
    space_object* Get(uint32_t Idx);
    uint32_t Add(space_object* Value);

    void Destroy();
    void Clear() ;

private:
    void Invalidate(slot* Slot);
    void PopFree();
    void AddToFree(uint32_t Idx);

private:
    node*              Free;
    uint32_t           FreeCount;
    uint32_t           SlotCapacity;
    std::vector<slot*> Slots;
};

#endif