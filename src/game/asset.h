#ifndef ASSET_H
#define ASSET_H

#include <string>
#include <cstdint>

class asset 
{

protected:
             asset(uint32_t ID, std::string AssetPath);

public:
    virtual ~asset();

public:
    uint32_t    ID;
    std::string Path;
};


#endif