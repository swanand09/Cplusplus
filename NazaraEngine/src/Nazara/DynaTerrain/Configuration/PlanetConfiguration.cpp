// Copyright (C) 2012 Rémi Bèges
// This file is part of the "Nazara Engine".
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Error.hpp>
#include <Nazara/DynaTerrain/Config.hpp>
#include <Nazara/DynaTerrain/Configuration/PlanetConfiguration.hpp>
#include <Nazara/DynaTerrain/Debug.hpp>

NzPlanetConfiguration::NzPlanetConfiguration()
{
    //Rayon de la planète
    planetRadius = 2000.f;
}

NzPlanetConfiguration::~NzPlanetConfiguration()
{
    //dtor
}

void NzPlanetConfiguration::AutoFix()
{
    NzDynaTerrainConfigurationBase::AutoFix();
}

bool NzPlanetConfiguration::IsValid() const
{
    return NzDynaTerrainConfigurationBase::IsValid();
}


