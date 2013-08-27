// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_TERRAINCONFIGURATION_HPP
#define NAZARA_TERRAINCONFIGURATION_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/DynaTerrain/Configuration/DynaTerrainConfigurationBase.hpp>
#include <Nazara/Math/EulerAngles.hpp>

class NAZARA_API NzTerrainConfiguration : public NzDynaTerrainConfigurationBase
{
    public:
        NzTerrainConfiguration();
        ~NzTerrainConfiguration();

        void AutoFix();

        bool IsValid() const;

        //Terrain parameters

        float terrainSize;
        NzEulerAnglesf terrainOrientation;
    protected:
    private:
};

#endif // NAZARA_TERRAINCONFIGURATION_HPP
