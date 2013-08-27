// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/DynaTerrain/Functions.hpp>
#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/Debug.hpp>

nzNeighbourDirection Reverse(nzNeighbourDirection direction)
{
    switch(direction)
    {
        case nzNeighbourDirection_top :
            return nzNeighbourDirection_bottom;
        break;

        case nzNeighbourDirection_right :
            return nzNeighbourDirection_left;
        break;

        case nzNeighbourDirection_bottom :
            return nzNeighbourDirection_top;
        break;

        case nzNeighbourDirection_left :
            return nzNeighbourDirection_right;
        break;
    }
    #if NAZARA_DYNATERRAIN_SAFE
    NazaraError("Unhandled case value : nzNeighbourDirection must have been modified");
    return nzNeighbourDirection_left;
    #endif
}

void Split(nzNodeLocation location, nzNeighbourDirection& first, nzNeighbourDirection& second)
{
    switch(location)
        {
            case nzNodeLocation_topleft:
                first = nzNeighbourDirection_top;
                second = nzNeighbourDirection_left;
            break;

            case nzNodeLocation_topright:
                first = nzNeighbourDirection_top;
                second = nzNeighbourDirection_right;
            break;

            case nzNodeLocation_bottomleft:
                first = nzNeighbourDirection_bottom;
                second = nzNeighbourDirection_left;
            break;

            case nzNodeLocation_bottomright:
                first = nzNeighbourDirection_bottom;
                second = nzNeighbourDirection_right;
            break;

        }
}
