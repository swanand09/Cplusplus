// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_ENUMS_DYNATERRAIN_HPP
#define NAZARA_ENUMS_DYNATERRAIN_HPP

enum nzNodeLocation
{
    nzNodeLocation_topleft,
    nzNodeLocation_topright,
    nzNodeLocation_bottomleft,
    nzNodeLocation_bottomright
};

enum nzNeighbourDirection
{
    nzNeighbourDirection_top = 0,
    nzNeighbourDirection_bottom = 1,
    nzNeighbourDirection_left = 2,
    nzNeighbourDirection_right = 3
};

enum nzConnectionType
{
  nzConnectionType_straight,
  nzConnectionType_orthogonal,
  nzConnectionType_reverse,
  nzConnectionType_none
};

enum nzQuadTreeType
{
    nzQuadTreeType_terrain,
    nzQuadTreeType_planet
};

class NzTerrainChunksManager;
class NzTerrainQuadTree;
class NzTerrainNormalsManager;

struct nzTerrainNodeData
{
    NzTerrainQuadTree* quadtree;
    NzTerrainChunksManager* chunksManager;
    NzTerrainNormalsManager* normalsManager;
};
#endif // NAZARA_ENUMS_DYNATERRAIN_HPP
