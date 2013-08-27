// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_PLANETCONFIGURATION_HPP
#define NAZARA_PLANETCONFIGURATION_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/DynaTerrain/Configuration/DynaTerrainConfigurationBase.hpp>
#include <Nazara/Math/EulerAngles.hpp>

class NAZARA_API NzPlanetConfiguration : public NzDynaTerrainConfigurationBase
{
    public:
        NzPlanetConfiguration();
        ~NzPlanetConfiguration();

        void AutoFix();

        bool IsValid() const;

        //Planet parameters
        float planetRadius;

    protected:
    private:
};

#endif // NAZARA_PLANETCONFIGURATION_HPP
