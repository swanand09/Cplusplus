// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/TerrainRenderer/TerrainNodeID.hpp>
#include <cmath>
#include <Nazara/DynaTerrain/Debug.hpp>

NzTerrainNodeID::NzTerrainNodeID()
{
    depth = 0;
    locx = 0;
    locy = 0;
}

NzTerrainNodeID::NzTerrainNodeID(int Depth, int locationx, int locationy) : depth(Depth), locx(locationx), locy(locationy)
{

}

bool NzTerrainNodeID::IsValid() const
{
    return depth >= 0 && locx >= 0 && locy >= 0 && locx < (std::pow(2,depth)) && locy < (std::pow(2,depth));
}

void NzTerrainNodeID::InvertXY()
{
    int tmp = locx;
    locx = locy;
    locy = tmp;
}

void NzTerrainNodeID::FlipX()
{
    //TODO
}

void NzTerrainNodeID::FlipY()
{
    //TODO
}

void NzTerrainNodeID::Normalize()
{
    if(locx < 0)
        locx += std::pow(2,depth);

    if(locy < 0)
        locy += std::pow(2,depth);

    if(locx > (std::pow(2,depth)-1))
        locx -= std::pow(2,depth);

    if(locy > (std::pow(2,depth)-1))
        locy -= std::pow(2,depth);
}

bool NzTerrainNodeID::operator<( const NzTerrainNodeID& id ) const
{
    return (this->depth != id.depth) ? this->depth < id.depth : (this->locx != id.locx) ? this->locx < id.locx : this->locy < id.locy;
}
