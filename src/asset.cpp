#include "asset.h"

asset::asset(uint32_t AssetID, std::string AssetPath):
    ID(AssetID),
    Path(AssetPath)
{ }

asset::~asset()
{ }