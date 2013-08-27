// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_TERRAINNODEID_HPP
#define NAZARA_TERRAINNODEID_HPP

#include <Nazara/Prerequesites.hpp>

class NAZARA_API NzTerrainNodeID
{
    public:

        NzTerrainNodeID();
        NzTerrainNodeID(int Depth, int locationx, int locationy);
        ~NzTerrainNodeID() = default;

        bool IsValid() const;

        void InvertXY();
        void Normalize();//A RENOMMER ?
        void FlipX();
        void FlipY();

        bool operator<( const NzTerrainNodeID& id ) const;

        int depth;
        int locx;
        int locy;
    private:
};

#endif // NAZARA_TERRAINNODEID_HPP
