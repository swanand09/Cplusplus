// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_DYNATERRAINCONFIGURATIONBASE_HPP
#define NAZARA_DYNATERRAINCONFIGURATIONBASE_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Math/Vector3.hpp>

class NAZARA_API NzDynaTerrainConfigurationBase
{
    //For now, there are two different mesh-optimizing methods :
        //-Distance to camera
        //-Slope variation
    //Each method accepts various parameters, but there are several conditions over these parameters
    //This class helps configurating the quadtree and checks input parameters

    friend class NzDynaTerrainMainClassBase;
    friend class NzTerrainQuadTree;
    friend class NzDynamicTerrain;
    friend class NzTerrainInternalNode;
    public:
        NzDynaTerrainConfigurationBase();
        ~NzDynaTerrainConfigurationBase();

        virtual void AutoFix();

        virtual bool IsValid() const;

        float maxHeight;
        unsigned int terrainMinimalPrecision;

        //NzString groundTextures;

    protected:
        int x_offset;
        int y_offset;
    private:

};

#endif // NAZARA_DYNATERRAINCONFIGURATIONBASE_HPP
