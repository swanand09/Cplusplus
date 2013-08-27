// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_TERRAINVERTEX_HPP
#define NAZARA_TERRAINVERTEX_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Math/Vector3.hpp>

class NzTerrainQuadTree;
class NzTerrainNodeID;

class NAZARA_API NzTerrainVertex
{
    public:
        NzTerrainVertex();
        ~NzTerrainVertex() = default;

        void SetPosition(const NzTerrainVertex& vertex);
        void SetPosition(const NzVector3f& position);
        const NzVector3f& GetPosition() const;

        void ComputePosition(NzTerrainQuadTree* quadtree, const NzTerrainNodeID& ID, const NzVector2i& offset);

        void Invalidate();
        bool IsInitialized() const;

    protected:
    private:
        NzVector3f m_position;
        bool m_isPositionInitialized;
};

#endif // NAZARA_TERRAINVERTEX_HPP
