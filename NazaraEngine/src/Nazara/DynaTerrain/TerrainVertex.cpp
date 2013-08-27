// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/TerrainVertex.hpp>
#include <Nazara/DynaTerrain/TerrainQuadTree.hpp>
#include <Nazara/TerrainRenderer/TerrainNodeID.hpp>
#include <Nazara/DynaTerrain/Debug.hpp>

NzTerrainVertex::NzTerrainVertex()
{
    m_isPositionInitialized = false;
}

void NzTerrainVertex::ComputePosition(NzTerrainQuadTree* quadtree, const NzTerrainNodeID& ID, const NzVector2i& offset)
{
    if(!m_isPositionInitialized)
    {
        m_position = quadtree->GetVertexPosition(ID,offset.x,offset.y);
        m_isPositionInitialized = true;
    }
}

const NzVector3f& NzTerrainVertex::GetPosition() const
{
    return m_position;
}

void NzTerrainVertex::Invalidate()
{
    m_isPositionInitialized = false;
}

bool NzTerrainVertex::IsInitialized() const
{
    return m_isPositionInitialized;
}

void NzTerrainVertex::SetPosition(const NzTerrainVertex& vertex)
{
    m_position = vertex.m_position;
    m_isPositionInitialized = true;
}

void NzTerrainVertex::SetPosition(const NzVector3f& position)
{
    m_position = position;
    m_isPositionInitialized = true;
}
