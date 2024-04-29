#ifndef SHIP_H
#define SHIP_H

#include "game_object.h"

class ship: public game_object
{

private: /* PREVENT COPY AND 
            MOVE CONSTRUCTION */
    ship(const ship& Right) = delete;
    ship(ship&& Right) = delete;
    ship& operator=(const ship& Right) = delete;
    ship& operator=(ship&& Right) = delete;

public: /* CONSTRUCTOR AND DESTRUCTORS */
             ship();
    virtual ~ship();

public: /* STATIC CREATIONAL METHODS */
    static ship* Make(uint32_t AssetID, 
                      int ShipX, int ShipY,
                      int ShipW, int ShipH,
                      float BaseSpeed, 
                      float MaxSpeed)
    {
        ship* Ship = new ship();

        if(!Ship)
        {
            // logging, failed to alloc
            // memory for a ship;

            return nullptr;
        }

        Ship->SetAssetID(AssetID);
        Ship->SetPosition(ShipX, ShipY);
        Ship->SetSize(ShipW, ShipH);
        Ship->SetVelocityParams(BaseSpeed,
                                MaxSpeed);
        return Ship;

    }
};

#endif